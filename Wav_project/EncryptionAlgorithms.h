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

	std::vector<int> xor (const std::vector<int>& inputVector, const std::vector<int> keyVector);

	std::vector<short int> Rsa8 (const std::vector<short int>& inputData, const int & e, const int & n);
};

