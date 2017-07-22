//
// Created by itai on 6/30/17.
//

#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5151
#define BUFFER_SIZE 10


class Server {
public:
    Server();

    virtual ~Server();

    void bind_server();

    size_t recv();

    void send(size_t len);

    void run();

private:
    int socket_file_descriptor;
    sockaddr_in* addr;
    socklen_t addr_len;

    sockaddr_in* client;

    char buffer[BUFFER_SIZE];
};


#endif
