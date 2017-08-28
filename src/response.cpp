#include "response.hpp"
#include <cstdio>

using DNS::Response;
using DNS::Query;

Response::Response(const Query& query) : Query(query) {
	// This is always a constant for one response.
	// When the server will support more than one answers in a single packet - this should be calculated.
	m_name = 0xc00c;

	// This was chosen arbitrarily
	m_ttl = 300;

	// This will always be 4 since the IP address's length is 4.
	m_rdlength = 4;
}

int Response::code(char* buffer) {
	return 0;
}

void Response::decode(char* buffer, size_t size) {
}

void Response::parse_ip_address(const std::string& ip) {
	sscanf(ip.c_str(), "%d.%d.%d.%d", m_rdata, m_rdata + 1, m_rdata + 2, m_rdata + 3);
}
