#pragma once
#include <iostream>
#include <fstream>
#include "Complex.hpp"
using namespace std;

class Pixel {
private:
	unsigned int blue;
	unsigned int green;
	unsigned int red;
public:
	Pixel();
	Pixel(const Pixel&);
	Pixel(unsigned int, unsigned int, unsigned int);
	~Pixel();
	const unsigned int& operator[](const char*);
	friend ofstream& operator <<(ofstream& os, const Pixel&);
};
