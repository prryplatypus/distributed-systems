#include "FileManagerImp.h"
#include "FileManagerStub.h"
#include "Utils.h"
#include <iostream>
#include <string>

FileManagerImp::FileManagerImp(ClientConnection* cli_conn)
{
    terminate = false;
    this->cli_conn = cli_conn;

    /**
     * Get the directory that the client
     * wants to work with.
     */ 
    char *buffr;
    this->cli_conn->Receive(buffr);

    std::cout << "Buffer contains: " << buffr << std::endl;

    std::string dir = std::string(buffr);
    delete[] buffr;

    fm = new FileManager(dir);
}


void FileManagerImp::handleRequest()
{
    int typeOp;

    this->cli_conn->Receive(&typeOp);

    switch (typeOp)
    {
        case OP_END: {
            terminate = true;
            break;
        }

        case OP_LIST: {
            vector<string*> *vfiles = fm->listFiles();
            int qty = vfiles->size();
            cli_conn->Send(qty);
            // sendMSG(client_id, &(qty), sizeof(int)); // Tell client how many filenames we're gonna send
            for (unsigned i = 0; i < qty; ++i)
            {
                const char *filename = vfiles->at(i)->c_str();
                cli_conn->Send((char *)filename);
                // sendMSG(client_id, filename, strlen(filename) + 1); // 99% sure something's gonna go wrong here
            }
            fm->freeListedFiles(vfiles);
            break;
        }

        case OP_READ: {
            char* filename;
            char* data = NULL;
            unsigned long int data_len = 0;

            // Get filename to read
            // recvMSG(client_id, (void**)&buffr, &bufferLen);
            // std::cout << "Reading " << buffr << std::endl;
            cli_conn->Receive(filename);
            fm->readFile(filename, data, data_len);
            delete[] filename;

            // Send file contents
            std::cout << "Sending " << data << std::endl;
            // sendMSG(client_id, data, strlen(data) + 1);
            cli_conn->Send(data);
            delete[] data;
        }

        case OP_WRITE: {
            char* filename, * data;
            int data_len = 0;

            // Get filename to write to
            // recvMSG(client_id, (void**)&buffr, &bufferLen);
            cli_conn->Receive(filename);

            // Get file contents to write
            // recvMSG(client_id, (void **)&data, &data_len);
            cli_conn->Receive(data);

            std::cout << "Writing " << data << " to file " << filename << std::endl;
            fm->writeFile(filename, data, data_len + 1);

            delete[] filename;
            delete[] data;
        }

        default: {
            std::cout << "ERROR: operación no reconocida" << std::endl;
            int op = OP_ERR;
            // sendMSG(client_id, &op, sizeof(int));
            cli_conn->Send(op);
        }
    }
}


FileManagerImp::~FileManagerImp()
{
    delete fm;
}
