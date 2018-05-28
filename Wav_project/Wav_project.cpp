// Wav_project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <thread>

#include "DataAlgorithms.h"
#include "WavDecoder.h"
#include "EncryptionAlgorithms.h"
#include "Menu.h"

#include <bitset>

int main()
{
	//Menu m;
	//m.runMenu();

	/*ComplexVec d = {1,2,3,4, 5};


	for (auto value : d)
		std::cout << value << "  ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	fft(d);
	
	for (auto value : d)
		std::cout << value << "  ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


	reverseFft(d);

	for (auto value : d)
		std::cout << value << "  ";
	std::cout << std::endl;*/

	/*boostInt::int128_t dupa, ser;
	std::vector<short int> dd = {12, 23, -44, 2132, 9323, 2313, 9393, 1231};
	std::vector<short int> kek;

	boostInt::import_bits(dupa, dd.begin(), dd.end(), 16);
	boostInt::import_bits(ser, dd.begin(), dd.end(), 16);

	boostInt::export_bits(dupa, std::back_inserter(kek), 16);
	boostInt::export_bits(ser, std::back_inserter(kek), 16);

	for (auto value : kek)
		std::cout << value << "  ";*/

	/*boostInt::int128_t dataBlock;
	std::vector<short int> tmpVec = { 231,343,123,45,-22, 23,59, 94 }, result, ser = {2};

	boostInt::import_bits(dataBlock, tmpVec.begin(), tmpVec.end(), 16);
	boostInt::int256_t encryptedBlock = dataBlock;
	//boostInt::import_bits(encryptedBlock, ser.begin(), ser.end(), 16);

	boostInt::export_bits(encryptedBlock, std::back_inserter(result), 16);

	for (auto value : result)
		std::cout << value << "  ";
	std::cout << std::endl;*/
	


	/*auto keys = EncryptionAlgorithms::generateKeys(67, 131);
	std::cout << keys.modulKey << " " << keys.privateKey << " " << keys.publicKey << std::endl;

	std::vector<short int> dupa = {1231,-231,-546,999,312,-9};

	auto dec = EncryptionAlgorithms::encryptRsa8(dupa, 7, 8777);
	auto res = EncryptionAlgorithms::decryptRsa8(dec, 4903, 8777);

	for (auto i : res)
		std::cout << i << " ";
	std::cout << std::endl;*/
	boostInt::int256_t suk;
	boostInt::int128_t ser, pep, sen;
	ser.assign("52751510013433959741152243176812731813");
	pep.assign("68024952896801804974038439994705433499");
	sen.assign("527");
	suk = ser;

	auto mem = EncryptionAlgorithms::generateKeys128(ser, pep);

	std::cout << mem.privateKey << std::endl;
	std::cout << mem.publicKey << std::endl;
	std::cout << mem.modulKey << std::endl;

	std::vector<short int> dupa = {1, -1, 1, 1, 1, 1, -1, 1};

	auto enc = EncryptionAlgorithms::encryptRsa128(dupa, mem.publicKey, mem.modulKey);
	auto dec = EncryptionAlgorithms::decryptRsa128(enc, mem.privateKey, mem.modulKey);

	for (auto v : dec)
		std::cout << v << "  ";
	std::cout << std::endl;
	//std::cout << "amammam "  << EncryptionAlgorithms::powMod128(EncryptionAlgorithms::powMod128(12122, mem.publicKey, mem.modulKey), mem.privateKey, mem.modulKey) << std::endl;
	//seks.assign("22535833610500932295038042708271200209190285849060804598076968552725383424859");

	std::system("pause");
	return 0;
}

