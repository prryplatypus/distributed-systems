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
    FileManagerStub(char *host, int port, char *dir);
	vector<string*>* listFiles();
	void readFile(char* fileName, char*& data, unsigned long int& data_len);
	void writeFile(char* fileName, char* data, unsigned long int data_len);
	void freeListedFiles(vector<string*>* file_list);
    ~FileManagerStub();
};

#endif // FILEMANAGER_STUB_H
