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

#include <bitset>

int main()
{
	/*std::string filename = "samplemono.wav";
	WavDecoder decoder;
	std::vector<double> data;

	//std::cout << "Prosze podac nazwe pliku\n";

	//std::cin >> filename;

	decoder.readFile(filename);

	if (decoder.getChannelsNumber() == 1)
	{
		//std::vector<__int16> tmpData;
		auto tmpData = (decoder.getMonoData());

		for (std::vector<int>::iterator it = tmpData.begin(); it != tmpData.begin() + 10; ++it)
		{
			std::cout << *it;
		}
		std::cout << std::endl;

		for (auto sample : tmpData)
		{
			data.push_back(double(sample));
		}
	}
	else if (decoder.getChannelsNumber() == 2)
	{
		auto tmpData = decoder.getStereoData();

		for (auto sample : tmpData)
		{
			data.push_back(sample.l);
		}
	}
	else
	{
		return 0;
	}

	std::cout << "bez dobla: \n";
	for (std::vector<double>::iterator it = data.begin(); it != data.begin() + 10; ++it)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	auto complexData = doubleToComplexVector(data);

	std::cout << "czysty: \n";
	for (std::vector<std::complex<double>>::iterator it = complexData.begin(); it != complexData.begin()+10; ++it)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	//fft(complexData);

	std::cout << "fft: \n";
	for (std::vector<std::complex<double>>::iterator it = complexData.begin(); it != complexData.begin() + 10; ++it)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

	//reverseFft(complexData);
	std::cout << "\n\nnieczysty: \n";
	for (std::vector<std::complex<double>>::iterator it = complexData.begin(); it != complexData.begin() + 10; ++it)
	{
		std::cout << *it;
	}
	std::cout << std::endl;


	//std::thread display(DisplayComplexVector, complexData, filename, -1);

	auto properties = decoder.getWavHeader();

	std::cout << "Czestotliwosc:  " << properties.sampleRate << std::endl;
	std::cout << "Liczba probek:  " << decoder.getNumberOfSamples() << std::endl;
	std::cout << "Liczba kanalow: " << decoder.getChannelsNumber() << std::endl;
	std::cout << "Liczba bitow na probke: " << properties.bitsPerSample << std::endl << std::endl;

	//if (display.joinable())
	//{
		//display.join();
	//}

	decoder.writeToFile("dupa.wav");*/
	/*
	std::vector<std::complex<double>> dupa{-777.0, 2.0, 3.0, 4.0};

	fft(dupa);
	//reverseFft(dupa);
	for (auto i : dupa)
		std::cout << i;*/
	/*short int l = 32761;

	std::bitset<16> b(l);

	b[1] = 1;
	b[2] = 1;
	//uint8_t b[] = {l, l >> 8 };
	//b[0] = 1;
	//std::memcpy(&b, &l, sizeof(short int));
	short int o;
	//b[0] = (uint8_t)(l & 0xff);
	//b[1] = (uint8_t)((l >> 8) & 0xff);
	std::memcpy(&o, &b, sizeof(short int));
	std::cout << o;*/

	std::vector<short int> dupa;
	//uint8_t b[] = { 123, 1 };
	short int o = -2137;
	//std::memcpy(&o, &b, sizeof(short int));

	dupa.push_back(o);

	auto keys = EncryptionAlgorithms::generateKeys(13, 11);

	//std::cout << keys.publicKey << " " << keys.privateKey << " " << keys.modulKey << std::endl;

	auto enc = EncryptionAlgorithms::Rsa8(dupa, keys.publicKey, keys.modulKey);

	auto dec = EncryptionAlgorithms::Rsa8(enc, keys.privateKey, keys.modulKey);

	for (auto val : dec)
		std::cout << val << "  ";

	std::system("pause");
	return 0;
}

