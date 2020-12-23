/**
 * Néstor Pérez
 * github.com/prryplatypus
 */
#ifndef _CLIENT_CONNECTION_H
#define _CLIENT_CONNECTION_H

#include "MyConnection.h"

class ClientConnection : public MyConnection
{
public:
	int id;
	ClientConnection(int sock_fd, int id);
};

#endif // _CLIENT_CONNECTION_H
