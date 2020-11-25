#ifndef _CLIENT_CONNECTION_H
#define _CLIENT_CONNECTION_H

#include <list>

#include "MyConnection.h"

/*typedef struct dataPacket_t {
	int dataSize;
	char* data;
}dataPacket_t;*/

class ClientConnection : public MyConnection
{
public:
	int id;
	// int sock_fd;
	// std::list<dataPacket_t *> buffr;

	ClientConnection(int sock_fd, int id);
	~ClientConnection();
};

#endif // _CLIENT_CONNECTION_H
