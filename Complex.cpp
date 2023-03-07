#include <iostream>
#include "Complex.hpp"

Complex::Complex() :imag(0), real(0) {
}
Complex::Complex(const Complex& c) {
	this->real = c.real;
	this->imag = c.imag;
}
Complex::Complex(double d) {
	real = d;
	imag = 0;
}
Complex::Complex(double d1, double d2) {
	real = d1;
	imag = d2;
}
Complex::~Complex() {
}
double& Complex::operator[](const char* temp) {
	if (temp == "real")
		return this->real;
	else if (temp == "imag")
		return this->imag;
	else {
		InputOutOfBoundsException e("ERROR: Invalid complex input argument.", "err1");
		throw e;
	}
}
const Complex operator*(const Complex& c1, const Complex& c2) {
	Complex temp;
	temp["real"] = c1.real * c2.real - c1.imag * c2.imag;
	temp["imag"] = c1.real * c2.imag + c1.imag * c2.real;
	return temp;
}
const Complex operator/(const Complex& c1, const Complex& c2) {
	Complex temp;
	temp["real"] = (c1.real * c2.real + c1.imag * c2.imag)
		/ (c2.real * c2.real + c2.imag * c2.imag);
	temp["imag"] = (c1.imag * c2.real - c1.real * c2.imag)
		/ (c2.real * c2.real + c2.imag * c2.imag);
	return temp;
}
const Complex operator+(const Complex& c1, const Complex& c2) {
	Complex temp;
	temp["real"] = c1.real + c2.real;
	temp["imag"] = c1.imag + c2.imag;
	return temp;
}
const Complex operator-(const Complex& c1, const Complex& c2) {
	Complex temp;
	temp["real"] = c1.real - c2.real;
	temp["imag"] = c1.imag - c2.imag;
	return temp;
}
double getMagnitude(const Complex& c) {
	return sqrt(c.real * c.real + c.imag * c.imag);
}