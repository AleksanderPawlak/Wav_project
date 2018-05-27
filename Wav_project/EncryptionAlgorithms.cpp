#include "stdafx.h"
#include "EncryptionAlgorithms.h"

bool EncryptionAlgorithms::isPrime(int number)
{
	for (int i{}; i < number; i++) 
	{
		if (number % i == 0)
			return false;
	}

	return true;
}

int EncryptionAlgorithms::nwd(int a, int b)
{
	while (a != b)
	{
		if (a > b)
			a -= b;
		else
			b -= a;
	}

	return a;
}

int EncryptionAlgorithms::inverseModulo(int a, int b)
{
	a = a%b;
	for (int i{ 1 }; i < b; i++)
		if ((a*i) % b == 1)
			return i;
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

boostInt::int256_t EncryptionAlgorithms::powMod128(boostInt::int128_t value, boostInt::int128_t pow, boostInt::int128_t m)
{
	boostInt::int256_t pot, result, q;
	pot = value; result = 1;

	for (q = pow; q > 0; q /= 2)
	{
		if (q % 2) result = (result * pot) % m;
		pot = (pot * pot) % m;
	}

	return result;
}

RsaKeys EncryptionAlgorithms::generateKeys(int p, int q)
{	
	RsaKeys result;

	int phi = (p - 1) * (q - 1);

	result.modulKey = p * q;

	for (int i{ 3 }; i < result.modulKey; i++)
	{
		if (nwd(i, phi) == 1)
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

std::vector<short int> EncryptionAlgorithms::encryptRsa16(const std::vector<short int>& inputData, const short int & e, const short int & n)
{
	std::vector<short int> encryptionResult;
	encryptionResult.reserve(inputData.size() * 2);

	for (auto value: inputData)
	{
		int encryptedValue = powMod(value, e, n);

		short int encryptedBlock[] = { static_cast<short int>(value), static_cast<short int>(value >> 16) };
		encryptionResult.push_back(encryptedBlock[0]);
		encryptionResult.push_back(encryptedBlock[1]);
	}

	return encryptionResult;
}

std::vector<short int> EncryptionAlgorithms::decryptRsa16(const std::vector<short int>& inputData, const short int & e, const short int & n)
{
	std::vector<short int> encryptionResult;
	encryptionResult.reserve(inputData.size());

	for (int i{}; i < inputData.size(); i += 2)
	{
		int intEncrypted;
		short int valueBits16[] = { inputData[i], inputData[i + 1] };
		std::memcpy(&intEncrypted, &valueBits16, sizeof(int));

		short int decryptedValue = (short int)powMod(intEncrypted, e, n);

		encryptionResult.push_back(decryptedValue);
	}

	return std::move(encryptionResult);
}

std::vector<short int> EncryptionAlgorithms::encryptRsa128(std::vector<short int> inputData, boostInt::int128_t e, boostInt::int128_t n)
{
	std::vector<short int> result;
	result.reserve(inputData.size() * 8);

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
		boostInt::int256_t encryptedBlock = powMod128(dataBlock, e, n);
		boostInt::export_bits(encryptedBlock, std::back_inserter(result), 16);
	}

	return result;
}
/*
std::vector<short int> EncryptionAlgorithms::decryptRsa128(const std::vector<short int>& inputData, const boostInt::int128_t & e, const boostInt::int128_t & n)
{
	return std::vector<short int>();
}*/
