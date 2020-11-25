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

	void _InitSocket(int port);
	void _Listen();
	void _HandleConnection(int cli_id);
	void _RemoveClientConn(int cli_id);
protected:
	void FreeFinishedThreads();
public:
	Server();
	int AwaitConnection();
	void AddPendingConnection(int new_cli_id);
	bool HasPendingConnections();
	bool HasRemainingConnections();
	int GetNextPendingConnectionId();
	ClientConnection* GetClientConn(int cli_id);
	void SetFinishedThread(int cli_id);
	void Run(int port);
	bool ShouldTerminate();
	void Terminate();
	~Server();
};

void Listener(Server* server);
void Handler(Server* server, int cli_id);

#endif // _SERVER_H
