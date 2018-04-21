#pragma once
#include <vector>

struct RsaKeys
{
	int privateKey;
	int publicKey;
	int modulKey;
};

class EncryptionAlgorithms
{
private:
	bool isPrime(int);
	int nwd(int, int);
	int inverseModulo(int, int);

public:
	std::vector<int> xor (const std::vector<int>& inputVector, const std::vector<int> keyVector);

	RsaKeys generateKeys(int, int);
	//static std::vector<int> encryptRsa (const std::vector<int>& inputVector, const int& p, const int& q);
	//static std::vector<int> decryptRsa(const std::vector<int>& inputVector);

	EncryptionAlgorithms();
	~EncryptionAlgorithms();
};

