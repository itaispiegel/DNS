/**
 * This file contains some tests for the DNS query message class.
 * @author Itai Spiegel
**/

#include <gtest/gtest.h>
#include "query.hpp"

using DNS::Query;

class TestQuery : public ::testing::Test {
protected:
	
	virtual void SetUp() {
	}
	Query m_query;
};
