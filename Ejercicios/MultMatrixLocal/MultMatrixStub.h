#ifndef MULTMATRIX_STUB_H
#define MULTMATRIX_STUB_H

#include "MyConnection.h"
#include "multmatrix.h"

#define OP_ERR -1
#define OP_END 0
#define OP_MULT 1
#define OP_RAND 2
#define OP_IDENT 3
#define OP_READ 4
#define OP_WRITE 5

using namespace std;


class MultMatrixStub : protected MyConnection
{
    int id;
    multMatrix mm; // Para las operaciones locales
public:
	MultMatrixStub(char *host, int port);
    matrix_t* readMatrix(const char* filename);
    matrix_t* multMatrices(matrix_t* m1, matrix_t* m2);
    void writeMatrix(matrix_t* m, const char* filename);
    matrix_t* createIdentity(int rows, int cols);
    matrix_t* createRandMatrix(int rows, int cols);
    ~MultMatrixStub();
};

#endif // MULTMATRIX_STUB_H
