#include "FileManagerStub.h"
#include <string.h>
#include <iostream>


FileManagerStub::FileManagerStub(char* host, int port, char* dir) : MyConnection(host, port)
{
	if (sock_fd < 0) {
		throw exception();
	}

	this->receive(&(this->id));
	std::cout << "Client connected. Assigned ID: " << this->id << ". Working directory: " << dir << std::endl;

	this->send(dir);
}


vector<string*>* FileManagerStub::listFiles()
{
	char* buffr;
	int op_type;
	int files_qty;
	vector<string*>* flist = new vector<string*>();

	op_type = OP_LIST;
	this->send(op_type);

	this->receive(&files_qty);
	for (int i = 0; i < files_qty; ++i)
	{
		this->receive(buffr);
		flist->push_back(new string(buffr));
		delete[] buffr;
	}

	return flist;
}


void FileManagerStub::readFile(char* filename, char*& data, unsigned long int& data_len)
{
	int op_type = OP_READ;
	this->send(op_type);

	this->send(filename);
	this->receive(data);
	data_len = strlen(data) + 1;
}


void FileManagerStub::writeFile(char* fileName, char* data, unsigned long int data_len)
{
	return;
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
}
