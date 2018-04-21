#include "stdafx.h"
#include "EncryptionAlgorithms.h"


std::vector<int> EncryptionAlgorithms::xor(const std::vector<int>& inputVector, const std::vector<int> keyVector)
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

EncryptionAlgorithms::EncryptionAlgorithms()
{
}


EncryptionAlgorithms::~EncryptionAlgorithms()
{
}
