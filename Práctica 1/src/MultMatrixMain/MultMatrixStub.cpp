/**
 * Néstor Pérez
 * github.com/prryplatypus
 */
#include "MultMatrixStub.h"
#include <iostream>


MultMatrixStub::MultMatrixStub(char* host, int port) : MyConnection(host, port)
{
	receive(&(this->id));
	std::cout << "Client connected. Assigned ID: " << this->id << "." << std::endl;
}


matrix_t* MultMatrixStub::readMatrix(const char* filename)
{
	return mm.readMatrix(filename);
}


matrix_t* MultMatrixStub::multMatrices(matrix_t* m1, matrix_t* m2)
{
	matrix_t* result = new matrix_t[1];

	send(OP_MULT);
	send(m1);
	send(m2);
	receive(result);

	return result;
}


void MultMatrixStub::writeMatrix(matrix_t* m, const char* filename)
{
	return mm.writeMatrix(m, filename);
}


matrix_t* MultMatrixStub::createIdentity(int rows, int cols)
{
	matrix_t* result = new matrix_t[1];

	send(OP_IDENT);
	send(rows);
	send(cols);
	receive(result);

	return result;
}


matrix_t* MultMatrixStub::createRandMatrix(int rows, int cols)
{
	matrix_t* result = new matrix_t[1];

	send(OP_RAND);
	send(rows);
	send(cols);
	receive(result);

	return result;
}


MultMatrixStub::~MultMatrixStub()
{
	send(OP_END);
}
