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

EncryptionAlgorithms::EncryptionAlgorithms()
{
}

EncryptionAlgorithms::~EncryptionAlgorithms()
{
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
