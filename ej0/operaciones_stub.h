#ifndef OPERACIONES_STUB_H
#define OPERACIONES_STUB_H

#define OP_END 0
#define OP_SUMA 1
#define OP_FICHERO 2


class operaciones_stub
{
    int socket=0;
public:
    operaciones_stub();
    int suma(int a, int b);
    char* leeFichero(char* nombre);
    ~operaciones_stub();

};

#endif // OPERACIONES_STUB_H
