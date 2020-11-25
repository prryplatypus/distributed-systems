#ifndef FILEMANAGER_STUB_H
#define FILEMANAGER_STUB_H

#include <string>
#include <map>
#include <vector>

#include "MyConnection.h"

#define OP_ERR -1
#define OP_END 0
#define OP_LIST 1
#define OP_READ 2
#define OP_WRITE 3

using namespace std;

class FileManagerStub : public MyConnection
{
    int id;
public:
    FileManagerStub(char *dir);
	vector<string*>* listFiles();
	void readFile(char* fileName, char*& data, unsigned long int& dataLength);
	void writeFile(char* fileName, char* data, unsigned long int dataLength);
	void freeListedFiles(vector<string*>* fileList);
    ~FileManagerStub();
};

int initClient(char* host, int port);

#endif // FILEMANAGER_STUB_H
