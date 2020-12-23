/**
 * Néstor Pérez
 * github.com/prryplatypus
 */
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include "MultMatrixStub.h"


void freeMatrix(matrix_t* m) {
	delete[] m->data;
	delete[] m;
}

std::string getInput()
{
	std::string input;
	getline(std::cin, input);
	return input;
}


std::string extractCommand(std::string input)
{
	size_t pos = input.find(' ');
	return (pos != std::string::npos) ? input.substr(0, pos) : input;
}


std::string extractParameters(std::string input)
{
	size_t pos = input.find(' ');
	return (pos != std::string::npos) ? input.substr(pos + 1) : std::string("");
}

int* getNums(int total)
{
	std::string input;
	int* data = new int[total];
	int parsed = 0;

	std::cout << "Enter " << total << " number" << ((total > 1) ? "s: " : ": ");
	while (parsed < total) {
		std::cin >> input;
		try {
			data[parsed] = std::stoi(input);
			++parsed;
		}
		catch (std::invalid_argument) {
			std::cout << "Invalid number (" << input << ")" << std::endl;
		}
	}
	std::cin.get();

	return data;
}


int main()
{
	bool stop = false;
	unsigned last_id = 0;
	std::map<unsigned, matrix_t*> matrices;
	MultMatrixStub* mmatrix = new MultMatrixStub("192.168.1.85", 8081);

	std::cout << "Available commands:" << std::endl;
	std::cout << "\t- create: Creates a matrix of the given size for you to fill in" << std::endl;
	std::cout << "\t- rand: Creates a random matrix of the given size" << std::endl;
	std::cout << "\t- ident: Creates an identity matrix of the given size" << std::endl;
	std::cout << "\t- show: Shows all currently existing matrices and lets you display one" << std::endl;
	std::cout << "\t- mult: Allows you to select 2 matrices and multiply them together" << std::endl;
	std::cout << "\t- load: Allows you to load a matrix from a local file" << std::endl;
	std::cout << "\t- save: Allows you to save a matrix to a local file" << std::endl;
	std::cout << "\t- quit" << std::endl;

	do {
		std::cout << "someone@mycode:$~ ";
		std::string input = getInput();
		std::string command = extractCommand(input);

		if (command == "create") {
			int* size;
			matrix_t* matrix = new matrix_t[1];
			std::cout << "Please select the size of rows and columns. ";
			size = getNums(2);
			matrix->rows = size[0];
			matrix->cols = size[1];
			delete[] size;
			std::cout << "Now fill the matrix in. ";
			matrix->data = getNums(matrix->rows * matrix->cols);
			matrices[last_id++] = matrix;
		}

		else if(command == "rand") {
			int* size;
			matrix_t* matrix;
			std::cout << "Please select the size of rows and columns. ";
			size = getNums(2);
			matrix = mmatrix->createRandMatrix(size[0], size[1]);
			delete[] size;
			matrices[last_id++] = matrix;
		}

		else if (command == "ident") {
			int* size;
			matrix_t* matrix;
			std::cout << "Please select the size of rows and columns. ";
			size = getNums(2);

			matrix = mmatrix->createIdentity(size[0], size[1]);
			delete[] size;
			matrices[last_id++] = matrix;
		}

		else if (command == "show") {
			std::cout << "Currently available matrices:" << std::endl;
			for (auto it = matrices.begin(); it != matrices.end(); ++it)
				std::cout << "\t" << it->first << ". " << it->second->rows << "x" << it->second->cols << std::endl;

			int* choice;
			std::cout << "Select your choice, or a non-existant one to ignore this. ";
			choice = getNums(1);
			if (matrices.find(choice[0]) != matrices.end()) {
				matrix_t* matriz = matrices[choice[0]];
				for (size_t i = 0; i < matriz->rows; ++i) {
					for (size_t j = 0; j < matriz->cols; ++j) {
						std::cout << matriz->data[(i * matriz->cols) + j] << "\t";
					}
					std::cout << std::endl;
				}
			}
			delete[] choice;
		}

		else if (command == "mult") {
			std::cout << "Currently available matrices:" << std::endl;
			for (auto it = matrices.begin(); it != matrices.end(); ++it)
				std::cout << "\t" << it->first << ". " << it->second->rows << "x" << it->second->cols << std::endl;

			int* choices;
			std::cout << "Choose the matrices to multiply together. ";
			choices = getNums(2);

			if (matrices.find(choices[0]) != matrices.end() &&
				matrices.find(choices[0]) != matrices.end())
			{
				matrix_t* matriz = mmatrix->multMatrices(matrices[choices[0]], matrices[choices[1]]);
				for (size_t i = 0; i < matriz->rows; ++i) {
					for (size_t j = 0; j < matriz->cols; ++j) {
						std::cout << matriz->data[(i * matriz->cols) + j] << "\t";
					}
					std::cout << std::endl;
				}
				matrices[last_id++] = matriz;
			}
			delete[] choices;
		}

		else if (command == "load") {
			std::cout << "Please enter file to load: ";
			std::string filename = getInput();
			if (filename.empty()) {
				std::cout << "Filename can't be empty" << std::endl;
				continue;
			}
			matrix_t* matriz = mmatrix->readMatrix(filename.c_str());
			for (size_t i = 0; i < matriz->rows; ++i) {
				for (size_t j = 0; j < matriz->cols; ++j) {
					std::cout << matriz->data[(i * matriz->cols) + j] << "\t";
				}
				std::cout << std::endl;
			}
			matrices[last_id++] = matriz;
		}

		else if (command == "save") {
			std::cout << "Currently available matrices:" << std::endl;
			for (auto it = matrices.begin(); it != matrices.end(); ++it)
				std::cout << "\t" << it->first << ". " << it->second->rows << "x" << it->second->cols << std::endl;

			int* choices;
			std::cout << "Choose the matrix to save. ";
			choices = getNums(1);

			if (matrices.find(choices[0]) != matrices.end())
			{
				std::cout << "Please enter file to save: ";
				std::string filename = getInput();
				if (filename.empty()) {
					std::cout << "Filename can't be empty" << std::endl;
					continue;
				}
				mmatrix->writeMatrix(matrices[choices[0]], filename.c_str());
			}
			delete[] choices;
		}

		else if (command == "quit") {
			stop = true;
		}

		else {
			std::cout << "Unrecognized command." << std::endl;
		}
	} while (stop != true);

	for (auto it = matrices.begin(); it != matrices.end(); ++it) {
		delete[] it->second->data;
		delete[] it->second;
	}
	delete mmatrix;

	return 0;
}
