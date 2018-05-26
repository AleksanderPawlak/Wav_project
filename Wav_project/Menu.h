#pragma once
#include "WavDecoder.h"

class Menu
{
	WavDecoder decoder;

	void loadFile();
	void playFile();
	void SaveFile();
	void displayFileFFT();
	void encryptData();
	void displayHeaderBasics();

public:
	Menu();
	~Menu();

	void runMenu();
};

