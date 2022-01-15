// BuildRandomLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>

#include "BuildRandom.hpp"


int main()
{
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
	//filling a vector<char> with random characters between 5 and 100 elements long.
	std::vector<char> fillVector;
	const bool result = BuildRandom::FillContainerRandom<char>(fillVector, 100, 5);
	cout << "Printing some character values from a std::vector." << endl;
	for_each(begin(fillVector), end(fillVector), [](const auto elem)
		{
			cout << std::dec << "[" << static_cast<const int>(elem) << "]";
		});
	cout << endl << endl;
	//filling a list<char> with random characters between 5 and 100 elements long.
	list<char> fillList;
	const bool result2 = BuildRandom::FillContainerRandom<char>(fillList, 100, 5);
	cout << "Printing some character values from a std::list." << endl;
	for_each(begin(fillList), end(fillList), [](const auto elem)
		{
			cout << std::dec << "[" << static_cast<const int>(elem) << "]";
		});
	cout << endl << endl;
}
