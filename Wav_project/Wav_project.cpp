// Wav_project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <thread>

#include "DataAlgorithms.h"
#include "WavDecoder.h"
#include "EncryptionAlgorithms.h"
#include "Menu.h"

#include <bitset>

int main()
{
	//Menu m;
	//m.runMenu();

	/*ComplexVec d = {1,2,3,4, 5};


	for (auto value : d)
		std::cout << value << "  ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	fft(d);
	
	for (auto value : d)
		std::cout << value << "  ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


	reverseFft(d);

	for (auto value : d)
		std::cout << value << "  ";
	std::cout << std::endl;*/

	/*boostInt::int128_t dupa, ser;
	std::vector<short int> dd = {12, 23, -44, 2132, 9323, 2313, 9393, 1231};
	std::vector<short int> kek;

	boostInt::import_bits(dupa, dd.begin(), dd.end(), 16);
	boostInt::import_bits(ser, dd.begin(), dd.end(), 16);

	boostInt::export_bits(dupa, std::back_inserter(kek), 16);
	boostInt::export_bits(ser, std::back_inserter(kek), 16);

	for (auto value : kek)
		std::cout << value << "  ";*/

	boostInt::int128_t dupa = 1213912;
	boostInt::int256_t ss = dupa;

	std::system("pause");
	return 0;
}

