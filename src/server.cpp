//
// Created by itai on 6/30/17.
//

#include <iostream>
#include "server.hpp"
#include "util.hpp"
#include "logger.hpp"
#include "resolver.hpp"
#include "query.hpp"
#include "response.hpp"

using DNS::Message;
using DNS::Query;
using DNS::Response;

Server::Server(Resolver* resolver) : m_resolver(resolver) {
	// Create a new inbound address
	m_addr = new sockaddr_in;
	m_addr->sin_family = AF_INET;
	m_addr->sin_port = htons(PORT);
	m_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	
	// Initialize the client socket
	m_client = new sockaddr_in;
	m_addr_len = sizeof(*m_addr);
	
	// Initialize the server socket
	m_sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	// Die if an error occurred
	if (m_sock_fd == -1) {
		DIE("Socket could not be created.");
	}
}

Server::~Server() {
	delete m_addr;
	delete m_client;
}

void Server::bind_server() {
	debug("Binding the server's socket");
	
	// Bind the server's socket
	int result = bind(m_sock_fd, (const sockaddr*) m_addr, m_addr_len);
	
	// Die if an error occurred
	if (result == -1) {
		DIE("Socket could not be binded.");
	}
}

size_t Server::recv() {
	// Receive data from the server socket
	ssize_t data_len = recvfrom(m_sock_fd, m_buffer, BUFFER_SIZE, 0,
				(struct sockaddr*) m_client, &m_addr_len);
	
	// Die if there was an error while receiving the data.
	if (data_len == -1) {
		DIE("Error while receiving data.");
	}
	
	// Return the size of the received data
	return (size_t) data_len;
}

void Server::send(size_t buffer_size) {
	sendto(m_sock_fd, m_buffer, buffer_size, 0,
		(struct sockaddr*) m_client, m_addr_len);
}

size_t Server::handle_query(Query* query) {
	debug("Received query of type: " + std::to_string(query->get_qtype()));

	// Drop AAAA queries since our server does not support IPv6.
	if (query->get_qtype() == Query::Type::AAAA) {
		debug("Dropping IPv6 query");
		delete query;
		return 0;
	}

	std::string resolved = m_resolver->resolve(query->get_qname());
	Response response = *query;
	response.parse_ip_address(resolved);

	size_t buffer_size = response.code(m_buffer);

	delete query;

	return buffer_size;
}

void Server::run() {
	bind_server();
	
	// For now this server listens for connections and then sends the length of the received data.
	// This server should be multithreaded.
	while (1) {
		size_t len = recv();

		// Handle short packets
		if (len < Message::HEADER_SIZE) {
			error("Received a malformed packet (size=" + std::to_string(len) + ").");
		} else {	
			Query* query = new Query;
			query->decode(m_buffer, len);

			size_t buffer_size = handle_query(query);
			send(buffer_size);
		}
	}
}
