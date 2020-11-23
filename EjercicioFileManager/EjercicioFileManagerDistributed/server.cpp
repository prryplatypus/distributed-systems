#include <string>
#include "Utils.h"
#include "FileManagerImp.h"

void clientHandler(int client_id)
{
    FileManagerImp *fm = new FileManagerImp(client_id);

    while (!fm->ragequit)
        fm->handleRequest();

    delete fm;
}

int main(int argc, char **argv)
{
    int server_fd = initServer(8081);
    std::cout << "Server listening on port 8081" << std::endl;

    while (true)
    {
        if (checkNewConnections())
        {
            std::cout << "New connection received" << std::endl;
            int new_id = getNewConnection();
            std::thread *newClient = new std::thread(clientHandler, new_id);
        }
        usleep(1000);
    }

    return 0;
}
