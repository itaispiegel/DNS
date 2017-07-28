//
// Created by itai on 7/22/17.
//

#ifndef DNS_QUERY_H
#define DNS_QUERY_H

#include "message.h"
#include "Types.h"
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
