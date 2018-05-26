#pragma once
#include <vector>
#include <bitset>
#include <iostream>
struct RsaKeys
{
	int privateKey;
	int publicKey;
	int modulKey;
};

namespace EncryptionAlgorithms
{

	bool isPrime(int);
	int nwd(int, int);
	int inverseModulo(int, int);
	int powMod(int value, int pow, int m);

	RsaKeys generateKeys(int, int);

	std::vector<short int> xor (const std::vector<short int>& inputVector, const std::vector<short int> keyVector);

	std::vector<short int> encryptRsa8 (const std::vector<short int>& inputData, const short int & e, const short int & n);
	std::vector<short int> decryptRsa8(const std::vector<short int>& inputData, const short int & e, const short int & n);
	std::vector<short int> encryptRsa16(const std::vector<short int>& inputData, const short int & e, const short int & n);
	std::vector<short int> decryptRsa16(const std::vector<short int>& inputData, const short int & e, const short int & n);
};

