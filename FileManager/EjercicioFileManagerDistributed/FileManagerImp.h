#ifndef FILEMANAGERIMP_H
#define FILEMANAGERIMP_H
#include "FileManager.h"
#include "ClientConnection.h"

using namespace std;

class FileManagerImp
{
	ClientConnection* cli_conn;
	FileManager* fm;
public:
	// Ignore the variable name
	bool terminate;
	FileManagerImp(ClientConnection* cli_conn);
	void handleRequest();
	~FileManagerImp();
};

#endif // FILEMANAGERIMP_H
