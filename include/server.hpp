//
// Created by itai on 6/30/17.
//

#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>

#include "component.hpp"
#include "resolver.hpp"
#include "types.hpp"

#define PORT 53
#define BUFFER_SIZE 1024


class Server : public Component {
public:
	/**
	 * The constructor initializes a new UDP socket on port 53.
	**/
    Server(Resolver* resolver);

	/**
	 * The destructor deletes the server socket.
	**/
    virtual ~Server();

	/**
	 * Send given the data to the client. 
	**/
    void send(const std::string& msg);

	/**
	 * Run the DNS server - handle client requests.
	**/
    void run();

private:
	// Private methods

	/**
	 * Bind the server's socket.
	**/
    void bind_server();

	/**
	 * Receive data from the server's socket.
	**/
    size_t recv();

	// Members

	// The file descriptor of the socket
    int m_sock_fd;
    sockaddr_in* m_addr;
    socklen_t m_addr_len;

    sockaddr_in* m_client;

    char m_buffer[BUFFER_SIZE];

	Resolver* m_resolver;
};


#endif
