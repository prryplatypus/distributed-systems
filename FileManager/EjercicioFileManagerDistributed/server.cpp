#include <iostream>

#include "Server.h"
#include "FileManagerImp.h"


void Listener(Server* server)
{
    std::cout << "Now listening for connections" << std::endl;
    while (! server->ShouldTerminate()) {
        int new_cli_id = server->AwaitConnection();
        server->AddPendingConnection(new_cli_id);
    }
    std::cout << "No longer accepting new connections" << std::endl;
}


void Handler(Server *server, int cli_id)
{
    ClientConnection* cli_conn = server->GetClientConn(cli_id);

    std::cout << "Cli Conn: " << cli_conn->id << std::endl;

    FileManagerImp* fm = new FileManagerImp(cli_conn);

    while (!fm->terminate)
        fm->handleRequest();

    delete fm;
    server->SetFinishedThread(cli_id);
}


Server::Server()
{
    terminate = false;
    sock_fd = -1;
    last_id = 0;
    connection_listener = nullptr;
}


void Server::_InitSocket(int port)
{
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        std::cout << "ERROR: Failed to create socket" << std::endl;
        return;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    int option = 1;
    setsockopt(sock_fd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), &option, sizeof(option));

    if (bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "ERROR: Failed to bind socket" << std::endl;
        sock_fd = -1;
        return;
    }

    listen(sock_fd, 5);
}


void Server::_RemoveClientConn(int cli_id)
{
    cli_list_mtx.lock();
    cli_list.erase(cli_id);
    cli_list_mtx.unlock();
}


void Server::FreeFinishedThreads()
{
    int finished_threads;
    
    finished_conn_threads_mtx.lock();
    finished_threads = finished_conn_threads.size();
    finished_conn_threads_mtx.unlock();

    for (int i = 0; i < finished_threads; ++i)
    {
        int cli_id;
        std::thread* conn_thread;

        finished_conn_threads_mtx.lock();
        cli_id = finished_conn_threads.front();
        finished_conn_threads.pop_front();
        finished_conn_threads_mtx.unlock();

        conn_threads_mtx.lock();
        conn_thread = conn_threads[cli_id];
        conn_threads.erase(cli_id);
        conn_threads_mtx.unlock();

        conn_thread->join();
        delete conn_thread;

        _RemoveClientConn(cli_id);
    }
}


int Server::AwaitConnection()
{
    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    int cli_sock_fd = accept(sock_fd, (struct sockaddr*)&cli_addr, &cli_len);

    ClientConnection* conn = new ClientConnection(cli_sock_fd, last_id++);

    cli_list_mtx.lock();
    cli_list[conn->id] = conn;
    cli_list_mtx.unlock();

    return conn->id;
}


void Server::AddPendingConnection(int new_cli_id)
{
    pending_conns_mtx.lock();
    pending_conns.push_back(new_cli_id);
    pending_conns_mtx.unlock();
}


bool Server::HasPendingConnections()
{
    int pending_count;

    pending_conns_mtx.lock();
    pending_count = pending_conns.size();
    pending_conns_mtx.unlock();

    return (pending_count > 0);
}


bool Server::HasRemainingConnections()
{
    int remaining_clients;

    cli_list_mtx.lock();
    remaining_clients = cli_list.size();
    cli_list_mtx.unlock();

    return (remaining_clients > 0);
}


int Server::GetNextPendingConnectionId()
{
    int next_conn_id;

    pending_conns_mtx.lock();
    next_conn_id = pending_conns.front();
    pending_conns.pop_front();
    pending_conns_mtx.unlock();

    return next_conn_id;
}


ClientConnection* Server::GetClientConn(int cli_id)
{
    ClientConnection* cli_conn;

    cli_list_mtx.lock();
    cli_conn = cli_list[cli_id];
    cli_list_mtx.unlock();

    return cli_conn;
}


void Server::SetFinishedThread(int cli_id)
{
    finished_conn_threads_mtx.lock();
    finished_conn_threads.push_back(cli_id);
    finished_conn_threads_mtx.unlock();
}


void Server::Run(int port)
{
    _InitSocket(port);
    if (sock_fd < 0)
    {
        return;
    }

    connection_listener = new std::thread(Listener, this);

    while ((! ShouldTerminate()) || HasRemainingConnections())
    {
        if (HasPendingConnections())
        {
            std::cout << "New connection received" << std::endl;
            int new_id = GetNextPendingConnectionId();

            conn_threads_mtx.lock();
            conn_threads[new_id] = new std::thread(Handler, this, new_id);
            conn_threads_mtx.unlock();
        }
        FreeFinishedThreads();
        usleep(1000);
    }
}


bool Server::ShouldTerminate()
{
    bool tmp_terminate;

    terminate_mtx.lock();
    tmp_terminate = terminate;
    terminate_mtx.unlock();

    return tmp_terminate;
}


void Server::Terminate()
{
    terminate_mtx.lock();
    terminate = true;
    terminate_mtx.unlock();
}


Server::~Server()
{
    connection_listener->join();
    delete connection_listener;
}