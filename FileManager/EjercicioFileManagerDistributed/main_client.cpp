#include <iostream>
#include "FileManagerStub.h"

int main(int argc, char** argv)
{
	while (true) {
		FileManagerStub* fm = new FileManagerStub("192.168.1.85", 8081, "./dirprueba");
		vector<string*>* vfiles = fm->listFiles();

		std::cout << "Lista de ficheros en el directorio de prueba:" << std::endl;
		for (unsigned i = 0; i < vfiles->size(); ++i)
		{
			std::cout << "\t- " << vfiles->at(i)->c_str() << std::endl;
		}
		
		std::cout << "Leyendo el primer fichero del directorio de prueba: ";
		char* data = nullptr;
		unsigned long int dataLen = 0;
		fm->readFile(&(*(vfiles->at(0)))[0], data, dataLen);
		std::cout << data;

		/*std::cout << "Escribiendo el primer fichero del directorio de prueba..." << std::endl;
		fm->writeFile(&(*(vfiles->at(0)))[0], data, dataLen);

		std::cout << "Escribiendo el primer fichero del directorio en el directorio local..." << std::endl;
		FILE* f = fopen(&(*(vfiles->at(0)))[0], "w");
		fwrite(data, dataLen, 1, f);
		fclose(f);*/

		std::cout << "Liberando lista de ficheros..." << std::endl;
		fm->freeListedFiles(vfiles);

		std::cout << "Liberando datos de fichero leído..." << std::endl;
		delete[] data;
		delete fm;
	}

	return 0;
}
