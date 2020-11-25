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

#define ERR		-1
#define ACK      0
#define SYN_ACK  1
#define SYN      2
#define END      3


class MyConnection {
protected:
	int sock_fd;
public:
	MyConnection(int sock_fd);
	void Send(int num);
	void Send(char* str);
	void Receive(int* num);
	void Receive(char* str);
	~MyConnection();
};

#endif // _MY_CONNECTION_H