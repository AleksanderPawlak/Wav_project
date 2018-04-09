// Wav_project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <thread>

#include "DataAlgorithms.h"
#include "WavDecoder.h"





int main()
{
	std::string filename = "samplemono.wav";
	WavDecoder decoder;
	std::vector<double> data;

	std::cout << "Prosze podac nazwe pliku\n";

	std::cin >> filename;

	decoder.ReadFile(filename);

	if (decoder.getChannelsNumber() == 1)
	{
		auto tmpData = decoder.getMonoData();
		
		for (auto sample : tmpData)
		{
			data.push_back(sample);
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

	auto complexData = doubleToComplexVector(data);

	fft(complexData);

	std::thread display(DisplayWavFFT, complexData, filename, -1);

	auto properties = decoder.getWavHeader();

	std::cout << "Czestotliwosc:  " << properties.sampleRate << std::endl;
	std::cout << "Liczba probek:  " << decoder.getNumberOfSamples() << std::endl;
	std::cout << "Liczba kanalow: " << decoder.getChannelsNumber() << std::endl;
	std::cout << "Liczba bitow na probke: " << properties.bitsPerSample << std::endl << std::endl;

	if (display.joinable())
	{
		display.join();
	}

	std::system("pause");
	return 0;
}

