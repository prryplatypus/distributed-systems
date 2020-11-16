#ifndef OPERACIONES_IMP_H
#define OPERACIONES_IMP_H
#include "operaciones.h"

class operaciones_imp
{
    int client_fd=0;

    operaciones* op;
public:
    operaciones_imp(int socket_fd);
    void recvOp();
    ~operaciones_imp();

    bool salir =false;
};

#endif // OPERACIONES_IMP_H
