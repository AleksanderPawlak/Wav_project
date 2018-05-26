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


void Menu::loadFile()
{
	std::string filename;

	std::cout << "Proszê podaæ nazwê pliku.\n";

	std::cin >> filename;

	decoder.readFile(filename);
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

	std::cout << "Proszê podaæ nazwê pliku.\n";
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

	std::system("pause");

	if (display.joinable())
	{
		display.join();
	}

	std::cout << "Czy chcesz wyswietlic odwrotn¹ transformate?(Y/N)\n";
	std::cin >> response;

	if (response == "Y") 
	{
		//fft(complexData);
		reverseFft(complexData);

		std::thread display(DisplayComplexVector, complexData, "", -1);

		std::system("pause");

		if (display.joinable())
		{
			display.join();
		}
	}
}

void Menu::encryptData()
{

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

Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::runMenu()
{
	std::vector<std::pair<std::string, std::function<void()>>> options{
		{ "wczytaj plik", std::bind(&Menu::loadFile, this) },
		{ "odtworz wczytany plik", std::bind(&Menu::playFile, this) },
		{ "Zapisz dane do pliku", std::bind(&Menu::SaveFile, this) },
		{ "Wyswietl szczegoly pliku", std::bind(&Menu::displayHeaderBasics, this) }
	};

	bool running{ true };
	int choice;

	while (running)
	{
		std::cout << "Proszê wybraæ opcjê:\n";

		for (int i{}; i < options.size(); i++)
		{
			std::cout << i << ". " << options[i].first << std::endl;
		}

		std::cout << options.size() << ". Zakoñcz.\n";

		std::cin >> choice;

		if (choice > 0 && choice < options.size())
		{
			options[choice].second();
		}
		else
		{
			if (choice == options.size())
				running = false;
			else
				std::cout << "Niepoprawny wybór, spróbuj ponownie.\n";
		}

		std::system("cls");
	}
}
