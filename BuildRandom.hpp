#pragma once
#include <string>
#include <random>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <numeric>
#include <ranges>
#include <concepts>
#include <vector>

namespace BuildRandom
{
	using ValueRangeType = long long;
	using CountType = size_t;
	using CharType = unsigned char;
	using WCharType = wchar_t;
	using StringType = std::string;
	using WStringType = std::wstring;

	/// <typeparam name="T">Typename of values you want in the container.</typeparam>
	///	<typeparam name="X">Distribution template param to use, not less than sizeof an int</typeparam>
	/// <summary>Helper function used to fill a container</summary>
	///	<param name="containerType">some range capable container type</param>
	///	<param name="maxLength">the maximum count of the type T in the returned vector.</param>
	///	<param name="minLength">the minimum count of the type T in the returned vector.</param>
	///	<throws> exception on failure to resize container type. </throws>
	template <typename T, typename X> requires std::is_integral_v<T> && std::is_integral_v<X>
	constexpr void DoGenerate(std::ranges::range auto& containerType, const CountType maxLength, const CountType minLength)
	{
		std::uniform_int_distribution<X> distElementPossibility(std::numeric_limits<X>::min(), std::numeric_limits<X>::max());
		const std::uniform_int_distribution distLengthPossibility(minLength, maxLength);
		std::random_device rd;
		std::mt19937 randomElementGenerator(rd()); // seed mersenne engine
		//the distribution uses the generator engine to get the value
		const auto tLength = static_cast<std::size_t>(distLengthPossibility(randomElementGenerator));
		containerType.resize(tLength); // <-- can fail to allocate the memory.
		const auto GenLambda = [&randomElementGenerator, &distElementPossibility]()constexpr { return static_cast<T>(distElementPossibility(randomElementGenerator)); };
		std::ranges::generate(containerType, GenLambda);
	}
	/// <typeparam name="T">Typename of value you want in the return value.</typeparam>
	///	<typeparam name="X">Distribution template param to use, not less than sizeof an int</typeparam>
	/// <summary>Helper function used to get a range-bound value</summary>
	///	<param name="maxValue">the maximum value of the type T in the returned value.</param>
	///	<param name="minValue">the minimum value of the type T in the returned value.</param>
	///	<returns>T with random value</returns>
	template <typename T, typename X> requires std::is_integral_v<T>&& std::is_integral_v<X>
	constexpr T DoGenerateSingle(const T maxValue, const T minValue) noexcept
	{
		std::uniform_int_distribution<X> distElementPossibility(minValue,maxValue);
		std::random_device rd;
		std::mt19937 randomElementGenerator(rd()); // seed mersenne engine
		//the distribution uses the generator engine to get the value
		return static_cast<T>(distElementPossibility(randomElementGenerator));
	}
	/// <summary>Returns a vector of a random number of type <c>T</c> with randomized content using a uniform distribution. T must be default constructable.</summary>
	///	<param name="maxLength">the maximum count of the type T in the returned vector.</param>
	///	<param name="minLength">the minimum count of the type T in the returned vector.</param>
	/// <returns> a vector of type T with randomized content. Empty vector on error. </returns>
	template<typename T> requires std::is_arithmetic_v<T> && (!std::is_same_v<T, bool>)
	[[nodiscard]] constexpr auto BuildRandomVector(const CountType maxLength, const CountType minLength = 3) -> std::vector<T>
	{
		//arg error checking, returns empty vector as per description
		if (minLength > maxLength || (maxLength <= 0) || (minLength <= 0))
		{
			return std::vector<T>();
		}
		std::vector<T> currentBuiltVector;
		if constexpr (sizeof(T) <= sizeof(int) && std::is_unsigned_v<T>)
		{
			DoGenerate<T, unsigned int>(currentBuiltVector, maxLength, minLength);
		}
		else if constexpr (sizeof(T) <= sizeof(int) && std::is_signed_v<T>)
		{
			DoGenerate<T, int>(currentBuiltVector, maxLength, minLength);
		}
		else
		{
			DoGenerate<T, T>(currentBuiltVector, maxLength, minLength);
		}
		return currentBuiltVector;
	}
	/// <summary>Fills a container of type <c>T</c> with randomized content using a uniform distribution. T must be default constructable.</summary>
	///	<param name="containerType">some range capable container type</param>
	///	<param name="maxLength">the maximum count of the type T in the returned vector.</param>
	///	<param name="minLength">the minimum count of the type T in the returned vector.</param>
	/// <returns> true on success, false on error.</returns>
	template<typename T> requires std::is_integral_v<T> && (!std::is_same_v<T, bool>)
	[[nodiscard]] constexpr bool FillContainerRandom(std::ranges::range auto &containerType, const CountType maxLength, const CountType minLength = 3)
	{
		//arg error checking, returns false as per description
		if (minLength > maxLength || (maxLength <= 0) || (minLength <= 0))
		{
			return false;
		}
		if constexpr (sizeof(T) <= sizeof(int) && std::is_unsigned_v<T>)
		{
			DoGenerate<T, unsigned int>(containerType, maxLength, minLength);
		}
		else if constexpr (sizeof(T) <= sizeof(int) && std::is_signed_v<T>)
		{
			DoGenerate<T, int>(containerType, maxLength, minLength);
		}
		else
		{
			DoGenerate<T,T>(containerType, maxLength, minLength);
		}
		return true;
	}
	/// <summary>Returns a vector of <c>std::string</c> with randomized content using a uniform distribution.<para>NOTE:
	///	The char type is a character representation type that efficiently encodes members of the basic execution character set.
	///	The C++ compiler treats variables of type char, signed char, and unsigned char as having different types.
	///	<para>***Microsoft - specific: Variables of type char are promoted to int as if from type signed char by default,
	///	unless the / J compilation option is used. In this case, they're treated as type unsigned char and are promoted to int without sign extension.***</para>
	///	</para><para><a href="https://docs.microsoft.com/en-us/cpp/cpp/fundamental-types-cpp/">MSDOCS</a></para></summary>
	///	<param name="numberOfStrings">the number of strings in the returned vector.</param>
	///	<param name="maxLength">the maximum length of the strings in the returned vector.</param>
	///	<param name="minLength">the minimum length of the strings in the returned vector.</param>
	/// <returns> a vector of std::string with randomized content. Empty vector on error. </returns>
	[[nodiscard]] constexpr auto BuildRandomStringVector(const CountType numberOfStrings, const CountType maxLength, const CountType minLength = 3)
	{
		//arg error checking, returns empty vector as per description
		if (minLength > maxLength || (maxLength <= 0) || (numberOfStrings <= 0) || (minLength <= 0))
		{
			return std::vector<StringType>();
		}
		std::vector<StringType> ret;
		for (CountType i = 0; i < numberOfStrings; i++)
		{
			const auto tempString = BuildRandom::BuildRandomVector<CharType>(maxLength, minLength);
			ret.emplace_back(StringType(tempString.begin(), tempString.end()));
		}
		return ret;
	}
	/// <summary>Returns a vector of <c>std::wstring</c> with randomized content using a uniform distribution.</summary>
	///	<param name="numberOfStrings">the number of strings in the returned vector.</param>
	///	<param name="maxLength">the maximum length of the strings in the returned vector.</param>
	///	<param name="minLength">the minimum length of the strings in the returned vector.</param>
	/// <returns> a vector of std::wstring with randomized content. Empty vector on error. </returns>
	[[nodiscard]] constexpr auto BuildRandomWStringVector(const CountType numberOfStrings, const CountType maxLength, const CountType minLength = 3)
	{
		//arg error checking, returns empty vector as per description
		if (minLength > maxLength || (maxLength <= 0) || (numberOfStrings <= 0) || (minLength <= 0))
		{
			return std::vector<WStringType>();
		}
		std::vector<WStringType> ret;
		for (CountType i = 0; i < numberOfStrings; i++)
		{
			const auto tempString = BuildRandom::BuildRandomVector<WCharType>(maxLength, minLength);
			ret.emplace_back(WStringType(tempString.begin(), tempString.end()));
		}
		return ret;
	}
	/// <summary>Returns a vector of a random number of type <c>T</c> with randomized content using a uniform distribution. T must be default constructable.</summary>
	///	<param name="maxValue">the maximum value of the type T in the returned value.</param>
	///	<param name="minValue">the minimum value of the type T in the returned value.</param>
	/// <returns> A type T with random value. Default constructed T on error. </returns>
	template<typename T> requires std::is_arithmetic_v<T> && (!std::is_same_v<T, bool>)
	[[nodiscard]] constexpr T BuildRandomSingleValue(const T maxValue = std::numeric_limits<T>::max(), const T minValue = std::numeric_limits<T>::min()) noexcept
	{
		//arg error checking, returns default constructed T as per description
		if (minValue > maxValue)
		{
			return T{};
		}
		if constexpr (sizeof(T) <= sizeof(int) && std::is_unsigned_v<T>)
		{
			return DoGenerateSingle<T, unsigned int>(maxValue, minValue);
		}
		else if constexpr (sizeof(T) <= sizeof(int) && std::is_signed_v<T>)
		{
			return DoGenerateSingle<T, int>(maxValue, minValue);
		}
		else
		{
			return DoGenerateSingle<T, T>(maxValue, minValue);
		}
	}
}