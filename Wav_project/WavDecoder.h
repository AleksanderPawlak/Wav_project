#pragma once
#include <vector>

struct Wav_Header
{
	unsigned char chunkID[4];
	unsigned long chunkSize;
	unsigned char format[4];
	unsigned char subchunk1ID[4];
	unsigned long subchunk1Size;
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned long sampleRate;
	unsigned long byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
};

struct Wav_Data
{
	unsigned char subchunk2ID[4];
	unsigned long subchunk2Size;
};

struct WavStereoSample
{
	int l;
	int r;
};

class WavDecoder
{
	Wav_Header fileHeader;
	Wav_Data dataArgs;

	std::vector<WavStereoSample> audioData;
	__int16* audioMonoData;

	unsigned int samplesNumber;
	
public:

	void readFile(std::string);
	void writeToFile(std::string);

	std::vector<int> getMonoData();
	std::vector<WavStereoSample> getStereoData();

	int getChannelsNumber();
	int getNumberOfSamples();

	Wav_Header getWavHeader();

	void setMonoData(std::vector<int> inputData);

	WavDecoder() {};
	~WavDecoder() {};
};
