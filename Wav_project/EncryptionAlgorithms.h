#pragma once
#include <vector>

class EncryptionAlgorithms
{
public:
	static std::vector<int> xor (const std::vector<int>& inputVector, const std::vector<int> keyVector);

	//static std::vector<int> encryptRsa (const std::vector<int>& inputVector, const int& p, const int& q);
	//static std::vector<int> decryptRsa(const std::vector<int>& inputVector);

	EncryptionAlgorithms();
	~EncryptionAlgorithms();
};

