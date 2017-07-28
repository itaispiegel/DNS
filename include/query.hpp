/**
 * This this subclass of the abstract DNS message implements a DNS query message.
 * @author Itai Spiegel
**/

#ifndef DNS_QUERY_H
#define DNS_QUERY_H

#include "message.hpp"
#include "types.hpp"
#include <string>

using DNS::Message;

class Query : public Message {
public:
    Query() : Message(Type::Query) {}

protected:
    std::string m_query;
    ushort m_qtype;
    ushort m_qclass;
};

#endif //DNS_QUERY_H
