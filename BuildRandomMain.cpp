#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>
#include <format>
#include "BuildRandom.hpp"

template <typename T, typename X>
void FillContainerTest(auto &strm, const int minLength = 10, const int maxLength = 10)
{
	using std::for_each;
	using std::endl;
	using std::cout;
	using std::begin;
	using std::end;
	using std::format; // modify this if your compiler doesn't have format yet
	//filling a container T with random X
	T fillContainer{};
	const bool result = BuildRandom::FillContainerRandom<X>(fillContainer, minLength, maxLength);
	strm << "Printing some values from a " << typeid(X).name() << std::endl;
	if (result)
	{
		for (const auto elem : fillContainer)
		{
			if constexpr (std::same_as<X, signed char> || std::same_as<X, unsigned char>)
				strm << std::dec << "[" << static_cast<const int>(elem) << "]";
			else
				strm << std::dec << "[" << static_cast<X>(elem) << "]";
		}
		strm << std::endl << std::endl;
	}
	else
		strm << format("Error filling container in FillContainerTests() where T:{0}, X:{1}, strm:{2}", typeid(T).name(), typeid(X).name(), typeid(strm).name());
}

int main()
{
	/* Note if you run this solution with clang ASAN enabled, you will see "access violation reading location" messages as the asan expands the address space
	 * via generating exceptions.
	 * Also note that in VS 2019 having a "requires (someconcept) && (someconcept)" on a line separate from the template<typename T> declaration line
	 * would not parse! The compiler could not parse that line, it was very obviously a bug, so be aware if you use C++20 concepts in VS2019.
	 */
	using namespace std;
	constexpr size_t NumberOfItems= 10;
	constexpr size_t MaxLengthOfStrings = 10;
	constexpr size_t MinLengthOfStrings = 3;
	constexpr size_t MinLength = 10;
	constexpr size_t MaxLength = 10;
	// can be used to delay or disable output.
	std::stringstream ss;
	std::wstringstream ws;
	//building a vector of strings
	const auto stringVec = BuildRandom::BuildRandomStringVector(NumberOfItems, MaxLengthOfStrings, MaxLengthOfStrings);
	ss << "Printing some character values, the default char type for std::string might be signed..." << endl;
	for (const auto& selem : stringVec)
	{
		for (const auto celem : selem)
			ss << std::dec << "[" << static_cast<const int>(celem) << "]";
		ss << endl;
	}
	ss << endl << endl;
	//building a vector of random size (between the arg values) with random data.
	const auto stringVec2 = BuildRandom::BuildRandomVector<unsigned char>(MinLength, MaxLength);
	ss << "Printing some unsigned character values." << endl;
	for (const auto elem : stringVec2)
		ss << std::dec << "[" << static_cast<const int>(elem) << "]";
	ss << endl << endl;
	//building a vector of wstrings (wide char)
	const auto stringVec3 = BuildRandom::BuildRandomWStringVector(NumberOfItems, MinLengthOfStrings, MaxLengthOfStrings);
	ws << "Printing some wide char values." << endl;
	for (const auto& selem : stringVec3)
	{
		for (const auto welem : selem)
			ws << std::dec << "[" << static_cast<const int>(welem) << "]";
		ws << endl;
	}
	cout << ss.str();
	wcout << ws.str();
	ss.str("");
	FillContainerTest<std::list<unsigned char>, unsigned char>(ss);
	FillContainerTest<std::list<char>, char>(ss);
	FillContainerTest<std::vector<int>, int>(ss);
	FillContainerTest<std::vector<unsigned int>, unsigned int>(ss);
	FillContainerTest<std::vector<long long>, long long>(ss);
	FillContainerTest<std::vector<unsigned long long>, unsigned long long>(ss);
	cout << ss.str();
	ss.str("");
	
	//building single element values
	auto PrintSingleValue = [&ss](auto val)
	{
		//ss.imbue(std::locale(""));
		ss << typeid(decltype(val)).name() << ":" << std::showpos << std::dec << val << endl;
	};
	PrintSingleValue(BuildRandom::BuildRandomSingleValue<unsigned char>());
	PrintSingleValue(BuildRandom::BuildRandomSingleValue<signed char>());
	PrintSingleValue(BuildRandom::BuildRandomSingleValue<unsigned int>());
	PrintSingleValue(BuildRandom::BuildRandomSingleValue<signed int>());
	PrintSingleValue(BuildRandom::BuildRandomSingleValue<unsigned long long>());
	PrintSingleValue(BuildRandom::BuildRandomSingleValue<signed long long>());
	cout << ss.str();
	ss.str("");


	//FillContainerTest<std::vector<bool>, bool>(ss); // doesn't work for bool, constrained away
	/* Uncomment below to test vector too large exception handling. */
	//ss << "Building a container that is far too large, in order to catch the alloc exception." << std::endl;
	//cout << ss.str();
	//try
	//{
	//	using BigSize = size_t;
	//	constexpr BigSize BigVectorSize = std::numeric_limits<BigSize>::max()-1;
	//	auto bigVec = BuildRandom::BuildRandomVector<BigSize>(BigVectorSize, BigVectorSize);
	//}
	//catch (const std::exception &e)
	//{
	//	ss << e.what() << std::endl;
	//	cout << ss.str();
	//}
	cout << "Enter to exit." << endl;
	cin.get();
}
