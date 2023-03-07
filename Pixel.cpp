#include <iostream>
#include "Pixel.hpp"
using namespace std;

Pixel::Pixel() :blue(0), green(0), red(0) {
}
Pixel::Pixel(const Pixel& p) {
	this->red = p.red;
	this->green = p.green;
	this->blue = p.blue;
}
Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b) :red(r), green(g), blue(b) {
}
Pixel::~Pixel() {
}
const unsigned int& Pixel::operator[](const char* t) {
	if (t == "red")
		return this->red;
	else if (t == "green")
		return this->green;
	else if (t == "blue")
		return this->blue;
	else {
		InputOutOfBoundsException e("ERROR: Invalid pixel input argument.", "err2");
		throw e;
	}
}
//implement exceptions
ofstream& operator<<(ofstream& os, const Pixel& p) {
	try {
		os << p.red << " " << p.green << " " << p.blue;
	}
	catch (InputOutOfBoundsException e) {
		cout << e.returnError();
	}
	return os;
}