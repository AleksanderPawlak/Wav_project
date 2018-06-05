// Wav_project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <thread>
#include <Windows.h>

#include "DataAlgorithms.h"
#include "WavDecoder.h"
#include "EncryptionAlgorithms.h"
#include "Menu.h"
#include <fstream>

#include <SFML\Audio.hpp>
#include <bitset>

int main()
{

	Menu m;
	m.runMenu();
	
	return 0;
}
