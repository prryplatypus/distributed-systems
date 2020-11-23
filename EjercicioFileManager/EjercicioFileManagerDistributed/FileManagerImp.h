#ifndef FILEMANAGERIMP_H
#define FILEMANAGERIMP_H
#include "FileManager.h"

using namespace std;

class FileManagerImp
{
public:
	// Ignore the variable name
	bool ragequit;
	int client_id;
	FileManager *fm;
	FileManagerImp(int client_id);
	void handleRequest();
	~FileManagerImp();
};

#endif // FILEMANAGERIMP_H
