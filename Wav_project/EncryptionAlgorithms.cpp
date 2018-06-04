#include "stdafx.h"
#include "EncryptionAlgorithms.h"
#include <boost\random.hpp>
#include <boost\generator_iterator.hpp>
#include <boost\math\common_factor_rt.hpp>


bool EncryptionAlgorithms::isPrime(int number)
{
	for (int i{2}; i < number; i++) 
	{
		if (number % i == 0)
			return false;
	}

	return true;
}

int EncryptionAlgorithms::powMod(int value, int pow, int m)
{
	int pot, result, q;
	pot = value; result = 1; 

	for (q = pow; q > 0; q /= 2)
	{
		if (q % 2) result = (result * pot) % m;
		pot = (pot * pot) % m;
	}

	return result;
}

boostInt::int128_t EncryptionAlgorithms::random128Value()
{
	boost::mt19937 rng;
	boost::uniform_int<uint64_t> UInt64Range(1, std::numeric_limits<uint64_t>::max());
	boost::variate_generator< boost::mt19937, boost::uniform_int<uint64_t>> generator(rng, UInt64Range);

	boostInt::int128_t int64left = generator();
	boostInt::int128_t int64right = generator();

	boostInt::int128_t randomInt = int64left << 64 | int64right;

	return randomInt;
}

bool EncryptionAlgorithms::isPrime128(boostInt::int128_t number)
{
	boostInt::int128_t i;
	i.assign("18446744073709551617");
	for (; i < number; i++)
	{
		if (number % i == 0)
			return false;
	}

	return true;
}

boostInt::int512_t EncryptionAlgorithms::powMod128(boostInt::int512_t value, boostInt::int256_t pow, boostInt::int256_t m)
{
	boostInt::int512_t pot, result, q;
	pot = value; result = 1;

	for (q = pow; q > 0; q /= 2)
	{
		if (q % 2) result = (result * pot) % m;
		pot = (pot * pot) % m;
	}

	return result;
}

std::pair<boostInt::int128_t, boostInt::int128_t> EncryptionAlgorithms::Prime128Random()
{
	std::pair<boostInt::int128_t, boostInt::int128_t> result;

	do
	{
		result.first = random128Value();
		std::cout << result.first << std::endl;
		if (!isPrime128(result.first))
			result.first = 0;

		result.second = random128Value();
		if (!isPrime128(result.second))
			result.second = 0;
	} 
	while (result.first == result.second || result.first == 0 || result.second == 0);

	return result;
}

RsaKeys<int> EncryptionAlgorithms::generateKeys(int p, int q)
{	
	RsaKeys<int> result;

	int phi = (p - 1) * (q - 1);

	result.modulKey = p * q;

	for (int i{ 3 }; i < result.modulKey; i++)
	{
		if (boost::math::gcd(i, phi) == 1)
		{
			result.publicKey = i;
			result.privateKey = inverseModulo(i, phi);
			break;
		}
	}

	return result;
}

RsaKeys<boostInt::int256_t> EncryptionAlgorithms::generateKeys256(boostInt::int256_t p, boostInt::int256_t q)
{
	RsaKeys<boostInt::int256_t> result;

	boostInt::int256_t phi = (p - 1) * (q - 1);

	result.modulKey = p * q;

	boostInt::int256_t i = phi - 1;
	for (; i > 0; i--)
	{
		if (boost::math::gcd(i, phi) == 1 && i != phi)
		{
			result.publicKey = i;
			result.privateKey = inverseModulo(i, phi);
			break;
		}
	}

	return result;
}

std::vector<short int> EncryptionAlgorithms:: xor (const std::vector<short int>& inputVector,
	const std::vector<short int> keyVector)
{
	std::vector<short int> encryptedData;
	encryptedData.reserve(inputVector.size());

	for (int i{}, j{}; i < inputVector.size(); i++, j++)
	{
		if (j == keyVector.size())
			j = 0;

		short int encryptedValue = inputVector[i] ^ keyVector[j];
		encryptedData.push_back(encryptedValue);
	}

	return encryptedData;
}

std::vector<short int> EncryptionAlgorithms::encryptRsa8(const std::vector<short int>& inputData, const short int & e, const short int & n)
{
	std::vector<short int> encryptionResult;
	encryptionResult.reserve(inputData.size());

	for (auto value : inputData)
	{
		uint8_t valueBits8[] = {static_cast<uint8_t>(value), static_cast<uint8_t>(value >> 8)};
		short int valueBits16[2];
		short int encryptedValue;

		valueBits16[0] = (short int)powMod(valueBits8[0], e, n);
		valueBits16[1] = (short int)powMod(valueBits8[1], e, n);

		encryptionResult.push_back(valueBits16[0]);
		encryptionResult.push_back(valueBits16[1]);
	}

	return std::move(encryptionResult);
}

std::vector<short int> EncryptionAlgorithms::decryptRsa8(const std::vector<short int>& inputData, const short int & e, const short int & n)
{
	std::vector<short int> encryptionResult;
	encryptionResult.reserve(inputData.size());

	for (int i{}; i < inputData.size(); i += 2)
	{
		short int valueBits16[] = { inputData[i], inputData[i + 1] };
		uint8_t valueBits8[2];
		short int encryptedValue;

		valueBits8[0] = (uint8_t)powMod(valueBits16[0], e, n);
		valueBits8[1] = (uint8_t)powMod(valueBits16[1], e, n);

		std::memcpy(&encryptedValue, &valueBits8, sizeof(short int));
		encryptionResult.push_back(encryptedValue);
	}

	return std::move(encryptionResult);
}

std::vector<short int> EncryptionAlgorithms::encryptRsa128(std::vector<short int> inputData, boostInt::int256_t e, boostInt::int256_t n)
{
	std::vector<short int> result;
	result.reserve(inputData.size() * 2);

	if (inputData.size() % 8 != 0)
	{
		int missingSpace = 8 - inputData.size() % 8;
		for (int i{}; i < missingSpace; i++)
			inputData.push_back(0);
	}

	for (int i{}; i < inputData.size(); i += 8)
	{
		std::vector<short int> tmpVec;
		boostInt::int128_t dataBlock;

		for (int j{}; j < 8; j++)
			tmpVec.push_back(inputData[i + j]);

		boostInt::import_bits(dataBlock, tmpVec.begin(), tmpVec.end(), 16);
		boostInt::int512_t encryptedBlock = powMod128(dataBlock, e, n);
		boostInt::export_bits(encryptedBlock, std::back_inserter(result), 16);
	}
	
	return result;
}

std::vector<short int> EncryptionAlgorithms::decryptRsa128(std::vector<short int> inputData, const boostInt::int256_t & e, const boostInt::int256_t & n)
{
	std::vector<short int> result;
	result.reserve(inputData.size() / 2);

	if (inputData.size() % 16 != 0)
	{
		int missingSpace = 16 - inputData.size() % 16;
		for (int i{}; i < missingSpace; i++)
			inputData.push_back(0);
	}
	std::cout << inputData.size() << std::endl;
	for (int i{}; i < inputData.size(); i += 16)
	{
		std::vector<short int> tmpVec;
		boostInt::int256_t dataBlock;

		for (int j{}; j < 16; j++)
		{
			tmpVec.push_back(inputData[i + j]);
		}
		boostInt::import_bits(dataBlock, tmpVec.begin(), tmpVec.end(), 16);
		boostInt::int512_t decryptedBlock = powMod128(dataBlock, e, n);
		boostInt::export_bits(decryptedBlock, std::back_inserter(result), 16);
	}

	while (result.back() == 0)
		result.pop_back();

	return result;
}

