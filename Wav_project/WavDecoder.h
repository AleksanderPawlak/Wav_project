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

class WavDecoder
{
	Wav_Header fileHeader;
	Wav_Data dataArgs;

	short int* audioData;

	unsigned int samplesNumber;
	
public:
	static std::vector<char> splitMonoToStereo(std::vector<short int>);

	void readFile(std::string);
	void writeToFile(std::string);

	std::vector<short int> getAudioData();

	int getChannelsNumber();
	int getNumberOfSamples();

	Wav_Header getWavHeader();

	void setData(std::vector<short int> inputData);

	WavDecoder() {};
	~WavDecoder() { delete[] audioData; };
};
