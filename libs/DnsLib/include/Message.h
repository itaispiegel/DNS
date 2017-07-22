//
// Created by itai on 7/8/17.
//

#ifndef DNS_MESSAGE_H
#define DNS_MESSAGE_H

#include "Types.h"
#include <stddef.h>

namespace DNS {

    class Message {
    public:

        // The header size in bytes
        static const size_t HEADER_SIZE = 12;

        /**
         * The type of DNS message.
         */
        enum Type {
            Query = 0, Response = 1
        };

        /**
         * Default constructor.
         */
        Message() = default;

        /**
         * Constructor
         * @param type The type of the DNS message.
         */
        Message(Type type) : m_type(type) {}

        /**
         * Code the DNS message header section.
         * @param buffer The buffer to code the message header to.
         */
        void code_hdr(uchar* buffer);

        /**
         * Decode the given buffer into the current instance.
         * @param buffer The buffe to decode.
         */
        void decode_hdr(uchar* buffer);

        /**
         * Puts the 8 bits into the buffer.
         * @param buffer
         * @param value
         */
        void put8bits(uchar*& buffer, uchar value);

        /**
         * Puts the 16 bits into the buffer.
         * @param buffer
         * @param value
         */
        void put16bits(uchar*& buffer, ushort value);

        /**
         * Returns the next 8 bits of the buffer.
         * @param buffer The buffer to get the bits from.
         * @return
         */
        uchar get8bits(uchar*& buffer);

        /**
         * Returns the next 16 bits of the buffer.
         * @param buffer The buffer to get the bits from.
         * @return
         */
        ushort get16bits(uchar*& buffer);

        ushort get_id() const;

        void set_id(ushort id);

        Type get_type() const;

        void set_type(Type type);

        uchar get_opcode() const;

        void set_opcode(uchar opcode);

        bool is_aa() const;

        void set_aa(bool aa);

        bool is_truncated() const;

        void set_truncation(bool truncation);

        bool is_recursion_desired() const;

        void set_recursion_desired(bool rd);

        bool is_recursion_available() const;

        void set_recursion_available(bool ra);

        uchar get_response_code() const;

        void set_response_code(uchar response);

        ushort get_qd_count() const;

        void set_qd_count(ushort qd_count);

        ushort get_an_count() const;

        void set_an_count(ushort an_count);

        ushort get_ns_count() const;

        void set_ns_count(ushort ns_count);

        ushort get_ar_count() const;

        void set_ar_count(ushort ar_count);

    protected:

        /**
         * The first two bytes represent the ID that the client generated.
         */
        ushort m_id;

        /**
         * This bit represents whether this message is a query or a response.
         */
        Type m_type;

        /**
         * These 4 bytes represent the type of query:
         *
         * <table>
         * <tr>
         * <th>Value</th>
         * <th>Meaning</th>
         * <tr>
         * <td>0</td>
         * <td>Standard query (QUERY)</td>
         * </tr>
         * <tr>
         * <td>1</td>
         * <td>Inverse query (IQUERY)</td>
         * </tr>
         * <tr>
         * <td>2</td>
         * <td>Server status request (STATUS)</td>
         * </tr>
         * <tr>
         * <td>3-15</td>
         * <td>Reserved for future use.</td>
         * </tr>
         * </table>
         */
        uchar m_opcode;

        /**
         * Authoritative Answer - this bit is valid in responses, and specifies
         * that the responding name server is an authority for the domain name in question section.
         */
        bool m_aa;

        /**
         * Truncation - specifies that this message was truncated due to length greater
         * than that permitted on the transmission channel.
         */
        bool m_tc;

        /**
         * Recursion Desired - This bit may be set in a query and is copied into the response.
         * If it is set, it directs the name server to pursue the query recursively.
         * Recursive query support is optional.
         */
        bool m_rd;

        /**
         * Recursion Available - This bit is set or cleared in a response and denotes whether recursive query
         * support is available in the name server.
         */
        bool m_ra;

        /**
         * Response Code - this 4 bit field is set as part of responses.
         *
         * <table>
         * <tr>
         * <th>Value</th>
         * <th>Meaning</th>
         * <tr>
         * <td>0</td>
         * <td>No error condition</td>
         * </tr>
         * <tr>
         * <td>1</td>
         * <td>Format Error - the name server was unable to interpret the query.</td>
         * </tr>
         * <tr>
         * <td>2</td>
         * <td>Server Failure - The name server was unable to process this query due to a
         * problem with the name server.</td>
         * </tr>
         * <tr>
         * <td>3</td>
         * <td>Name Error - Meaningful only for responses from an authoritative name server, this code
         * signifies that the domain name referenced in the query does not exist.</td>
         * </tr>
         * <tr>
         * <td>4</td>
         * <td>Not Implemented - The name server does not support the requested kind of query.</td>
         * </tr>
         * <tr>
         * <td>5</td>
         * <td>Refused - The name server refuses to perform the specified operation for policy reasons. For example, a name
         * server may not wish to provide the information to the particular requester,
         * or a name server may not wish to perform a particular operation.</td>
         * </tr>
         * </table>
         */
        uchar m_rcode;

        /**
         * An unsigned 16 bit integer specifying the number of entries in the question section.
         */
        ushort m_qdCount;

        /**
         * An unsigned 16 bit integer specifying the number of resource records in the answer section.
         */
        ushort m_anCount;

        /**
         * An unsigned 16 bit integer specifying the number of name server resource records in the authority
         * records section.
         */
        ushort m_nsCount;

        /**
         * An unsigned 16 bit integer specifying the number of resource records in the additional
         * records section.
         */
        ushort m_arCount;
    };
}
#endif //DNS_MESSAGE_H
