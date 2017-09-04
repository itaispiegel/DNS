/**
 * This class represents a DNS query response and inherits from the Query class since the query is contained
 * in the response body.
 *
 * @author Itai Spiegel
**/

#ifndef RESPONSE_H
#define RESPONSE_H

#include "query.hpp"

using DNS::Message;
using DNS::Query;

namespace DNS {
	class Response : public Query {
		public:
			Response() : Query(Message::Response) { }

			/**
			 * Copy contructor from query instance.
			 * TODO Rule of three - need to also implement destructor and copy assignment operator.
			**/
			explicit Response(const Query& query);

			/**
			 * Receives an IP address, for example: 10.0.0.138 and parses the value to the member m_rdata, so it will hold: \x0a\x00\x00\x8a
			 **/
			void parse_ip_address(const std::string& ip);


			size_t code(char* buffer);
			void decode(char* buffer, size_t size);
	
		protected:
			ushort m_name;
			uint m_ttl;
			uint m_rdlength;
			uchar m_rdata[4];

			/**
			 * Codes the query name to the given buffer/
			 **/
			void code_qname(char*& buffer, const std::string& qname);
	};
}

#endif
