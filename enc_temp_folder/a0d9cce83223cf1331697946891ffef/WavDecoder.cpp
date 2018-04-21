#include "stdafx.h"
#include "WavDecoder.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <stdio.h>

void WavDecoder::ReadFile(std::string filename1)
{
	const char* filename = filename1.c_str();
	FILE* file;
	errno_t dupa = fopen_s(&file, filename, "rb");


	if (file == NULL)
	{
		std::cerr << "Problem with opening " << filename << std::endl;
		return;
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

	this->samplesNumber = dataArgs.subchunk2Size * 8 / fileHeader.bitsPerSample;

	if (fileHeader.numChannels == 2) {
		this->audioData.resize(samplesNumber);

		for (int i{}; i < samplesNumber; i++)
		{
			std::fread(&audioData[i], sampleSize, 1, file);
		}
	}
	else if (fileHeader.numChannels == 1) {
		this->audioMonoData = new __int16[samplesNumber];

		std::fread(this->audioMonoData, sizeof(__int16), samplesNumber, file);
	}
	else
	{
		std::cerr << "Not supported channels number" << std::endl;
	}

	std::fclose(file);
}

std::vector<int> WavDecoder::getMonoData()
{
	if (fileHeader.numChannels != 1)
	{
		std::cerr << "File doesn't contain mono samples" << std::endl;
		return std::vector<int>();
	}

	std::vector<int> result;
	result.reserve(samplesNumber);

	for (int i{}; i < samplesNumber; i++)
	{
		result.push_back(int(audioMonoData[i]));
	}

	return result;
}

std::vector<WavStereoSample> WavDecoder::getStereoData()
{
	if (fileHeader.numChannels != 2)
	{
		std::cerr << "File doesn't contain stereo samples" << std::endl;
		return std::vector<WavStereoSample>();
	}
	return this->audioData;
}

int WavDecoder::getChannelsNumber()
{
	return this->fileHeader.numChannels;
}

int WavDecoder::getNumberOfSamples()
{
	//return this->dataArgs.subchunk2Size;
	return samplesNumber;
}

Wav_Header WavDecoder::getWavHeader()
{
	return this->fileHeader;
}
