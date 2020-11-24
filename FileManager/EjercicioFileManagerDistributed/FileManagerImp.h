#ifndef FILEMANAGERIMP_H
#define FILEMANAGERIMP_H
#include "FileManager.h"

using namespace std;

class FileManagerImp
{
	int client_id;
	FileManager* fm;
public:
	// Ignore the variable name
	bool ragequit;
	FileManagerImp(int client_id);
	void handleRequest();
	~FileManagerImp();
};

#endif // FILEMANAGERIMP_H
