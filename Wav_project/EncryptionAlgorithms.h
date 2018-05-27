#pragma once
#include <vector>
#include <bitset>
#include <iostream>
#include <boost\multiprecision\cpp_int.hpp>

namespace boostInt = boost::multiprecision;

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
	boostInt::int256_t powMod128(boostInt::int128_t, boostInt::int128_t, boostInt::int128_t);

	RsaKeys generateKeys(int, int);

	std::vector<short int> xor (const std::vector<short int>& inputVector, const std::vector<short int> keyVector);

	std::vector<short int> encryptRsa8 (const std::vector<short int>& inputData, const short int & e, const short int & n);
	std::vector<short int> decryptRsa8(const std::vector<short int>& inputData, const short int & e, const short int & n);

	std::vector<short int> encryptRsa16(const std::vector<short int>& inputData, const short int & e, const short int & n);
	std::vector<short int> decryptRsa16(const std::vector<short int>& inputData, const short int & e, const short int & n);

	std::vector<short int> encryptRsa128(std::vector<short int> inputData, boostInt::int128_t e, boostInt::int128_t n);
	//std::vector<short int> decryptRsa128(const std::vector<short int>& inputData, const boostInt::int128_t & e, const boostInt::int128_t & n);
};

