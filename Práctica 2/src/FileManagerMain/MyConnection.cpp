/**
 * N�stor P�rez
 * github.com/prryplatypus
 */
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "MyConnection.h"


MyConnection::MyConnection(int sock_fd)
{
    this->sock_fd = sock_fd;
}


MyConnection::MyConnection(char* host, int port)
{
    struct sockaddr_in serv_addr;

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "ERROR: Failed to create socket" << std::endl;
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form 
    if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0)
    {
        std::cout << "ERROR: Invalid address / Address not supported" << std::endl;
        sock_fd = -1;
        return;
    }

    if (connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "ERROR: Connection Failed" << std::endl;
        close(sock_fd);
        sock_fd = -1;
        return;
    }
}


void MyConnection::send(int num)
{
    short tag = SYN;
    int crc;

    // >>> SYN
    write(sock_fd, &tag, sizeof(short));

    // <<< SYN_ACK
    read(sock_fd, &tag, sizeof(short));
    if (tag != SYN_ACK)
    {
        std::cout << "ERROR: Invalid tag received (expected " << SYN_ACK << " received " << tag << ") at line " << __LINE__ << std::endl;
        tag = ERR;
        write(sock_fd, &tag, sizeof(short));
        exit(0);
    }

    // >>> ACK
    tag = ACK;
    write(sock_fd, &tag, sizeof(short));

    // Send data
    write(sock_fd, &num, sizeof(int));

    // <<< "crc"
    read(sock_fd, &crc, sizeof(int));
    if (crc != sizeof(int))
    {
        std::cout << "ERROR: Invalid CRC received (expected " << sizeof(unsigned short) << " received " << crc << ") at line " << __LINE__ << std::endl;
        tag = ERR;
        write(sock_fd, &tag, sizeof(short));
        exit(0);
    }

    // >>> ACK
    tag = ACK;
    write(sock_fd, &tag, sizeof(short));
    
    // <<< END
    read(sock_fd, &tag, sizeof(short));
    if (tag != END)
    {
        std::cout << "ERROR: Invalid tag received (expected " << END << " received " << tag << ") at line " << __LINE__ << std::endl;
        tag = ERR;
        write(sock_fd, &tag, sizeof(short));
        exit(0);
    }
}


void MyConnection::send(char* str, unsigned long data_len)
{
    short tag = SYN;
    int crc;

    // >>> SYN
    write(sock_fd, &tag, sizeof(short));

    // <<< SYN_ACK
    read(sock_fd, &tag, sizeof(short));
    if (tag != SYN_ACK)
    {
        std::cout << "ERROR: Invalid tag received (expected " << SYN_ACK << " received " << tag << ") at line " << __LINE__ << std::endl;
        tag = ERR;
        write(sock_fd, &tag, sizeof(short));
        exit(0);
    }

    // >>> ACK
    tag = ACK;
    write(sock_fd, &tag, sizeof(short));

    // Send datalen
    write(sock_fd, &data_len, sizeof(unsigned long));

    // Send data
    write(sock_fd, str, data_len);

    // <<< "crc"
    read(sock_fd, &crc, sizeof(int));
    if (crc != data_len)
    {
        std::cout << "ERROR: Invalid CRC received (expected " << data_len << " received " << crc << ") at line " << __LINE__ << std::endl;
        tag = ERR;
        write(sock_fd, &tag, sizeof(short));
        exit(0);
    }

    // >>> ACK
    tag = ACK;
    write(sock_fd, &tag, sizeof(short));

    // <<< END
    read(sock_fd, &tag, sizeof(short));
    if (tag != END)
    {
        std::cout << "ERROR: Invalid tag received (expected " << END << " received " << tag << ") at line " << __LINE__ << std::endl;
        tag = ERR;
        write(sock_fd, &tag, sizeof(short));
        exit(0);
    }
}

void MyConnection::receive(int* num)
{
    short tag = 0;
    
    // <<< SYN
    read(sock_fd, &tag, sizeof(short));
    if (tag != SYN)
    {
        std::cout << "ERROR: Invalid tag received (expected " << SYN << " received " << tag << ") at line " << __LINE__ << std::endl;
        exit(0);
    }

    // >>> SYN_ACK
    tag = SYN_ACK;
    write(sock_fd, &tag, sizeof(short));

    // <<< ACK
    read(sock_fd, &tag, sizeof(short));
    if (tag != ACK)
    {
        std::cout << "ERROR: Invalid tag received (expected " << ACK << " received " << tag << ") at line " << __LINE__ << std::endl;
        exit(0);
    }

    // Read data
    int crc = read(sock_fd, num, sizeof(int));

    // >>> "crc"
    write(sock_fd, &crc, sizeof(int));

    // <<< ACK
    read(sock_fd, &tag, sizeof(short));
    if (tag != ACK)
    {
        std::cout << "ERROR: Invalid tag received (expected " << ACK << " received " << tag << ") at line " << __LINE__ << std::endl;
        exit(0);
    }

    // >>> END
    tag = END;
    write(sock_fd, &tag, sizeof(short));
}

void MyConnection::receive(char*&str, unsigned long& data_len)
{
    short tag = 0;

    // <<< SYN
    read(sock_fd, &tag, sizeof(short));
    if (tag != SYN)
    {
        std::cout << "ERROR: Invalid tag received (expected " << SYN << " received " << tag << ") at line " << __LINE__ << std::endl;
        exit(0);
    }

    // >>> SYN_ACK
    tag = SYN_ACK;
    write(sock_fd, &tag, sizeof(short));

    // <<< ACK
    read(sock_fd, &tag, sizeof(short));
    if (tag != ACK)
    {
        std::cout << "ERROR: Invalid tag received (expected " << ACK << " received " << tag << ") at line " << __LINE__ << std::endl;
        exit(0);
    }

    // Read data len
    read(sock_fd, &data_len, sizeof(unsigned long));

    // Allocate memory and read
    str = new char[data_len];
    int crc = read(sock_fd, str, data_len);

    // >>> "crc"
    write(sock_fd, &crc, sizeof(int));

    // <<< ACK
    read(sock_fd, &tag, sizeof(short));
    if (tag != ACK)
    {
        std::cout << "ERROR: Invalid tag received (expected " << ACK << " received " << tag << ") at line " << __LINE__ << std::endl;
        exit(0);
    }

    // >>> END
    tag = END;
    write(sock_fd, &tag, sizeof(short));
}

MyConnection::~MyConnection()
{
    if (sock_fd >= 0)
        close(sock_fd);
}