#include "stdafx.h"
#include "Menu.h"
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <string>
#include <thread>

#include <SFML\Audio.hpp>
#include "DataAlgorithms.h"
#include "EncryptionAlgorithms.h"


void Menu::showDataValues()
{
	auto data = decoder.getAudioData();

	if (data.size() > 20)
	{
		for (int i{}; i < 20; i++)
			std::cout << data[i] << "  ";
		std::cout << std::endl;
	}
	else
	{
		for (auto value : data)
			std::cout << value << "  ";
		std::cout << std::endl;
	}
	std::system("pause");
}

void Menu::loadFile()
{
	std::string filename;

	std::cout << "Prosze podac nazwe pliku.\n";

	std::cin >> filename;

	try
	{
		decoder.readFile(filename);
	}
	catch(const std::exception& e)
	{
		std::cout << "Nie wczytano pliku\n";
		std::cout << "error: " << e.what() << std::endl;
		std::system("pause");
	}
}

void Menu::playFile()
{
	sf::SoundBuffer buffer;
	sf::Sound player;
	std::vector<short int> data = decoder.getAudioData();

	buffer.loadFromSamples(&data[0], data.size(), decoder.getChannelsNumber(), decoder.getWavHeader().sampleRate);

	player.setBuffer(buffer);
	player.play();

	std::cout << "Nacisnij dowolny przycisk aby zatrzymac.\n";
	std::getchar();

	player.stop();
}

void Menu::SaveFile()
{
	std::string filename;

	std::cout << "Prosze podac nazwe pliku.\n";
	std::cin >> filename;

	decoder.writeToFile(filename);
}

void Menu::displayFileFFT()
{
	std::string response;
	std::vector<double> doubleData;
	auto data = decoder.getAudioData();

	if (decoder.getChannelsNumber() == 1)
	{
		doubleData = std::vector<double>(data.begin(), data.end());
	}
	else
	{
		for (auto value : data)
		{
			char valueBits8[] = { static_cast<char>(value), static_cast<char>(value >> 8) };
			doubleData.push_back(valueBits8[0]);
		}
	}

	auto complexData = doubleToComplexVector(doubleData);
	fft(complexData);

	std::thread display(DisplayComplexVector, complexData, "", -1);

	std::cout << "pierwsze 10 probek z fft dla danych:\n";
	for (int i{}; i < 10; i++)
		std::cout << complexData[i] << "  ";
	std::cout << std::endl;
	std::system("pause");

	if (display.joinable())
	{
		display.join();
	}

	std::cout << "Czy chcesz wyswietlic odwrotna transformate?(Y)\n";
	std::cin >> response;

	if (response == "Y" || response == "y")
	{
		reverseFft(complexData);

		std::thread display(DisplayComplexVector, complexData, "", -1);
		std::system("pause");

		if (display.joinable())
		{
			display.join();
		}
	}
}

void Menu::displayFileData()
{
	std::string response;
	std::vector<double> doubleData;
	auto data = decoder.getAudioData();

	if (decoder.getChannelsNumber() == 1)
	{
		doubleData = std::vector<double>(data.begin(), data.end());
	}
	else
	{
		for (auto value : data)
		{
			char valueBits8[] = { static_cast<char>(value), static_cast<char>(value >> 8) };
			doubleData.push_back(valueBits8[0]);
		}
	}

	auto complexData = doubleToComplexVector(doubleData);
	std::thread display(DisplayComplexVector, complexData, "", -1);

	std::system("pause");

	if (display.joinable())
	{
		display.join();
	}
}

void Menu::encryptData()
{
	bool running{ true };
	int choice;
	DecoderMenu decMenu;

	std::vector<std::pair<std::string, std::function<void(WavDecoder&)>>> options{
		{ "Zaszyfruj 8 bitowym algorytmem RSA", std::bind(&DecoderMenu::doRSA, decMenu, std::placeholders::_1) },
		{ "Odszyfruj 8 bitowym algorytmem RSA", std::bind(&DecoderMenu::revertRSA, decMenu, std::placeholders::_1) },
		{ "Uzyj algorytmu XOR", std::bind(&DecoderMenu::doXOR, decMenu, std::placeholders::_1) }
	};

	while (running)
	{
		std::cout << "Prosze wybrac opcjê:\n";

		for (int i{}; i < options.size(); i++)
		{
			std::cout << i << ". " << options[i].first << std::endl;
		}

		std::cout << options.size() << ". Wroc do menu glownego.\n";

		std::cin >> choice;

		if (choice >= 0 && choice < options.size())
		{
			options[choice].second(decoder);
		}
		else
		{
			if (choice == options.size())
				running = false;
			else
				std::cout << "Niepoprawny wybor, sprobuj ponownie.\n";
		}

		std::system("cls");
	}
}

