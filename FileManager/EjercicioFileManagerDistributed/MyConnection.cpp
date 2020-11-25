#include <iostream>
#include <unistd.h>
#include <cstring>
#include "MyConnection.h"


MyConnection::MyConnection(int sock_fd)
{
    this->sock_fd = sock_fd;
}


void MyConnection::Send(int num)
{
    short tag = SYN;
    int crc;

    // >>> SYN
    write(sock_fd, &tag, sizeof(short));

    // <<< SYN_ACK
    read(sock_fd, &tag, sizeof(short));
    if (tag != SYN_ACK)
    {
        std::cout << "ERROR: Invalid tag received (expected " << SYN_ACK << " received " << tag << ")" << std::endl;
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
        std::cout << "ERROR: Invalid CRC received (expected " << sizeof(unsigned short) << " received " << crc << ")" << std::endl;
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
        std::cout << "ERROR: Invalid tag received (expected " << END << " received " << tag << ")" << std::endl;
        tag = ERR;
        write(sock_fd, &tag, sizeof(short));
        exit(0);
    }
}


void MyConnection::Send(char* str)
{
    short tag = SYN;
    unsigned data_len = strlen(str) + 1;
    int crc;

    // >>> SYN
    write(sock_fd, &tag, sizeof(short));

    // <<< SYN_ACK
    read(sock_fd, &tag, sizeof(short));
    if (tag != SYN_ACK)
    {
        std::cout << "ERROR: Invalid tag received (expected " << SYN_ACK << " received " << tag << ")" << std::endl;
        tag = ERR;
        write(sock_fd, &tag, sizeof(short));
        exit(0);
    }

    // >>> ACK
    tag = ACK;
    write(sock_fd, &tag, sizeof(short));

    // Send datalen
    write(sock_fd, &data_len, sizeof(unsigned));

    // Send data
    write(sock_fd, str, data_len);

    // <<< "crc"
    read(sock_fd, &crc, sizeof(int));
    if (crc != data_len)
    {
        std::cout << "ERROR: Invalid CRC received (expected " << data_len << " received " << crc << ")" << std::endl;
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
        std::cout << "ERROR: Invalid tag received (expected " << END << " received " << tag << ")" << std::endl;
        tag = ERR;
        write(sock_fd, &tag, sizeof(short));
        exit(0);
    }
}

void MyConnection::Receive(int* num)
{
    short tag = 0;
    
    // <<< SYN
    read(sock_fd, &tag, sizeof(short));
    if (tag != SYN)
    {
        std::cout << "ERROR: Invalid tag received (expected " << SYN << " received " << tag << ")" << std::endl;
        exit(0);
    }

    // >>> SYN_ACK
    tag = SYN_ACK;
    write(sock_fd, &tag, sizeof(short));

    // <<< ACK
    read(sock_fd, &tag, sizeof(short));
    if (tag != ACK)
    {
        std::cout << "ERROR: Invalid tag received (expected " << ACK << " received " << tag << ")" << std::endl;
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
        std::cout << "ERROR: Invalid tag received (expected " << ACK << " received " << tag << ")" << std::endl;
        exit(0);
    }

    // >>> END
    tag = END;
    write(sock_fd, &tag, sizeof(short));
}

void MyConnection::Receive(char* str)
{
    short tag = 0;
    unsigned data_len;

    // <<< SYN
    read(sock_fd, &tag, sizeof(short));
    if (tag != SYN)
    {
        std::cout << "ERROR: Invalid tag received (expected " << SYN << " received " << tag << ")" << std::endl;
        exit(0);
    }

    // >>> SYN_ACK
    tag = SYN_ACK;
    write(sock_fd, &tag, sizeof(short));

    // <<< ACK
    read(sock_fd, &tag, sizeof(short));
    if (tag != ACK)
    {
        std::cout << "ERROR: Invalid tag received (expected " << ACK << " received " << tag << ")" << std::endl;
        exit(0);
    }

    // Read data len
    read(sock_fd, &data_len, sizeof(unsigned));

    // Allocate memory and read
    str = new char[data_len];
    int crc = read(sock_fd, str, data_len);

    // >>> "crc"
    write(sock_fd, &crc, sizeof(int));

    // <<< ACK
    read(sock_fd, &tag, sizeof(short));
    if (tag != ACK)
    {
        std::cout << "ERROR: Invalid tag received (expected " << ACK << " received " << tag << ")" << std::endl;
        exit(0);
    }

    // >>> END
    tag = END;
    write(sock_fd, &tag, sizeof(short));
}

MyConnection::~MyConnection()
{
    close(sock_fd);
}