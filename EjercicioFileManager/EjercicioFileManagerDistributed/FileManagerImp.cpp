#include "FileManagerImp.h"
#include "OperacionesStub.h"
#include "Utils.h"
#include <iostream>
#include <string>

FileManagerImp::FileManagerImp(int client_id)
{
    ragequit = false;
    client_id = client_id;

    /**
     * Get the directory that the client
     * wants to work with.
     */ 
    char *buffr = NULL;
    int bufferLen = 0;
    recvMSG(client_id, (void**)&buffr, &bufferLen);
    std::string dir = std::string(buffr);
    delete[] buffr;

    fm = new FileManager(dir);
}


void FileManagerImp::handleRequest()
{
    char *buffr = 0x00;
    int bufferLen = 0;
    int typeOp = 0;

    recvMSG(client_id, (void**)&buffr, &bufferLen);
    typeOp = ((int*)buffr)[0];

    delete[] buffr;

    switch (typeOp)
    {
        case OP_END: {
            ragequit = true;
            break;
        }

        case OP_LIST: {
            vector<string*> *vfiles = fm->listFiles();
            int qty = vfiles->size();
            sendMSG(client_id, &(qty), sizeof(int)); // Tell client how many filenames we're gonna send
            for (unsigned i = 0; i < qty; ++i)
            {
                const char *filename = vfiles->at(i)->c_str();
                sendMSG(client_id, &(filename), strlen(filename) + 1); // 99% sure something's gonna go wrong here
            }
            fm->freeListedFiles(vfiles);
            break;
        }

        case OP_READ: {
            //
        }

        case OP_WRITE: {
            //
        }

        default: {
            std::cout << "ERROR: operación no reconocida" << std::endl;
            int op = OP_ERR;
            sendMSG(client_id, &op, sizeof(int));
        }
    }
}


FileManagerImp::~FileManagerImp()
{
    delete fm;
}
