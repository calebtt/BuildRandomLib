// BuildRandomLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BuildRandom.hpp"


int main()
{
	using namespace std;
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
	const auto stringVec2 = BuildRandom::BuildRandomVector<unsigned char>(10, 5);
	cout << "Printing some unsigned character values." << endl;
	for_each(begin(stringVec2), end(stringVec2), [](const auto elem)
		{
			cout << std::dec << "[" << static_cast<const int>(elem) << "]";
		});
	cout << endl << endl;
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
}
