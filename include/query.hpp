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

		enum Type : ushort {
			A = 1, AAAA = 28
		};

		Query() : Message(Message::Query) {}
		Query(Message::Type type) : Message(type) {}

		int code(char* buffer);
		void decode(char* buffer, size_t size);

		/**
		 * Parse the queried name.
		**/
		void decode_qname(char*& buffer);


		// Getters
		const std::string& get_qname() const;
		const Query::Type get_qtype() const;

	protected:
		std::string m_qname;
		Type m_qtype;
		ushort m_qclass;
	};
}

#endif //DNS_QUERY_H
