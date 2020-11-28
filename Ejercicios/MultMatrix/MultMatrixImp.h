#ifndef MULTMATRIXIMP_H
#define MULTMATRIXIMP_H

#include "ClientConnection.h"
#include "multmatrix.h"

using namespace std;


class MultMatrixImp
{
	ClientConnection* cli_conn;
	multMatrix* mm;
public:
	bool terminate;
	MultMatrixImp(ClientConnection* cli_conn);
	void handleRequest();
	~MultMatrixImp();
};

#endif // MULTMATRIXIMP_H
