#pragma once
#include <string>
#include <random>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <numeric>
#include <ranges>

namespace BuildRandom
{
	using CountType = int;
	using CharType = unsigned char;
	using WCharType = wchar_t;
	using StringType = std::string;
	using WStringType = std::wstring;

	/// <summary>Returns a vector of a random number of type <c>T</c> with randomized content using a uniform distribution. T must be default constructable.</summary>
	///	<param name="maxLength">the maximum count of the type T in the returned vector.</param>
	///	<param name="minLength">the minimum count of the type T in the returned vector.</param>
	/// <returns> a vector of type T with randomized content. Empty vector on error. </returns>
	template<typename T>
	requires std::is_integral_v<T> && std::is_pod_v<T> && std::is_trivial_v<T>
	[[nodiscard]] constexpr static auto BuildRandomVector(const CountType maxLength, const CountType minLength = 3) noexcept
	{
		//arg error checking, returns empty vector as per description
		if (minLength >= maxLength || (maxLength <= 0) || (minLength <= 0))
		{
			return std::vector<T>();
		}
		//Test all kinds of random type T possibilities.
		std::uniform_int_distribution<> distElementPossibility
		(std::numeric_limits<T>::min(),
			std::numeric_limits<T>::max());

		const std::uniform_int_distribution<> distLengthPossibility(minLength, maxLength);
		std::random_device rd;
		std::mt19937 stringGenerator(rd()); // seed mersenne engine

		//lambda used with std::generate to fill the vector with type T of randomized content.
		const auto getRandomElement = [&distElementPossibility, &stringGenerator]()
		{
			return static_cast<T>(distElementPossibility(stringGenerator));
		};
		//the distribution uses the generator engine to get the value
		const auto tLength = static_cast<std::size_t>(distLengthPossibility(stringGenerator));
		std::vector<T> currentBuiltVector(tLength, T{});
		std::generate(std::begin(currentBuiltVector), std::end(currentBuiltVector), getRandomElement);
		return currentBuiltVector;
	}
	/// <summary>Fills a container of type <c>T</c> with randomized content using a uniform distribution. T must be default constructable.</summary>
	///	<param name="maxLength">the maximum count of the type T in the returned vector.</param>
	///	<param name="minLength">the minimum count of the type T in the returned vector.</param>
	/// <returns> true on success, false on error.</returns>
	template<typename T>
	[[nodiscard]] constexpr static bool FillContainerRandom(std::ranges::range auto &containerType, const CountType maxLength, const CountType minLength = 3) noexcept
	{
		//arg error checking, returns false as per description
		if (minLength >= maxLength || (maxLength <= 0) || (minLength <= 0))
		{
			return false;
		}
		//Test all kinds of random type T possibilities.
		std::uniform_int_distribution<> distElementPossibility
		(std::numeric_limits<T>::min(),
			std::numeric_limits<T>::max());

		const std::uniform_int_distribution<> distLengthPossibility(minLength, maxLength);
		std::random_device rd;
		std::mt19937 randomElementGenerator(rd()); // seed mersenne engine

		//lambda used with std::generate to fill the vector with type T of randomized content.
		const auto getRandomElement = [&distElementPossibility, &randomElementGenerator]()
		{
			return static_cast<T>(distElementPossibility(randomElementGenerator));
		};
		//the distribution uses the generator engine to get the value
		const auto tLength = static_cast<std::size_t>(distLengthPossibility(randomElementGenerator));
		containerType.resize(tLength);
		std::generate(std::begin(containerType), std::end(containerType), getRandomElement);
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
	[[nodiscard]] constexpr static auto BuildRandomStringVector(const CountType numberOfStrings, const CountType maxLength, const CountType minLength = 3) noexcept
	{
		//arg error checking, returns empty vector as per description
		if (minLength >= maxLength || (maxLength <= 0) || (numberOfStrings <= 0) || (minLength <= 0))
		{
			return std::vector<StringType>();
		}
		std::vector<StringType> ret;
		for (CountType i = 0; i < numberOfStrings; i++)
		{
			const auto tempString = BuildRandom::BuildRandomVector<CharType>(maxLength, minLength);
			ret.emplace_back(StringType(std::begin(tempString), std::end(tempString)));
		}
		return ret;
	}
	/// <summary>Returns a vector of <c>std::wstring</c> with randomized content using a uniform distribution.</summary>
	///	<param name="numberOfStrings">the number of strings in the returned vector.</param>
	///	<param name="maxLength">the maximum length of the strings in the returned vector.</param>
	///	<param name="minLength">the minimum length of the strings in the returned vector.</param>
	/// <returns> a vector of std::wstring with randomized content. Empty vector on error. </returns>
	[[nodiscard]] constexpr static auto BuildRandomWStringVector(const CountType numberOfStrings, const CountType maxLength, const CountType minLength = 3) noexcept
	{
		//arg error checking, returns empty vector as per description
		if (minLength >= maxLength || (maxLength <= 0) || (numberOfStrings <= 0) || (minLength <= 0))
		{
			return std::vector<WStringType>();
		}
		std::vector<WStringType> ret;
		for (CountType i = 0; i < numberOfStrings; i++)
		{
			const auto tempString = BuildRandom::BuildRandomVector<WCharType>(maxLength, minLength);
			ret.emplace_back(WStringType(std::begin(tempString), std::end(tempString)));
		}
		return ret;
	}
}