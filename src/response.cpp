#include "response.hpp"
#include <cstdio>

using DNS::Response;
using DNS::Query;

Response::Response(const Query& query) : Query(query) {
	m_qr = Message::Type::Response;
	m_ra = 1;
	m_anCount = 1;

	// This is always a constant for one response.
	// When the server will support more than one answers in a single packet - this should be calculated.
	m_name = 0xc00c;

	// This was chosen arbitrarily
	m_ttl = 300;

	// This will always be 4 since the IP address's length is 4.
	m_rdlength = 4;
}

size_t Response::code(char* buffer) {
	debug("Response::code()");

	char* buffer_begin = buffer;

	code_hdr(buffer);
	buffer += HEADER_SIZE;

	code_qname(buffer, m_qname);
	put16bits(buffer, m_qtype);
	put16bits(buffer, m_qclass);

	put16bits(buffer, m_name);
	put16bits(buffer, m_qtype);
	put16bits(buffer, m_qclass);
	put32bits(buffer, m_ttl);
	put16bits(buffer, m_rdlength);

	put8bits(buffer, m_rdata[0]);
	put8bits(buffer, m_rdata[1]);
	put8bits(buffer, m_rdata[2]);
	put8bits(buffer, m_rdata[3]);
	put8bits(buffer, 0);

	return buffer - buffer_begin;
}

void Response::decode(char* buffer, size_t size) {
}

void Response::parse_ip_address(const std::string& ip) {
	int a, b, c, d;
	sscanf(ip.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);

	m_rdata[0] = a;
	m_rdata[1] = b;
	m_rdata[2] = c;
	m_rdata[3] = d;
}

void Response::code_qname(char*& buffer, const std::string& qname) {
	size_t start(0), end;

	while((end = qname.find('.', start)) != std::string::npos) {
		*buffer++ = end - start;

		for (size_t i = start; i < end; i++) {
			*buffer++ = qname[i];
		}

		start = end + 1;
	}

	*buffer++ = qname.size() - start;
	for (size_t i = start; i < qname.size(); i++) {
		*buffer++ = qname[i];
	}

	*buffer++ = 0;
}
