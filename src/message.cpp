/**
 * This is the implementation file of the base DNS message.
 * @author Itai Spiegel
**/

#include "message.hpp"
#include <iostream>

using DNS::Message;

/**
 * Receives a reference to the buffer of unsigned bytes, puts the given unsigned byte and increments the pointer.
**/
void Message::put8bits(uchar*& buffer, uchar value) {
    buffer[0] = value;
    buffer += 1;
}

/**
 * Calls twice the Message::put8bits function.
**/
void Message::put16bits(uchar*& buffer, ushort value) {
    put8bits(buffer, (uchar) ((value & 0xFF00) >> 8));
    put8bits(buffer, (uchar) (value & 0x00FF));
}

/**
 * Receives a reference to a buffer of unsigned bytes, returns the first value and increments the pointer.
**/
uchar Message::get8bits(uchar*& buffer) {
    uchar result = buffer[0];
    buffer += 1;

    return result;
}

/**
 * Basically calls twice the Message::get8bits function and returns the two values as an unsigned short.
**/
ushort Message::get16bits(uchar*& buffer) {

    // Get the first byte and left shift it by 8 bits.
    ushort c1 = static_cast<short>(get8bits(buffer));
    c1 = c1 << 8;

    // Add the second byte and return.
    uchar c2 = get8bits(buffer);
    return c1 + c2;
}

/**
 * Serializes the message instance to the given buffer.
**/
void Message::code_hdr(uchar* buffer) {
    put16bits(buffer, m_id);

    ushort flags = m_qr << 15;
    flags += m_opcode << 11;
    flags += m_aa << 10;
    flags += m_tc << 9;
    flags += m_rd << 8;
    flags += m_ra << 7;

    // The next 3 bytes are 0 since they are preserved for future use.

    flags += m_rcode;

    put16bits(buffer, flags);

    put16bits(buffer, m_qdCount);
    put16bits(buffer, m_anCount);
    put16bits(buffer, m_nsCount);
    put16bits(buffer, m_arCount);
}

/**
 * Deserializes the given buffer to the current message instance.
**/
void Message::decode_hdr(uchar* buffer) {
    m_id = get16bits(buffer);
    
    ushort flags = get16bits(buffer);

    m_rcode = flags & RCODE_MASK;
    m_ra = (flags & RA_MASK) >> 7;
    m_rd = (flags & RD_MASK) >> 8;
    m_tc = (flags & TC_MASK) >> 9;
    m_aa = (flags & AA_MASK) >> 10;
    m_opcode = (flags & OPCODE_MASK) >> 11;
    m_qr = (flags & QR_MASK) >> 15;
    
    m_qdCount = get16bits(buffer);
    m_anCount = get16bits(buffer);
    m_nsCount = get16bits(buffer);
    m_arCount = get16bits(buffer);
}


// Getters
ushort Message::get_id() const {
    return m_id;
}

ushort Message::get_qdCount() const {
    return m_qdCount;
}

ushort Message::get_anCount() const {
    return m_anCount;
}

ushort Message::get_nsCount() const {
    return m_nsCount;
}

ushort Message::get_arCount() const {
    return m_arCount;
}

// Setters
void Message::set_id(ushort id) { 
    m_id = id;
}

void Message::set_qdCount(ushort qd) {
    m_qdCount = qd;
}

void Message::set_anCount(ushort an) {
    m_anCount = an;
}

void Message::set_nsCount(ushort ns) {
    m_nsCount = ns;
}

void Message::set_arCount(ushort ar) {
    m_arCount = ar;
}
