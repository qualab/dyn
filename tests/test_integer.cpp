// test shared reference with copy-on-write mechanism

#include <dyn/integer.h>
#include <limits>
#include "test.h"

namespace dyn
{
    TEST_SUITE(test_integer_default)
    {
        integer n;
        TEST_CHECK(n).is_false();
        integer z;
        TEST_CHECK(n) == integer(0);
    }

    TEST_SUITE(test_integer_initialization)
    {
        integer x = 123;
        TEST_CHECK(x) == integer(123);
        integer c = 1234567890uLL;
        TEST_CHECK(c) == integer(1234567890uLL);
    }

	TEST_SUITE(test_integer_addition)
	{
		integer x = 123456789012345678uLL;
		integer y = -23456789012345678LL;
		TEST_CHECK(x + y) == integer(100000000000000000uLL);
		integer z = 12345678901234567890uLL;
		TEST_CHECK([z]() { z + z; }).expect_exception<integer::arithmetic_overflow_exception>();
		integer U64max = std::numeric_limits<std::uint64_t>::max();
		TEST_CHECK([U64max]() { U64max + integer(1); }).expect_exception<integer::arithmetic_overflow_exception>();
		integer I64min = std::numeric_limits<std::int64_t>::min();
		TEST_CHECK([I64min]() { I64min + integer(-1); }).expect_exception<integer::arithmetic_overflow_exception>();
		integer I64max = std::numeric_limits<std::int64_t>::max();
		TEST_CHECK(U64max + I64min) == I64max;
		TEST_CHECK(I64min + I64max) == integer(-1);
	}
}

// Unicode signature: Владимир Керимов
