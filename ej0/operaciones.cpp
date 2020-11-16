#include "operaciones.h"
#include <stdio.h>
#include <stdlib.h>

operaciones::operaciones()
{

}

int operaciones::suma(int a, int b)
{
    return a+b;
}

char* operaciones::leeFichero(char* nombre){

    int fileLen=0;
    char* data=0x00;

    FILE* f=fopen(nombre,"r");
    if(f!=NULL){
        fseek(f,0,SEEK_END);
        fileLen=ftell(f);
        fseek(f,0,SEEK_SET);
        data=new char[fileLen+1];
        fread(data,1,fileLen,f);
        data[fileLen]='\0';
        fclose(f);
    }
    else
        data=0x00;

    return data;

}
