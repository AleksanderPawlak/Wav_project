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

std::vector<int> EncryptionAlgorithms:: xor (const std::vector<int>& inputVector, const std::vector<int> keyVector)
{
	std::vector<int> encryptedData;
	encryptedData.reserve(inputVector.size());

	int i{};

	for (auto value : inputVector)
	{
		if (i == keyVector.size())
			i = 0;

		int encrypted = value ^ keyVector[i];
		encryptedData.push_back(encrypted);

		i++;
	}

	return encryptedData;
}

std::vector<short int> EncryptionAlgorithms::Rsa8(const std::vector<short int>& inputData, const int & e, const int & n)
{
	std::vector<short int> encryptionResult;
	encryptionResult.reserve(inputData.size());

	for (auto value : inputData)
	{
		uint8_t valueBits[] = {value, value >> 8};
		short int encryptedValue;

		valueBits[0] = (uint8_t)powMod(valueBits[0], e, n);
		valueBits[1] = (uint8_t)powMod(valueBits[1], e, n);

		std::memcpy(&encryptedValue, &valueBits, sizeof(short int));
		encryptionResult.push_back(encryptedValue);
	}

	return std::move(encryptionResult);
}
