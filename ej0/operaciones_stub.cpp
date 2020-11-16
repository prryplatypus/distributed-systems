#include "operaciones_stub.h"
#include <string.h>
#include "utils.h"

operaciones_stub::operaciones_stub()
{

    socket=initClient("127.0.0.1",8081);
}


int operaciones_stub::suma(int a, int b)
{

    int res=0;
    char* buffr;
    int buffrlen=0;
    int opType=OP_SUMA;
    sendMSG(socket,&opType,sizeof(int));
    sendMSG(socket,&a,sizeof(int));
    sendMSG(socket,&b,sizeof(int));
    recvMSG(socket,(void**)&buffr,&buffrlen);

    res=((int*)buffr)[0];
    delete[] buffr;
    return res;

}


 char* operaciones_stub::leeFichero(char* nombre)
 {
    char* data=0x00;
    int dataLen=0;
    int opType=OP_FICHERO;
    sendMSG(socket,&opType,sizeof(int));

    sendMSG(socket,nombre,strlen(nombre)+1);
    recvMSG(socket,(void**)&data,&dataLen);

    return data;
 }


 operaciones_stub::~operaciones_stub(){
     int opType=OP_END;
     sendMSG(socket,&opType,sizeof(int));

 }
