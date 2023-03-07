#include <iostream>
#include <fstream>
#include "Fractal.hpp"

Fractal::Fractal() :cols(0), rows(0), grid(nullptr) {
	cout << "> Default constructor called..." << endl;
}
Fractal::Fractal(const Fractal& f) {
	cout << "> Copy constructor called..." << endl;
	this->cols = f.cols;
	this->rows = f.rows;
	grid = new Pixel * [rows];
	
	
	for (unsigned int i = 0; i < rows; i++) {
		grid[i] = new Pixel[cols];

		
		for (unsigned int x = 0; x < cols; x++) {
			grid[i][x] = f.grid[i][x];
		}
	}

	//just a copy constructor. It did not work earlier because the default constructor was called and all values were assigned to 0 and never modified after that.
	//That is why it the second image was all black.
	
}
Fractal::Fractal(Fractal&& f) {
	cout << "> Move constructor called..." << endl;
	this->cols = f.cols;
	this->rows = f.rows;
	this->grid = f.grid;
	f.grid = nullptr;
}
Fractal::Fractal(unsigned int r, unsigned int c) :rows(r), cols(c) {
	cout << "> Two-arg constructor called..." << endl;
	grid = new Pixel * [rows];
	for (unsigned int i = 0; i < rows; i++)
		grid[i] = new Pixel[cols];
	makeNewtonFractal();
}
Fractal::~Fractal() {
	cout << ">Destructor called..." << endl;
	for (unsigned int i = 0; i < rows; i++) {
		delete[] grid[i];
		grid[i] = nullptr;
	}
	delete[] grid;
	grid = nullptr;
}
Pixel Fractal::determinePixelColor(Complex Z) {
	double tol = 1E-4, diff = 1.0, test = 0.58974;
	unsigned int iter = 0, color = 0;
	Complex Znew;
	while (iter < 512) {
		iter++;
		Znew = Z - ((Z * Z * Z) - (2.0 * Z) + 2.0) / ((3.0 * Z * Z) - 2.0);
		diff = getMagnitude(Z - Znew);
		Z = Znew;
		if (diff < tol) {
			color = maxIter - min(iter, maxIter);
			if (abs(Z["imag"]) < tol)
				return Pixel(color, color, 0);
			else if (abs(Z["imag"] - test) < tol)
				return Pixel(0, color, color);
			else if (abs(Z["imag"] + test) < tol)
				return Pixel(color, 0, color);
		}
	}
	return Pixel(0, 0, 0);
}
void Fractal::makeNewtonFractal() {
	cout << "> Now creating the Newton Fractal..." << endl;
	Complex Z;
	double height = 4.0 / rows;
	double width = 4.0 / cols;
	for (unsigned int j = 0; j < rows; j++) {
		for (unsigned int k = 0; k < cols; k++) {
			Z["imag"] = 2.0 - (j * height);
			Z["real"] = (k * width) - 2.0;
			grid[j][k] = determinePixelColor(Z);
		}
	}
}
const Fractal& Fractal::operator=(const Fractal& f) {
	if (this != &f) {
		if (this->grid != nullptr) {
			for (unsigned int i = 0; i < rows; i++) {
				delete[] grid[i];
				grid[i] = nullptr;
			}
			delete[] grid;
			grid = nullptr;
		}
		this->cols = f.cols;
		this->rows = f.rows;
		grid = new Pixel * [rows];
		for (unsigned int i = 0; i < rows; i++) {
			grid[i] = new Pixel[cols];
			for (unsigned int j = 0; j < cols; j++)
				grid[i][j] = f.grid[i][j];
		}
	}
	return *this;
}
Fractal& Fractal::operator=(Fractal&& f) {
	cout << "> Move assignment operator called..." << endl;
	if (this != &f) {
		swap(this->grid, f.grid);
		swap(this->cols, f.cols);
		swap(this->rows, f.rows);
	}
	return *this;
}
void saveToPPM(const Fractal& f, string fileName) {
	cout << "> Saving Fractal object to PPM file..." << endl;
	ofstream output;
	output.open(fileName);
	output << "P3\n"
		<< "# " << fileName << '\n'
		<< f.rows << " " << f.cols << '\n'
		<< f.maxIter << '\n';
	for (unsigned int i = 0; i < f.rows; i++) {
		for (unsigned int j = 0; j < f.cols; j++)
			output << f.grid[i][j] << " ";
		output << '\n';
	}
	output.close();
}