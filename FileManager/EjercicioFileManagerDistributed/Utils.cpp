#include "Utils.h"


int initClient(char* host, int port)
{
	int sock_out = 0;
	struct sockaddr_in serv_addr;

	if ((sock_out = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "ERROR: Failed to create socket" << std::endl;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form 
	if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0)
	{
		std::cout << "ERROR: Invalid address / Address not supported" << std::endl;
		return -1;
	}

	if (connect(sock_out, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << "ERROR: Connection Failed" << std::endl;
		return -1;
	}

	return sock_out;

	/*connection_t* conn = new connection_t[1];

	read(sock_out, &conn->clientID, sizeof(int));
	conn->socket_fd = sock_out;

	conn->buffer = new std::list<dataPacket_t*>();

	clientList[conn->clientID] = conn;

	return conn->clientID;*/
}


void sendMSG(int connID, const void* data, int dataLen) {

	connection_t* conn = clientList[connID];
	int socket = conn->socket_fd;

	short int tag = SYNC;
	int crc = 0;
	// Send sync
	write(socket, &tag, sizeof(short int));
	// Receive sync acknowledgement (if not, error & close connection)
	read(socket, &tag, sizeof(short int));
	//si !=SYNC_ACK
	if (tag != SYNC_ACK)
	{
		//error
		printf("ERROR: sendMSG, linea %d \n", __LINE__);
		//exit
		closeConnection(connID);
		exit(0);
	}

	// Send ACK
	tag = ACK;
	write(socket, &tag, sizeof(short int));

	// Envía tamaño de los datos
	write(socket, &dataLen, sizeof(int));

	// Envía los datos
	write(socket, data, dataLen);

	//recv END

		//recv "crc"
	read(socket, &crc, sizeof(int));
	//comprobar crc
	if (crc != dataLen)
	{    // !crc
			//recuperacion de errores
		printf("ERROR: sendMSG, linea: %d\n", __LINE__);
		//error
		tag = ERROR;
		write(socket, &tag, sizeof(short int));
		closeConnection(connID);
		//exit
		exit(0);
	}
	//else
	tag = ACK;
	//send ACK

	write(socket, &tag, sizeof(short int));
	//recv END
	read(socket, &tag, sizeof(short int));
	//comprobar END

	if (tag != END)
	{
		printf("ERROR: sendMSG, linea: %d\n", __LINE__);
		//error
		closeConnection(connID);
		//exit
		exit(0);
	}
}

void recvMSG(int connID, void** data, int* dataLen) {

	connection_t* conn = clientList[connID];
	int socket = conn->socket_fd;

	short int tag = 0;
	//recv SYNC
	read(socket, &tag, sizeof(short int));
	if (tag != SYNC)
	{
		printf("ERROR: recvMSG, linea: %d - Received TAG value %d\n", __LINE__, tag);
		//error
		closeConnection(connID);
		//exit
		exit(0);
	}

	tag = SYNC_ACK;
	//send SYNC_ACK
	write(socket, &tag, sizeof(short int));
	//recv ACK
	read(socket, &tag, sizeof(short int));

	//si !=ACK
		//error
		//exit	
	if (tag != ACK)
	{
		printf("ERROR: recvMSG, linea: %d\n", __LINE__);
		//error
		closeConnection(connID);
		//exit
		exit(0);
	}



	int tamanioDato = 0;
	char* datos = nullptr;
	int crc = 0;
	//recibe tamaño
	read(socket, &tamanioDato, sizeof(int));
	//recibe datos
		//reservar buffer
	datos = new char[tamanioDato];
	crc = read(socket, datos, tamanioDato);

	//enviar END
		//envio "crc"
	write(socket, &crc, sizeof(int));
	//recv ACK
	read(socket, &tag, sizeof(short int));

	if (tag != ACK)
	{
		printf("ERROR: recvMSG, linea: %d\n", __LINE__);
		//error
		closeConnection(connID);
		//exit
		exit(0);
	}
	tag = END;
	write(socket, &tag, sizeof(short int));
	//envio END
	*data = datos;
	*dataLen = tamanioDato;

}

void closeConnection(int clientID) {

	connection_t* conn = clientList[clientID];

	std::cout << "Closing connection for client with ID " << conn->clientID << std::endl;

	close(conn->socket_fd);
	clientList.erase(clientID);
	if (conn->buffer->size() > 0)
	{
		printf("WARNING Unatended messages on close connection\n");
	}
	for (std::list<dataPacket_t*>::iterator it = conn->buffer->begin();
		it != conn->buffer->end();
		++it)
	{
		delete[](*it)->data;
		delete[](*it);
	}

	delete conn->buffer;
	conn->alive = false;
}

bool checkNewConnections()
{
	return (pendingConnections.size() > 0);
}

int getNewConnection()
{
	int newId = pendingConnections.front();
	pendingConnections.pop_front();
	return newId;
}
