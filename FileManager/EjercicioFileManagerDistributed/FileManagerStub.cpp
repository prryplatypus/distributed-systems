#include "FileManagerStub.h"
#include "Utils.h"
#include <string.h>

FileManagerStub::FileManagerStub(char *dir)
{
    socket = initClient("127.0.0.1", 8081);
    sendMSG(socket, dir, strlen(dir));
}


vector<string*>* FileManagerStub::listFiles()
{
    char* buffr;
    int buffrlen = 0;
    int files_qty = 0;
    int opType = OP_LIST;
    vector<string*>* flist = new vector<string*>();
    sendMSG(socket, &opType, sizeof(int));

    // Receive the amount of filenames we'll have to receive
    recvMSG(socket, (void**)&buffr, &buffrlen);
    files_qty = ((int*)buffr)[0];
    delete[] buffr;

    // Receive each of the filenames
    for (int i = 0; i < files_qty; ++i)
    {
        recvMSG(socket, (void**)&buffr, &buffrlen);
        flist->push_back(new string(buffr));
        delete[] buffr;
    }

    return flist;
}


void FileManagerStub::readFile(char* fileName, char*& data, unsigned long int& dataLength)
{
    int opType = OP_READ;
    sendMSG(socket, fileName, strlen(fileName) + 1);

    recvMSG(socket, (void**)&data, (int *)&dataLength);
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
    int opType = OP_END;
    sendMSG(socket, &opType, sizeof(int));
}
