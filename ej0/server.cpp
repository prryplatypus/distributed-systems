#include "utils.h"
#include <string>
#include "operaciones_imp.h"

void clientHandler(int clientID)
{
    operaciones_imp* op=new operaciones_imp(clientID);

    while(!op->salir)
        op->recvOp();

    delete op;
}

int main(int argc,char** argv)
{

        int server_fd=initServer(8081);

        while(true)
        {
            if(checkNewConnections())
            {
                int newID=getNewConnection();
                std::thread* newClient=new std::thread(clientHandler,newID);
            }
            usleep(1000);
        }

        return 0;
}
