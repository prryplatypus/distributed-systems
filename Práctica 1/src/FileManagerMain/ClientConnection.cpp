/**
 * Néstor Pérez
 * github.com/prryplatypus
 */
#include "ClientConnection.h"


ClientConnection::ClientConnection(int sock_fd, int id)
	: MyConnection(sock_fd)
{
	this->id = id;
	this->send(this->id);
}
