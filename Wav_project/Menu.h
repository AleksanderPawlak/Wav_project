#pragma once
#include "WavDecoder.h"
#include "EncryptionAlgorithms.h"


struct DecoderMenu
{
	void doRSA(WavDecoder&);
	void revertRSA(WavDecoder&);
	void doRSA128(WavDecoder&);
	void revertRSA128(WavDecoder&);
	void doXOR(WavDecoder&);

	RsaKeys<boostInt::int256_t> RSA256KeysFromConfig(std::string filename);
	RsaKeys<int> RSAKeysFromConfig(std::string filename);

private:
	void handleEncryptionResult(WavDecoder&, std::vector<short int>&);
};

class Menu
{
	WavDecoder decoder;

	void showDataValues();
	void loadFile();
	void playFile();
	void SaveFile();
	void displayFileFFT();
	void displayFileData();
	void encryptData();
	void displayHeaderBasics();

public:
	Menu() {};
	~Menu() {};

	void runMenu();
};
