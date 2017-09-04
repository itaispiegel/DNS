#include "message.hpp"
#include "resolver.hpp"
#include "logger.hpp"
#include "server.hpp"
#include <iostream>

using DNS::Message;

int main() {
	Logger& logger = Logger::instance();
	logger.debug("Initializing DNS");

	Resolver resolver;
	Server server(&resolver);
	server.run();

	return 0;
}
