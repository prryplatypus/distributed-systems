#ifndef OPERACIONES_STUB_H
#define OPERACIONES_STUB_H


#define OP_ERR -1
#define OP_END 0
#define OP_LIST 1
#define OP_READ 2
#define OP_WRITE 3


class OperacionesStub
{
    int socket = 0;
public:
    OperacionesStub();
    /*int suma(int a, int b);
    char* leeFichero(char* nombre);*/
    ~OperacionesStub();
};

#endif // OPERACIONES_STUB_H
