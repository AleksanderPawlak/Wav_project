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

struct RsaKeys128
{
	boostInt::int128_t privateKey;
	boostInt::int128_t publicKey;
	boostInt::int128_t modulKey;
};

struct RsaKeys256
{
	boostInt::int256_t privateKey;
	boostInt::int256_t publicKey;
	boostInt::int256_t modulKey;
};

namespace EncryptionAlgorithms
{

	bool isPrime(int);
	int nwd(int, int);

	template<typename type>
	type inverseModulo(type, type);

	int powMod(int value, int pow, int m);
	
	boostInt::int128_t random128Value();
	bool isPrime128(boostInt::int128_t);
	//boostInt::int128_t inverseModulo128(boostInt::int128_t, boostInt::int128_t);
	boostInt::int512_t powMod128(boostInt::int512_t, boostInt::int256_t, boostInt::int256_t);
	std::pair<boostInt::int128_t, boostInt::int128_t> Prime128Random();

	//boostInt::int256_t inverseModulo256(boostInt::int256_t, boostInt::int256_t);

	RsaKeys generateKeys(int, int);
	RsaKeys128 generateKeys128(boostInt::int128_t, boostInt::int128_t);
	RsaKeys256 generateKeys256(boostInt::int256_t, boostInt::int256_t);

	std::vector<short int> xor (const std::vector<short int>& inputVector, const std::vector<short int> keyVector);

	std::vector<short int> encryptRsa8 (const std::vector<short int>& inputData, const short int & e, const short int & n);
	std::vector<short int> decryptRsa8(const std::vector<short int>& inputData, const short int & e, const short int & n);

	std::vector<short int> encryptRsa16(const std::vector<short int>& inputData, const short int & e, const short int & n);
	std::vector<short int> decryptRsa16(const std::vector<short int>& inputData, const short int & e, const short int & n);

	std::vector<short int> encryptRsa128(std::vector<short int> inputData, boostInt::int256_t e, boostInt::int256_t n);
	std::vector<short int> decryptRsa128(const std::vector<short int>& inputData, const boostInt::int256_t & e, const boostInt::int256_t & n);

	template<typename type>
	type inverseModulo(type a, type b)
	{
		type b0 = b, t, q;
		type x0 = 0, x1 = 1;

		if (b == 1) return 1;
		while (a > 1) {
			q = a / b;
			t = b, b = a % b, a = t;
			t = x0, x0 = x1 - q * x0, x1 = t;
		}
		if (x1 < 0) x1 += b0;
		return x1;
	}

};
