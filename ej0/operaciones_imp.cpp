#include "operaciones_imp.h"
#include "operaciones_stub.h"
#include <iostream>
#include <string.h>
#include "utils.h"
operaciones_imp::operaciones_imp(int clientID)
{

    client_fd=clientID;//waitForConnections(socket_fd);
    op=new operaciones();
}


void operaciones_imp::recvOp()
{
    char* buffr=0x00;
    int bufferLen=0;

    int typeOp=0;
    recvMSG(client_fd,(void**)&buffr,&bufferLen);
    typeOp=((int*)buffr)[0];
    delete[] buffr;

    switch(typeOp)
    {
    case OP_END:{
        this->salir=true;
    }
        break;

    case OP_SUMA:{
        int parametro1=0;
        int parametro2=0;
        int resultado=0;
        recvMSG(client_fd,(void**)&buffr,&bufferLen);
        parametro1=((int*)buffr)[0];
        delete[] buffr;
        recvMSG(client_fd,(void**)&buffr,&bufferLen);
        parametro2=((int*)buffr)[0];
        delete[] buffr;

        resultado=op->suma(parametro1,parametro2);

        sendMSG(client_fd,&resultado,sizeof(int));
    }
        break;
    case OP_FICHERO:
    {
        char* fichero=0x00;
        recvMSG(client_fd,(void**)&buffr,&bufferLen);
        fichero=op->leeFichero(buffr);
        delete[] buffr;
        sendMSG(client_fd,fichero,strlen(fichero)+1);
        delete[] fichero;
    }break;
    default:
    {
        std::cout<<"ERROR: operación no reconocida\n";
        exit(0);
    }
        break;
    }
}

operaciones_imp::~operaciones_imp()
{
    closeConnection(client_fd);
    delete op;
}
