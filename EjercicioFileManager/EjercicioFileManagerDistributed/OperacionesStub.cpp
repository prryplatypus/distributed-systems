#include "OperacionesStub.h"
#include "Utils.h"
#include <string.h>

OperacionesStub::OperacionesStub()
{
    socket = initClient("127.0.0.1", 8081);
}


/*int OperacionesStub::suma(int a, int b)
{
    int res = 0;
    char* buffr;
    int buffrlen = 0;
    int opType = OP_SUMA;
    sendMSG(socket, &opType, sizeof(int));
    sendMSG(socket, &a, sizeof(int));
    sendMSG(socket, &b, sizeof(int));
    recvMSG(socket, (void**)&buffr, &buffrlen);

    res = ((int*)buffr)[0];
    delete[] buffr;
    return res;
}


char* OperacionesStub::leeFichero(char* nombre)
{
    char* data = 0x00;
    int dataLen = 0;
    int opType = OP_FICHERO;
    sendMSG(socket, &opType, sizeof(int));

    sendMSG(socket, nombre, strlen(nombre) + 1);
    recvMSG(socket, (void**)&data, &dataLen);

    return data;
}*/


OperacionesStub::~OperacionesStub() {
    int opType = OP_END;
    sendMSG(socket, &opType, sizeof(int));

}
