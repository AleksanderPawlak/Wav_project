#pragma once
#include "WavDecoder.h"

struct DecoderMenu
{
	void doRSA(WavDecoder&);
	void revertRSA(WavDecoder&);
	void doXOR(WavDecoder&);
	
private:
	void handleEncryptionResult(WavDecoder&, const std::vector<short int>&);
};

class Menu
{
	WavDecoder decoder;

	void loadFile();
	void playFile();
	void SaveFile();
	void displayFileFFT();
	void displayFileData();
	void encryptData();
	void displayHeaderBasics();

public:
	Menu();
	~Menu();

	void runMenu();
};

