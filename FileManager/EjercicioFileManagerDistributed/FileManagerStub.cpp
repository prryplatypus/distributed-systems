#include "FileManagerStub.h"
#include <string.h>
#include <iostream>


int initClient(char* host, int port)
{
    int sock_out = 0;
    struct sockaddr_in serv_addr;

    if ((sock_out = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "ERROR: Failed to create socket" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form 
    if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0)
    {
        std::cout << "ERROR: Invalid address / Address not supported" << std::endl;
        return -1;
    }

    if (connect(sock_out, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "ERROR: Connection Failed" << std::endl;
        return -1;
    }

    return sock_out;
}


FileManagerStub::FileManagerStub(char *dir) : MyConnection(initClient("192.168.1.85", 8081))
{
    if (this->sock_fd < 0) {
        throw exception();
    }

    this->Receive(&(this->id));
    std::cout << "Client connected. Assigned ID: " << this->id << std::endl;

    this->Send(dir);
}


vector<string*>* FileManagerStub::listFiles()
{
    char* buffr;
    int op_type;
    int files_qty;
    int buffrlen = 0;
    vector<string*>* flist = new vector<string*>();
    
    op_type = OP_LIST;
    this->Send(op_type);
    // sendMSG(socket, &opType, sizeof(int));

    // Receive the amount of filenames we'll have to receive
    this->Receive(&files_qty);
    // recvMSG(socket, (void**)&buffr, &buffrlen);
    //files_qty = ((int*)buffr)[0];
    // delete[] buffr;

    // Receive each of the filenames
    for (int i = 0; i < files_qty; ++i)
    {
        this->Receive(buffr);
        // recvMSG(socket, (void**)&buffr, &buffrlen);
        flist->push_back(new string(buffr));
        delete[] buffr;
    }

    return flist;
}


void FileManagerStub::readFile(char* filename, char*& data, unsigned long int& data_len)
{
    int op_type = OP_READ;
    this->Send(op_type);
    // sendMSG(socket, &opType, sizeof(int));
    this->Send(filename);
    // sendMSG(socket, fileName, strlen(fileName) + 1);

    this->Receive(data);
    data_len = strlen(data) + 1;
    // recvMSG(socket, (void**)&data, (int *)&dataLength);
}


void FileManagerStub::writeFile(char* fileName, char* data, unsigned long int dataLength)
{
    return;
}


void FileManagerStub::freeListedFiles(vector<string*>* fileList)
{
    for (vector<string*>::iterator i = fileList->begin();i != fileList->end();++i)
    {
        delete* i;
    }
    delete fileList;
}


FileManagerStub::~FileManagerStub() {
    // int opType = OP_END;
    // sendMSG(socket, &opType, sizeof(int));
}
