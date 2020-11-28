#ifndef _SERVER_H
#define _SERVER_H

#include "ClientConnection.h"


class Server
{
private:
	bool terminate;
	std::mutex terminate_mtx;

	int sock_fd;
	int last_id;
	std::thread* connection_listener;
	
	std::map<int, ClientConnection*>  cli_list;
	std::mutex cli_list_mtx;
	std::list<int> pending_conns;
	std::mutex pending_conns_mtx;
	std::map<int, std::thread*> conn_threads;
	std::mutex conn_threads_mtx;
	std::list<int> finished_conn_threads;
	std::mutex finished_conn_threads_mtx;

	void initSocket(int port);
	void removeClientConn(int cli_id);
protected:
	void freeFinishedThreads();
public:
	Server();
	int awaitConnection();
	void addPendingConnection(int new_cli_id);
	bool hasPendingConnections();
	bool hasRemainingConnections();
	int getNextPendingConnectionId();
	ClientConnection* getClientConn(int cli_id);
	void setFinishedThread(int cli_id);
	void run(int port);
	bool shouldTerminate();
	void stop();
	~Server();
};

void listener(Server* server);
void handler(Server* server, int cli_id);

#endif // _SERVER_H
