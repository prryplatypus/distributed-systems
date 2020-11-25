#include "ClientConnection.h"


ClientConnection::ClientConnection(int sock_fd, int id)
	: MyConnection(sock_fd)
{
	this->id = id;
	// this.buffr = new std::list<dataPacket_t*>();
	// Let our client know what its id is
	this->Send(this->id);
	// write(this->sock_fd, &(this->id), sizeof(int));
}


ClientConnection::~ClientConnection()
{

}