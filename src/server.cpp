//
// Created by itai on 6/30/17.
//

#include <iostream>
#include "server.h"
#include "util.h"

Server::Server() {
    addr = new sockaddr_in;
    addr->sin_family = AF_INET;
    addr->sin_port = htons(PORT);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);

    client = new sockaddr_in;

    addr_len = sizeof(*addr);

    socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socket_file_descriptor == -1) {
        DIE("Socket Error");
    }
}

Server::~Server() {
    delete addr;
    delete client;
}

void Server::bind_server() {
    int res = bind(socket_file_descriptor, (const sockaddr*) addr, addr_len);

    if (res == -1) {
        DIE("Bind Error");
    }
}

size_t Server::recv() {
    ssize_t data_len = recvfrom(socket_file_descriptor, buffer, BUFFER_SIZE, 0,
                                (struct sockaddr*) client, &addr_len);

    if (data_len == -1) {
        DIE("Recv Error");
    }

    return (size_t) data_len;
}

void Server::send(size_t len) {
    sendto(socket_file_descriptor, buffer, len, 0,
           (struct sockaddr*) client, addr_len);
}

void Server::run() {
    while (1) {
        size_t len = recv();
        send(len);
    }
}
