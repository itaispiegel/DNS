/**
 * This file contains some tests for the base DNS message class.
 * @author Itai Spiegel
**/

#include <gtest/gtest.h>
#include "message.hpp"

using DNS::Message;

class TestMessage : public Message, public ::testing::Test {
public:
    TestMessage() : Message(Message::Type::Response) {}

    // This shouldn't be called.
    int code(uchar* buffer) {
        return 0;
    }

    // This shouldn't be called.
    void decode(uchar* buffer, size_t size) {
    }

protected:

    /**
     * Setup a mock message.
     */
    virtual void SetUp() {
        m_id = 7414;
        m_opcode = 11;
        m_aa = true;
        m_tc = false;
        m_rd = true;
        m_ra = true;
        m_rcode = 4;
        m_qdCount = 24156;
        m_anCount = 8317;
        m_nsCount = 4219;
        m_arCount = 4753;
    }
};


/**
 * Test the put 16 bits function of the message.
 */
TEST_F(TestMessage, TestPut16Bits) {

    // The size in bits we are comparing
    const size_t cmp_size = 16;

    // Initialize the new buffer and the expected buffer.
    uchar* buffer = new uchar[cmp_size];
    uchar* orig_buffer = buffer;
    uchar expected[cmp_size] = {0x1c, 0xf6};

    // Put the expected bytes in the buffer
    Message::put16bits(buffer, 7414);

    // Compare the results
    int result = memcmp(orig_buffer, expected, cmp_size / 8);
    ASSERT_EQ(result, 0);

    delete[] orig_buffer;
}

/**
 * Test that getting 16 bits from a given buffer returns the expected result.
 */
TEST_F(TestMessage, TestGet16bits) {
    size_t bytes_compared = 16;

    // Initialize a new buffer.
    uchar* orig_buffer = new uchar[bytes_compared];
    orig_buffer[0] = 0x54;
    orig_buffer[1] = 0xf8;

    // Save a pointer to the original buffer.
    uchar* buffer = orig_buffer;

    // Get the actual result.
    ushort expected = 0x54f8;
    ushort actual = Message::get16bits(buffer);

    // Compare the actual and expected results.
    ASSERT_EQ(expected, actual);

    // Delete the original buffer.
    delete[] orig_buffer;
}

/**
 * Test that serializing a message to a byte array gives the expected value.
 */
TEST_F(TestMessage, TestHeaderSerialization) {
    uchar* buffer = new uchar[Message::HEADER_SIZE];
    Message::code_hdr(buffer);

    uchar expected[Message::HEADER_SIZE] = {0x1c, 0xf6, 0xdd, 0x84, 0x5e, 0x5c, 0x20, 0x7d, 0x10, 0x7b, 0x12, 0x91};
    ASSERT_EQ(memcmp(buffer, expected, Message::HEADER_SIZE), 0);

    delete[] buffer;
}

/**
 * Test that deserializing a mock buffer to the message mock gives the expected results.
**/
TEST_F(TestMessage, TestHeaderDeserialization) {
    uchar buffer[Message::HEADER_SIZE] = {0x29, 0xe9, 0xcb, 0x11, 0xae, 0xa7, 0xb3, 0x19, 0x14, 0x77, 0x22, 0x11};

    Message::decode_hdr(buffer);
    EXPECT_EQ(Message::get_id(), 10729);

    EXPECT_EQ(m_qr, Type::Response);
    EXPECT_EQ(m_opcode, 9);
    EXPECT_EQ(m_aa, 0);
    EXPECT_EQ(m_tc, 1);
    EXPECT_EQ(m_rd, 1);
    EXPECT_EQ(m_ra, 0);
    EXPECT_EQ(m_rcode, 1);

    EXPECT_EQ(Message::get_qdCount(), 44711);
    EXPECT_EQ(Message::get_anCount(), 45849);
    EXPECT_EQ(Message::get_nsCount(), 5239);
    EXPECT_EQ(Message::get_arCount(), 8721);
}
*/
