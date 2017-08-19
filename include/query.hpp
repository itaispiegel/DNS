/**
 * This subclass of the abstract DNS message implements a DNS query message.
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

		/**
		 * Parse the queried name.
		**/
		void decode_qname(char*& buffer);

	protected:
		std::string m_qname;
		ushort m_qtype;
		ushort m_qclass;
	};
}

#endif //DNS_QUERY_H
