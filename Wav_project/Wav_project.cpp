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

	/*auto keys = EncryptionAlgorithms::generateKeys(67, 131);
	std::cout << keys.modulKey << " " << keys.privateKey << " " << keys.publicKey << std::endl;

	std::vector<short int> dupa = {1231,-231,-546,999,312,-9};

	auto dec = EncryptionAlgorithms::encryptRsa8(dupa, 7, 8777);
	auto res = EncryptionAlgorithms::decryptRsa8(dec, 4903, 8777);

	for (auto i : res)
		std::cout << i << " ";
	std::cout << std::endl;*/
	
	boostInt::int256_t ser, pep, sen;
	ser.assign("52751510013433959741152243176812731813");
	pep.assign("68024952896801804974038439994705433499");
	sen.assign("123121442");
	auto mem = EncryptionAlgorithms::generateKeys256(ser, pep);
	
	/*std::cout << mem.privateKey << std::endl;
	std::cout << mem.publicKey << std::endl;
	std::cout << mem.modulKey << std::endl;*/
	
	//std::vector<short int> dupa = { -41 ,-86 ,-86 ,-57, -57, -286 ,-286 ,-330 ,-330 ,-308 ,-308  ,69  ,69  ,484  ,484  ,305  ,305  ,121  ,121 , 575 };//{1243, -12223, 1, 1, 12221, 32318, -4321, 28218, -28218, 77, 1, 92, 340, 12, 44, -21, 40};
	/*std::vector<short int> dupa{-9724};
	auto enc = EncryptionAlgorithms::encryptRsa128(dupa, mem.publicKey, mem.modulKey);
	auto bec = EncryptionAlgorithms::decryptRsa128(enc, mem.privateKey, mem.modulKey);
	std::cout << dupa[0]<< "   " << enc[0] <<"  "<< bec[0]<<std::endl;*/
	/*WavDecoder dd;
	dd.readFile("samplemono.wav");
	std::vector<short int> dupa;

	dupa = dd.getAudioData();
	std::vector<short int> rez;
	std::cout << "raz   " << dupa.size();
	rez.reserve(dupa.size());
	auto enc = EncryptionAlgorithms::encryptRsa128(dupa, mem.publicKey, mem.modulKey);
	std::cout << enc.size() << std::endl;

	auto dec = EncryptionAlgorithms::decryptRsa128(dupa, mem.privateKey, mem.modulKey);

	/*for (int i{ 0 }, j{ 1040 }; j < enc.size(); i += 1040, j += 1040)
	{

		std::cout << "sram\n";
		std::vector<short int> ded(enc.begin() + i, enc.begin() + j);
		auto dec = EncryptionAlgorithms::decryptRsa128(ded, mem.privateKey, mem.modulKey);

		rez.insert(rez.end(), dec.begin(), dec.end());
	}*/
	/*
	for (int i{}; i < rez.size(); i++)
		if (dec[i] != dupa[i]) {
			std::cout << "Na poz  " << i << std::endl;
			break;
		}*/
	/*for (auto v : enc)
		std::cout << v << "  ";*/
	/*int popo{999};
	for (int i{ 0 }; i < 5000; i++)
		if (dec[i] != dupa[i])
		{
			popo = -1010;
			std::cout << "zepsulo sie na  " << i << std::endl;
		}

	std::cout << popo << std::endl;

	std::system("pause");*/
	//std::cout << dec.size() << std::endl;
	std::system("pause");
	return 0;
}

