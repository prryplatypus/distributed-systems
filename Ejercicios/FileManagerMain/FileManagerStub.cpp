#include "FileManagerStub.h"
#include <string.h>
#include <iostream>


FileManagerStub::FileManagerStub(char* host, int port, char* dir) : MyConnection(host, port)
{
	std::string local_path(".");
	fm_lcl = new FileManager(local_path);

	this->receive(&(this->id));
	std::cout << "Client connected. Assigned ID: " << this->id << ". Working directory: " << dir << std::endl;

	this->send(dir, strlen(dir) + 1);
}


vector<string*>* FileManagerStub::listRemoteFiles()
{
	char* buffr;
	unsigned long data_len;
	int op_type;
	int files_qty;
	vector<string*>* flist = new vector<string*>();

	op_type = OP_LIST;
	this->send(op_type);

	this->receive(&files_qty);
	for (int i = 0; i < files_qty; ++i)
	{
		this->receive(buffr, data_len);
		flist->push_back(new string(buffr, data_len));
		delete[] buffr;
	}

	return flist;
}


void FileManagerStub::readLocalFile(char* filename, char*& data, unsigned long int& data_len)
{
	fm_lcl->readFile(filename, data, data_len);
}


void FileManagerStub::readRemoteFile(char* filename, char*& data, unsigned long int& data_len)
{
	int op_type = OP_READ;
	this->send(op_type);

	this->send(filename, strlen(filename) + 1);
	this->receive(data, data_len);
}


void FileManagerStub::writeLocalFile(char* filename, char* data, unsigned long int data_len)
{
	fm_lcl->writeFile(filename, data, data_len);
}


void FileManagerStub::writeRemoteFile(char* filename, char* data, unsigned long int data_len)
{
	int op_type = OP_WRITE;
	this->send(op_type);

	this->send(filename, strlen(filename) + 1);
	this->send(data, data_len);
}


void FileManagerStub::freeListedFiles(vector<string*>* file_list)
{
	for (vector<string*>::iterator i = file_list->begin();i != file_list->end();++i)
	{
		delete* i;
	}
	delete file_list;
}


FileManagerStub::~FileManagerStub() {
	int op_type = OP_END;
	this->send(op_type);
	delete fm_lcl;
}
