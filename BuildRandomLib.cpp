// BuildRandomLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>

#include "BuildRandom.hpp"

template <typename T, typename X>
void FillContainerTest()
{
	using std::for_each;
	using std::endl;
	using std::cout;
	using std::begin;
	using std::end;
	//filling a container T with random X between 5 and 100 elements long.
	T fillContainer;
	const bool result = BuildRandom::FillContainerRandom<X>(fillContainer, 100, 5);
	std::cout << "Printing some values from a " << typeid(X).name() << std::endl;
	for_each(begin(fillContainer), end(fillContainer), [](const auto elem)
		{
			if constexpr (std::is_same_v<X, char> || std::is_same_v<X, unsigned char>)
			{
				std::cout << std::dec << "[" << static_cast<const int>(elem) << "]";
			}
			else
				std::cout << std::dec << "[" << static_cast<X>(elem) << "]";
		});
	std::cout << std::endl << std::endl;
}

int main()
{
	/* Note if you run this solution with clang ASAN enabled, you will see "access violation reading location" messages as the asan expands the address space
	 * via generating exceptions.
	 * Also note that in VS 2019 having a "requires (someconcept) && (someconcept)" on a line separate from the template<typename T> declaration line
	 * would not parse! The compiler could not parse that line, it was very obviously a bug, so be aware if you use C++20 concepts in VS2019.
	 */
	using namespace std;
	//building a vector of strings with 10 strings of length between 3 and 5 characters.
	const auto stringVec = BuildRandom::BuildRandomStringVector(10, 5);
	cout << "Printing some character values, the default char type for std::string might be signed..." << endl;
	for_each(begin(stringVec), end(stringVec), [](const auto &selem)
		{
			for_each(begin(selem), end(selem), [](const auto celem)
				{
					cout << std::dec << "[" << static_cast<const int>(celem) << "]";
				});
			cout << endl;
		});
	cout << endl << endl;
	//building a vector of random size (between the arg values) with random data.
	const auto stringVec2 = BuildRandom::BuildRandomVector<unsigned char>(100, 5);
	cout << "Printing some unsigned character values." << endl;
	for_each(begin(stringVec2), end(stringVec2), [](const auto elem)
		{
			cout << std::dec << "[" << static_cast<const int>(elem) << "]";
		});
	cout << endl << endl;
	//building a vector of wstrings (wide char) with 10 strings of length between 3 and 5 characters.
	const auto stringVec3 = BuildRandom::BuildRandomWStringVector(10, 5);
	cout << "Printing some wide char values." << endl;
	for_each(begin(stringVec3), end(stringVec3), [](const auto selem)
		{
			for_each(begin(selem), end(selem), [](const auto welem)
				{
					cout << std::dec << "[" << static_cast<const int>(welem) << "]";
				});
			cout << endl;
		});
	cout << endl << endl;

	FillContainerTest<std::list<unsigned char>, unsigned char>();
	FillContainerTest<std::list<char>, char>();
	FillContainerTest<std::vector<int>, int>();
	FillContainerTest<std::vector<unsigned int>, unsigned int>();
	FillContainerTest<std::vector<long long>, long long>();
	FillContainerTest<std::vector<unsigned long long>, unsigned long long>();
	//FillContainerTest<std::vector<bool>, bool>(); // doesn't work for bool, constrained away
}
