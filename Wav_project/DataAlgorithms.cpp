#include "stdafx.h"
#include "DataAlgorithms.h"

#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <complex>
#include <SFML\Graphics.hpp>

#define PI std::atan(1.0)*4

void fft(ComplexVec& inputVector)
{
	const int size = inputVector.size();

	if (size <= 1)
	{
		return;
	}

	ComplexVec even, odd;
	bool isEven = false;

	std::partition_copy(inputVector.begin(), inputVector.end(), std::back_inserter(even), std::back_inserter(odd),
		[&isEven](std::complex<double>) {return isEven = !isEven; });

	fft(odd);
	fft(even);

	for (int i{}; i < size / 2; i++)
	{
		std::complex<double> e = std::polar(1.0, ((-2.0 * PI) / size)* i) * odd[i];

		inputVector[i] = even[i] + e;
		inputVector[i + size / 2] = even[i] - e;
	}
}

void reverseFft(ComplexVec& inputVec)
{
	for (auto& value : inputVec)
		value = std::conj(value);

	fft(inputVec);

	for (auto& value : inputVec)
		value = std::conj(value);

	for (auto& value : inputVec)
		value = value / std::complex<double>(inputVec.size());
}

ComplexVec doubleToComplexVector(std::vector<double> inputV)
{
	ComplexVec outputVec;

	outputVec.reserve(inputV.size());

	for (auto doubleValue : inputV)
	{
		outputVec.push_back(std::complex<double>(doubleValue, 0.0));
	}

	return std::move(outputVec);
}

void handleWindow(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}

void DisplayComplexVector(ComplexVec inputVec, std::string filename, int size)
{
	std::string windowName = "fft for " + filename;

	if (size == -1)
	{
		size = inputVec.size();
	}

	float width(2000), height(2000), Xzero(height / 2), Xstart(0);
	float yScale, areaHeight(height - Xzero - 100);

	std::complex<double> maxValue = *std::max_element(inputVec.begin(), inputVec.end(), 
			[](std::complex<double> left, std::complex<double> right) {return left.real() > right.real(); });

	yScale = areaHeight / maxValue.real();
	float sampleWidth(width / size);


	sf::RectangleShape* line;
	line = new sf::RectangleShape[size];

	for (int i{}; i < size; i++)
	{
		line[i] = sf::RectangleShape(sf::Vector2f(inputVec[i].real()*yScale, sampleWidth));
		line[i].move(sf::Vector2f(Xstart + (i * sampleWidth), Xzero - inputVec[i].real()*yScale));
		line[i].rotate(90);
	}

	sf::RectangleShape axis(sf::Vector2f(width, 2));
	axis.move(sf::Vector2f(0, Xzero));
	axis.setFillColor(sf::Color::Yellow);

	sf::RenderWindow window(sf::VideoMode(height, width), windowName, sf::Style::Default);

	window.clear();

	for (int i{}; i < size; i++)
	{
		window.draw(line[i]);
	}

	window.draw(axis);
	window.display();

	handleWindow(window);

	delete[] line;
}

