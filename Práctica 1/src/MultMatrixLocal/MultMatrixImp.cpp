/**
 * Néstor Pérez
 * github.com/prryplatypus
 */
#include <iostream>
#include <cstring>
#include "MultMatrixImp.h"
#include "MultMatrixStub.h" // Contains OP_TYPEs

MultMatrixImp::MultMatrixImp(ClientConnection* cli_conn)
{
    terminate = false;
    this->cli_conn = cli_conn;
    mm = new multMatrix();
}


void MultMatrixImp::handleRequest()
{
    int type_op;
    cli_conn->receive(&type_op);

    switch (type_op)
    {
        case OP_END: {
            terminate = true;
            break;
        }

        case OP_MULT: {
            matrix_t* matrix1 = new matrix_t[1];
            matrix_t* matrix2 = new matrix_t[1];
            
            // Receive Matrices
            cli_conn->receive(matrix1);
            cli_conn->receive(matrix2);

            // Calculate result
            matrix_t* result = mm->multMatrices(matrix1, matrix2);
            delete[] matrix1->data;
            delete[] matrix1;
            delete[] matrix2->data;
            delete[] matrix2;

            // Send result
            cli_conn->send(result);
            delete[] result->data;
            delete[] result;

            break;
        }

        case OP_RAND: {
            int rows, cols;

            cli_conn->receive(&rows);
            cli_conn->receive(&cols);

            matrix_t* rand_matrix = mm->createRandMatrix(rows, cols);
            cli_conn->send(rand_matrix);

            delete[] rand_matrix->data;
            delete[] rand_matrix;
            break;
        }

        case OP_IDENT: {
            int rows, cols;

            cli_conn->receive(&rows);
            cli_conn->receive(&cols);

            matrix_t* ident_matrix = mm->createIdentity(rows, cols);
            cli_conn->send(ident_matrix);

            delete[] ident_matrix->data;
            delete[] ident_matrix;
            break;
        }

        case OP_READ: {
            char* filename;
            unsigned long data_len;

            cli_conn->receive(filename, data_len);
            matrix_t* matrix = mm->readMatrix(filename);
            cli_conn->send(matrix);

            delete[] matrix->data;
            delete[] matrix;
            break;
        }

        case OP_WRITE: {
            char* filename;
            unsigned long data_len;
            matrix_t* matrix = new matrix_t[1];

            cli_conn->receive(filename, data_len);
            cli_conn->receive(matrix);

            mm->writeMatrix(matrix, filename);

            delete[] filename;
            delete[] matrix->data;
            delete[] matrix;
            break;
        }

        default: {
            std::cout << "ERROR: Unknown operation type (" << type_op << ") on line " << __LINE__ << std::endl;
            int op = OP_ERR;
            cli_conn->send(op);
        }
    }
}


MultMatrixImp::~MultMatrixImp()
{
    delete mm;
}
