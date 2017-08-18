#include "component.hpp"

Logger& Component::logger() const {
	return Logger::instance();
}


void Component::debug(const std::string& msg) const {
	logger().debug(msg);
}

void Component::error(const std::string& msg) const {
	logger().error(msg);
}
