#include "resolver.hpp"
#include <fstream>

const std::string Resolver::DOMAINS_FILE = "/etc/dns/domains.conf";


Resolver::Resolver() {
    parse_domains();
}


void Resolver::parse_domains() {
    std::ifstream domains_file(Resolver::DOMAINS_FILE);

    // Iterate over all ip and domain pairs and add each one to the map.
    std::string ip, domain;
    while (domains_file >> ip >> domain) {
        m_resolved[ip] = domain;
    }

    domains_file.close(); 
}

std::string Resolver::resolve(const std::string& ip) const {
    return m_resolved.at(ip);
}
