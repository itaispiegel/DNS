#include "resolver.hpp"
#include "logger.hpp"
#include <fstream>

const std::string Resolver::DOMAINS_FILE = "/etc/dns/domains.conf";


Resolver::Resolver() {
	debug("Initializing resolver");

	parse_domains();
}


void Resolver::parse_domains() {
	std::ifstream domains_file(Resolver::DOMAINS_FILE);

	// Iterate over all ip and domain pairs and add each one to the map.
	std::string ip, domain;

	size_t i = 0;
	for (; domains_file >> ip >> domain; ++i) {
		m_resolved[domain] = ip;
	}

	debug(std::to_string(i) + " domains were resolved");
	domains_file.close(); 
}

std::string Resolver::resolve(const std::string& domain) const {
	auto result = m_resolved.find(domain);
	debug("Resolving for query: " + domain);

	if (result != m_resolved.end()) {
		debug(result->second);
		return result->second;
	}

	debug("The query couldn't be resolved.");
	return "";
}
