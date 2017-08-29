/**
 * This class represents an abstract DNS message and basically has a subclass for a query and for a response.
 * @author Itai Spiegel
**/

#ifndef DNS_MESSAGE_H
#define DNS_MESSAGE_H

#include "types.hpp"
#include "component.hpp"
#include <stddef.h>

namespace DNS {
    class Message : public Component {
    public:

        // The header size in bytes
        static const size_t HEADER_SIZE = 12;

        /**
         * The type of DNS message.
         */
        enum Type : char {
            Query = 0, Response = 1
        };

        /**
         * Pure virtual function that will code the DNS message into the given buffer.
         * @param buffer The buffer to code to.
         * @return The size of the coded message.
        **/
        virtual size_t code(char* buffer) = 0;

        /**
         * Pure virtual function that will decode the given buffer into the current message instance.
         * @param buffer The buffer to decode.
         * @param size The size of the buffer.
        **/
        virtual void decode(char* buffer, size_t size) = 0;

        /**
         * Code the DNS message header section.
         * @param buffer The buffer to code the message header to.
         */
        void code_hdr(char* buffer);

        /**
         * Decode the given buffer into the current instance.
         * @param buffer The buffe to decode.
         */
        void decode_hdr(char* buffer);

        /**
         * Puts the given 8 bits into the given buffer.
         * @param buffer The buffer to put the bits into.
         * @param value The value to put into the buffer.
         */
        void put8bits(char*& buffer, char value);

        /**
         * Puts the 16 bits into the buffer.
         * @param buffer The buffer to put the bits into.
         * @param value The value to put into the buffer.
         */
        void put16bits(char*& buffer, ushort value);

        /**
         * Puts the 32 bits into the buffer.
         * @param buffer The buffer to put the bits into.
         * @param value The value to put into the buffer.
         */
        void put32bits(char*& buffer, uint value);

        /**
         * Returns the next 8 bits of the buffer.
         * @param buffer The buffer to get the bits from.
         * @return The next 8 bits of the buffer.
         */
        char get8bits(char*& buffer);

        /**
         * Returns the next 16 bits of the buffer.
         * @param buffer The buffer to get the bits from.
         * @return The next 16 bits of the buffer.
         */
        ushort get16bits(char*& buffer);

        /**
         * Returns the next 32 bits of the buffer.
         * @param buffer The buffer to get the bits from.
         * @return The next 32 bits of the buffer.
         */
        uint get32bits(char*& buffer);

        // Getters
        ushort get_id() const;
        ushort get_qdCount() const;
        ushort get_anCount() const;
        ushort get_nsCount() const;
        ushort get_arCount() const;

        // Setters
        void set_id(ushort id);
        void set_qdCount(ushort qd);
        void set_anCount(ushort an);
        void set_nsCount(ushort ns);
        void set_arCount(ushort ar);

    protected:

        /**
         * Constructor
         * @param type The type of the DNS message.
         */
        Message(Type type) : m_qr(type) {}

        /**
         * Destructor
        **/
        virtual ~Message() { }

        /**
         * The first two bytes represent the ID that the client generated.
         */
        ushort m_id;

        /**
         * This bit represents whether this message is a query or a response.
         */
        bool m_qr;

        /**
         * 4 Bit field which represents the type of query message:
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
        char m_opcode;

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
        char m_rcode;

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

    private:
        static const ushort RCODE_MASK = 0xF;
        static const ushort RA_MASK = 0x80;
        static const ushort RD_MASK = 0x160;
        static const ushort TC_MASK = 0x320;
        static const ushort AA_MASK = 0x640;
        static const ushort OPCODE_MASK = 0x7800;
        static const ushort QR_MASK = 0x8000;
    };
}

#endif //DNS_MESSAGE_H
