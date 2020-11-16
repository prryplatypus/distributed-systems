#include "utils.h"
#include "operaciones_stub.h"
#include <iostream>
#include <string>

int main(int argc,char** argv)
{

    operaciones_stub* op=new operaciones_stub();


    int resultado=op->suma(52,25);
    char* datoLeido=op->leeFichero("holamundo.txt");


    std::cout<<"resultado "<<resultado <<", Fichero leido "<<std::string(datoLeido)<<"\n";
    delete[] datoLeido;
    delete op;
    return 0;

}