void Menu::displayHeaderBasics()
{
	auto properties = decoder.getWavHeader();

	std::cout << "Czestotliwosc:  " << properties.sampleRate << std::endl;
	std::cout << "Liczba probek:  " << decoder.getNumberOfSamples() << std::endl;
	std::cout << "Liczba kanalow: " << decoder.getChannelsNumber() << std::endl;
	std::cout << "Liczba bitow na probke: " << properties.bitsPerSample << std::endl << std::endl;

	std::system("pause");
}

void Menu::runMenu()
{
	std::vector<std::pair<std::string, std::function<void()>>> options{
		{ "wczytaj plik", std::bind(&Menu::loadFile, this) },
		{ "odtworz wczytany plik", std::bind(&Menu::playFile, this) },
		{ "Zapisz dane do pliku", std::bind(&Menu::SaveFile, this) },
		{ "Wyswietl szczegoly pliku", std::bind(&Menu::displayHeaderBasics, this) },
		{ "Wyswietl FFT pliku", std::bind(&Menu::displayFileFFT, this) },
		{ "Wyswietl zawartosc pliku", std::bind(&Menu::displayFileData, this) },
		{ "Szyfruj zawartosc pliku", std::bind(&Menu::encryptData, this) },
		{ "Wyswietl pierwsze wartosci danych z pliku", std::bind(&Menu::showDataValues, this) }
	};

	bool running{ true };
	int choice;

	while (running)
	{
		std::cout << "Prosze wybrac opcjê:\n";

		for (int i{}; i < options.size(); i++)
		{
			std::cout << i << ". " << options[i].first << std::endl;
		}

		std::cout << options.size() << ". Zakoncz.\n";

		std::cin >> choice;

		if (choice >= 0 && choice < options.size())
		{
			options[choice].second();
		}
		else
		{
			if (choice == options.size())
				running = false;
			else
				std::cout << "Niepoprawny wybor, sprobuj ponownie.\n";
		}

		std::system("cls");
	}
}

void DecoderMenu::doRSA(WavDecoder & decoder)
{
	int e, n;
	auto data = decoder.getAudioData();

	std::cout << "Podaj kolejne wartoœci kluczy RSA:\n";
	std::cout << "e: ";
	std::cin >> e;
	std::cout << "n: ";
	std::cin >> n;

	auto enc = EncryptionAlgorithms::encryptRsa8(data, e, n);

	this->handleEncryptionResult(decoder, enc);
}

void DecoderMenu::revertRSA(WavDecoder & decoder)
{
	int d, n;
	auto data = decoder.getAudioData();

	std::cout << "Podaj kolejne wartoœci kluczy RSA:\n";
	std::cout << "d: ";
	std::cin >> d;
	std::cout << "n: ";
	std::cin >> n;

	auto dec = EncryptionAlgorithms::decryptRsa8(data, d, n);

	this->handleEncryptionResult(decoder, dec);
}

void DecoderMenu::doXOR(WavDecoder & decoder)
{
	int size;
	short int key;
	std::vector<short int> keys;
	auto data = decoder.getAudioData();

	std::cout << "Podaj ilosc kluczy do szyfrowania: ";
	std::cin >> size;
	for (int i{}; i < size; i++)
	{
		std::cout << "klucz: ";
		std::cin >> key;
		keys.push_back(key);
	}

	auto dec = EncryptionAlgorithms:: xor (data, keys);

	this->handleEncryptionResult(decoder, dec);
}

void DecoderMenu::handleEncryptionResult(WavDecoder & decoder, std::vector<short int>& dataVector)
{
	int choice{};

	while (choice != 3)
	{
		std::cout << "Wybierz co chcesz zrobic.\n";
		std::cout << "1. Podmien obslugiwane dane na dane zaszyfrowane.\n";
		std::cout << "2 wyswietl wartosci zaszyfrowanych danych.\n";
		std::cout << "3. wracam do glownego menu.\n";

		std::cin >> choice;

		if (choice == 1)
		{
			decoder.setData(dataVector);
		}
		else if (choice == 2)
		{
			if (dataVector.size() > 20)
			{
				for (int i{}; i < 20; i++)
					std::cout << dataVector[i] << "   ";
				std::cout << std::endl;
			}
			else
			{
				for (auto value : dataVector)
					std::cout << value << "   ";
				std::cout << std::endl;
			}
		}
		else if(choice != 3)
		{
			std::cout << "Niepoprawna opcja.\n";
		}

		std::system("pause");
		std::system("cls");
	}
}
