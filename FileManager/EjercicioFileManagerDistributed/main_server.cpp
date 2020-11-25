#include "Server.h"

int main(int argc, char **argv)
{
    Server *server = new Server();

    server->Run(8081);

    return 0;
}
