// Test common integer class for basic operations

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
        TEST_CHECK(n) == 0;
    }

    TEST_SUITE(test_integer_initialization)
    {
        integer x = 123;
        TEST_CHECK(x) == 123;
        integer c = 1234567890uLL;
        TEST_CHECK(c) == 1234567890uLL;
    }

    TEST_SUITE(test_integer_addition)
    {
        integer x = 123456789012345678uLL;
        integer y = -23456789012345678LL;
        TEST_CHECK(x + y) == 100000000000000000uLL;
        integer z = 12345678901234567890uLL;
        TEST_CHECK([z]() { z + z; }).expect_exception<integer::arithmetic_overflow_exception>();
        integer U64max = std::numeric_limits<std::uint64_t>::max();
        TEST_CHECK([U64max]() { U64max + 1; }).expect_exception<integer::arithmetic_overflow_exception>();
        integer I64min = std::numeric_limits<std::int64_t>::min();
        TEST_CHECK([I64min]() { I64min - 1; }).expect_exception<integer::arithmetic_overflow_exception>();
        integer I64max = std::numeric_limits<std::int64_t>::max();
        TEST_CHECK(U64max + I64min) == std::numeric_limits<std::int64_t>::max();
        TEST_CHECK(I64min + I64max) == -1;
    }

    TEST_SUITE(test_integer_float)
    {
        integer x(0.5f);
        TEST_CHECK(x) == 0;
        x = 3.14f;
        TEST_CHECK(x) == 3;
        x = integer(-1.23f);
        TEST_CHECK(x) == -1;
        x = 1.84467e+19f;
        TEST_CHECK(x) == 18446700000000000000uLL;
        x = 9.22337e+18f;
        TEST_CHECK(x) == 9223370000000000000LL;
        x = -9.22337e+18f;
        TEST_CHECK(x) == -9223370000000000000LL;
        x = 234567.f;
        TEST_CHECK(x) == 234567;
        x = -9.87654e+5f;
        TEST_CHECK(x) == -987654;
        x = 3.0709e+10f;
        TEST_CHECK(x) == 30709000000;
        x = -6.00001e+7;
        TEST_CHECK(x) == -60000100;
    }
}

// Unicode signature: Владимир Керимов
