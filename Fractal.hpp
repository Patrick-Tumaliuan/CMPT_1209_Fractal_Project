#pragma once
#include "Pixel.hpp"
#include "Complex.hpp"

class Fractal {
private:
	unsigned int cols;
	unsigned int rows;
	Pixel** grid;
	static unsigned int maxIter;
public:
	Fractal();
	Fractal(const Fractal&);
	Fractal(Fractal&&);
	Fractal(unsigned int, unsigned int);
	~Fractal();
	Pixel determinePixelColor(Complex);
	void makeNewtonFractal();
	const Fractal& operator=(const Fractal&);
	Fractal& operator=(Fractal&&);
	friend void saveToPPM(const Fractal&, string);
};