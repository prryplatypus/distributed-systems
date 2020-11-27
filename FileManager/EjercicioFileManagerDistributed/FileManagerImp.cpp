#include "FileManagerImp.h"
#include "FileManagerStub.h"
#include <iostream>
#include <cstring>

FileManagerImp::FileManagerImp(ClientConnection* cli_conn)
{
    terminate = false;
    this->cli_conn = cli_conn;

    /**
     * Get the directory that the client
     * wants to work with.
     */ 
    char *dir;
    this->cli_conn->receive(dir);
    std::string basedir(dir);
    delete[] dir;

    fm = new FileManager(basedir);
}


void FileManagerImp::handleRequest()
{
    int type_op;
    cli_conn->receive(&type_op);

    switch (type_op)
    {
        case OP_END: {
            terminate = true;
            break;
        }

        case OP_LIST: {
            vector<string*> *vfiles = fm->listFiles();

            int how_many = vfiles->size();
            cli_conn->send(how_many);
            for (unsigned i = 0; i < how_many; ++i)
            {
                const char *filename = vfiles->at(i)->c_str();
                cli_conn->send((char *)filename);
            }

            fm->freeListedFiles(vfiles);
            break;
        }

        case OP_READ: {
            char* filename;
            char* content;
            unsigned long data_len;

            cli_conn->receive(filename);

            fm->readFile(filename, content, data_len);
            delete[] filename;

            cli_conn->send(content);
            delete[] content;
            break;
        }

        case OP_WRITE: {
            char* filename;
            char* content;

            cli_conn->receive(filename);
            cli_conn->receive(content);

            fm->writeFile(filename, content, strlen(content) + 1);
            delete[] filename;
            delete[] content;
            break;
        }

        default: {
            std::cout << "ERROR: Unknown operation type (" << type_op << ") on line " << __LINE__ << std::endl;
            int op = OP_ERR;
            cli_conn->send(op);
        }
    }
}


FileManagerImp::~FileManagerImp()
{
    delete fm;
}
