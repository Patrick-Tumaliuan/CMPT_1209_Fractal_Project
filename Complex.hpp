#pragma once

class Complex {
private:
	double imag;
	double real;
public:
	Complex();
	Complex(const Complex&);
	Complex(double);
	Complex(double, double);
	~Complex();
	double& operator[](const char*);
	friend const Complex operator*(const Complex&, const Complex&);
	friend const Complex operator/(const Complex&, const Complex&);
	friend const Complex operator+(const Complex&, const Complex&);
	friend const Complex operator-(const Complex&, const Complex&);
	friend double getMagnitude(const Complex&);
};

class InputOutOfBoundsException {
private:
	const char* errorMessage;
	const char* offendingIndex;
public:
	InputOutOfBoundsException(const char* msg, const char* index) {
		errorMessage = msg;
		offendingIndex = index;
	}
	const char* returnError() {
		return errorMessage;
	}
	const char* returnOffendingIndex() {
		return offendingIndex;
	}
};