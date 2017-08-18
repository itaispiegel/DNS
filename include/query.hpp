/**
 * This this subclass of the abstract DNS message implements a DNS query message.
 * @author Itai Spiegel
**/

#ifndef DNS_QUERY_H
#define DNS_QUERY_H

#include <string>
#include "message.hpp"
#include "types.hpp"

using DNS::Message;

namespace DNS {
	class Query : public Message {
	public:
		Query() : Message(Type::Query) {}

		int code(char* buffer);
		void decode(char* buffer, size_t size);

	protected:
		std::string m_query;
		ushort m_qtype;
		ushort m_qclass;
	};
}

#endif //DNS_QUERY_H
