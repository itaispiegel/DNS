#include "query.hpp"
#include "logger.hpp"

using DNS::Query;

int Query::code(char* buffer) {
	return 0;
}

void Query::decode(char* buffer, size_t size) {
	Logger& logger = Logger::instance();
	logger.debug("Query::decode() buffer of size: " + std::to_string(size));

	// Decode the header of the packet and increase the buffer.
	decode_hdr(buffer);
	buffer += HEADER_SIZE;
}
