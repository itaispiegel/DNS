/**
 * This class represents the resolver component of the server.
 * When the class is first initialized, it reads the resolved domains from the configuration file.
 * Then, it maps IP addresses to domain names accordingly.
 *
 * @author Itai Spiegel
**/

#ifndef RESOLVER_H
#define RESOLVER_H

#include "component.hpp"
#include <string>
#include <unordered_map>

class Resolver : Component {
    public:

        /**
         * This constant member represents the path of the file that defines the resolved domain names.
        **/
        static const std::string DOMAINS_FILE;

        /**
         * Constructor - this should parse the domains file.
        **/
        Resolver();

        /**
         * Resolves the given IP address.
        **/
        std::string resolve(const std::string& ip) const;

    private:

        /**
         * This private method is called from the constructor and is used to parse the configuration file.
        **/
        void parse_domains();

        /**
         * This map contains many pairs of IP addresses and their resolved domain.
        **/
        std::unordered_map<std::string, std::string> m_resolved;
};

#endif
