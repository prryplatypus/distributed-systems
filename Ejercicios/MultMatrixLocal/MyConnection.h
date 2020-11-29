#ifndef _MY_CONNECTION_H
#define _MY_CONNECTION_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <unistd.h>

#include <map>
#include <list>
#include <thread>
#include <mutex>

#include "multmatrix.h"

#define ERR		-1
#define ACK      0
#define SYN_ACK  1
#define SYN      2
#define END      3


class MyConnection {
private:
	int sock_fd;
protected:
	MyConnection(int sock_fd);
	MyConnection(char* host, int port);
	~MyConnection();
public:
	void send(int num);
	void send(matrix_t* matrix);
	void send(char* filename);
	void receive(int* num);
	void receive(matrix_t*& matrix_t);
	void receive(char* &filename);
};

#endif // _MY_CONNECTION_H