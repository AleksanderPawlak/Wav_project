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

	EncryptionAlgorithms d;
	auto p = d.generateKeys(13, 11);
	std::cout << p.publicKey << "   " << p.privateKey << " " << p.modulKey << std::endl;

	std::system("pause");
	return 0;
}

