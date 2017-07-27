//
// Created by itai on 7/8/17.
//

#include "Message.h"
#include <iostream>

using DNS::Message;

void Message::put8bits(uchar*& buffer, uchar value) {
    buffer[0] = value;
    buffer += 1;
}

void Message::put16bits(uchar*& buffer, ushort value) {
    put8bits(buffer, (uchar) ((value & 0xFF00) >> 8));
    put8bits(buffer, (uchar) (value & 0x00FF));
}

uchar Message::get8bits(uchar*& buffer) {
    uchar result = buffer[0];
    buffer += 1;

    return result;
}

ushort Message::get16bits(uchar*& buffer) {

    // Get the first byte and left shift it by 8 bits.
    ushort c1 = static_cast<short>(get8bits(buffer));
    c1 = c1 << 8;

    // Add the second byte and return.
    uchar c2 = get8bits(buffer);
    return c1 + c2;
}

void Message::code_hdr(uchar* buffer) {
    put16bits(buffer, m_id);

    ushort flags = m_type << 15;
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

void Message::decode_hdr(uchar* buffer) {

}

ushort Message::get_id() const {
    return m_id;
}

void Message::set_id(ushort id) {
    Message::m_id = id;
}

Message::Type Message::get_type() const {
    return m_type;
}

void Message::set_type(Message::Type type) {
    Message::m_type = type;
}


uchar Message::get_opcode() const {
    return m_opcode;
}

void Message::set_opcode(uchar opcode) {
    Message::m_opcode = opcode;
}

bool Message::is_aa() const {
    return m_aa;
}

void Message::set_aa(bool aa) {
    Message::m_aa = aa;
}

bool Message::is_truncated() const {
    return m_tc;
}

void Message::set_truncation(bool truncation) {
    Message::m_tc = truncation;
}

bool Message::is_recursion_desired() const {
    return m_rd;
}

void Message::set_recursion_desired(bool rd) {
    Message::m_rd = rd;
}

bool Message::is_recursion_available() const {
    return m_ra;
}

void Message::set_recursion_available(bool ra) {
    Message::m_ra = ra;
}

uchar Message::get_response_code() const {
    return m_rcode;
}

void Message::set_response_code(uchar response) {
    Message::m_rcode = response;
}

ushort Message::get_qd_count() const {
    return m_qdCount;
}

void Message::set_qd_count(ushort qd_count) {
    Message::m_qdCount = qd_count;
}

ushort Message::get_an_count() const {
    return m_anCount;
}

void Message::set_an_count(ushort an_count) {
    Message::m_anCount = an_count;
}

ushort Message::get_ns_count() const {
    return m_nsCount;
}

void Message::set_ns_count(ushort ns_count) {
    Message::m_nsCount = ns_count;
}

ushort Message::get_ar_count() const {
    return m_arCount;
}

void Message::set_ar_count(ushort ar_count) {
    Message::m_arCount = ar_count;
}
