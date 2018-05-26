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
	Menu m;
	m.runMenu();

	ComplexVec d = {1,2,3,4, 5};


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
	std::cout << std::endl;

	std::system("pause");
	return 0;
}

