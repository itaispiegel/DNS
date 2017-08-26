#include "query.hpp"

using DNS::Query;
using DNS::Message;

int Query::code(char* buffer) {
	return 0;
}

void Query::decode(char* buffer, size_t size) {
	debug("Query::decode() buffer of size: " + std::to_string(size));

	// Decode the header of the packet and increase the buffer.
	decode_hdr(buffer);
	buffer += HEADER_SIZE;

	decode_qname(buffer);
	m_qtype = static_cast<Query::Type>(get16bits(buffer));
	m_qclass = get16bits(buffer);
}

void Query::decode_qname(char*& buffer) {
	m_qname.clear();

	size_t length = *buffer++;
	while (length) {
		for (size_t i = 0; i < length; ++i) {
			m_qname += *buffer;
			buffer++;
		}

		length = *buffer++;

		if (length) {
			m_qname += ".";
		}
	}
}


// Getters
const std::string& Query::get_qname() const {
	return m_qname;
}

const Query::Type Query::get_qtype() const {
	return m_qtype;
}
