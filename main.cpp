#include "message.hpp"
#include "resolver.hpp"
#include "logger.hpp"
#include <iostream>

using DNS::Message;

int main() {
    Logger& logger = Logger::instance();
    logger.debug("Initializing DNS");

    Resolver resolver;

    return 0;
}
