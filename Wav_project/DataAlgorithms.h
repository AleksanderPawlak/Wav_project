#pragma once
#include <vector>
#include <complex>

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

typedef std::vector<std::complex<double>> ComplexVec;

void fft(ComplexVec& array);

void reverseFft(ComplexVec& inputVec);

ComplexVec doubleToComplexVector(std::vector<double> inputV);

void handleWindow(sf::RenderWindow& window);

void DisplayComplexVector(ComplexVec inputVec, std::string filename, int size);
