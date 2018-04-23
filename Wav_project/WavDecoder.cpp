#include "stdafx.h"
#include "WavDecoder.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <stdio.h>

std::vector<char> WavDecoder::splitMonoToStereo(std::vector<short int> inputData)
{
	std::vector<char> result(inputData.size() * 2);
	return result;
}

void WavDecoder::readFile(std::string filename1)
{
	const char* filename = filename1.c_str();
	FILE* file;
	errno_t openError = fopen_s(&file, filename, "rb");


	if (file == NULL || openError)
	{
		throw std::exception("Problem with file");
	}

	std::fread((&fileHeader), sizeof(fileHeader), 1, file);

	if (*(unsigned int *)&dataArgs.subchunk2ID == 0x46464952)
	{
		std::cerr << "Wrong file format" << std::endl;
		return;
	}

	while (true)
	{
		fread(&dataArgs, sizeof(dataArgs), 1, file);
		if (*(unsigned int *)&dataArgs.subchunk2ID == 0x61746164)
			break;
	}

	unsigned int sampleSize = fileHeader.bitsPerSample;

	if (sampleSize != 16)
	{
		fclose(file);
		throw std::invalid_argument("Not supported size of samples.");
	}

	this->samplesNumber = dataArgs.subchunk2Size * 8 / fileHeader.bitsPerSample;

	if (fileHeader.numChannels == 1 || fileHeader.numChannels == 2) {

		this->audioData = new short int[samplesNumber];

		std::fread(this->audioData, sizeof(short int), samplesNumber, file);
	}
	else
	{
		fclose(file);
		throw std::invalid_argument("Not supported channels number.");
	}

	std::fclose(file);
}

void WavDecoder::writeToFile(std::string inputFilename)
{
	const char* filename = inputFilename.c_str();
	FILE* file;
	errno_t openError = fopen_s(&file, filename, "wb");


	if (file == NULL || openError)
	{
		throw std::exception("Problem with file");
	}

	std::fwrite((&fileHeader), sizeof(Wav_Header), 1, file);
	std::fwrite((&dataArgs), sizeof(Wav_Data), 1, file);

	for (int i{}; i < samplesNumber; i++)
	{
		std::fwrite((&audioData[i]), sizeof(audioData), 1, file);
	}

	fclose(file);
}

std::vector<short int> WavDecoder::getAudioData()
{
	std::vector<short int> result;
	result.reserve(samplesNumber);

	for (int i{}; i < samplesNumber; i++)
	{
		result.push_back(audioData[i]);
	}

	return result;
}

int WavDecoder::getChannelsNumber()
{
	return this->fileHeader.numChannels;
}

int WavDecoder::getNumberOfSamples()
{
	return samplesNumber;
}

Wav_Header WavDecoder::getWavHeader()
{
	return this->fileHeader;
}

void WavDecoder::setData(std::vector<short int> inputData)
{
	/*if (inputData.size() != samplesNumber)
	{
		throw std::invalid_argument("Wrong vector size.");
	}*/

	delete[] audioData;
	audioData = new short int[inputData.size()];

	for (int i{}; i < inputData.size(); i++)
	{
		audioData[i] = inputData[i];
	}
}
