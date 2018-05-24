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
        x = 9.99999e+18f;
        TEST_CHECK(x) == 9999990000000000000uLL;
        TEST_CHECK([&x]() { x = 1.0e+20f; }).expect_exception<integer::out_of_range_exception_of<float>>();
        TEST_CHECK([&x]() { x = -9.9e+18f; }).expect_exception<integer::out_of_range_exception_of<float>>();
        x = 0.0f;
        TEST_CHECK(x) == 0;
        x = 1.0f;
        TEST_CHECK(x) == 1;
        x = -1.0f;
        TEST_CHECK(x) == -1;
        x = -654321.0f;
        TEST_CHECK(x) == -654321;
        x = 1234.56f;
        TEST_CHECK(x) == 1234;
    }

    TEST_SUITE(test_integer_double)
    {
        integer x(1234567890.12345e+5);
        TEST_CHECK(x) == 123456789012345LL;
        x = 9.00000000000001e+14;
        TEST_CHECK(x) == 900000000000001LL;
        x = -9.22337203685477e+18;
        TEST_CHECK(x) == -9223372036854770000LL;
        x = 9.22337203685477e+18;
        TEST_CHECK(x) == 9223372036854770000LL;
        x = 1.84467440737095e+19;
        TEST_CHECK(x) == 18446744073709500000uLL;
        x = 2.00400600800501e+14;
        TEST_CHECK(x) == 200400600800501LL;
        x = -5.00000000000001e+17;
        TEST_CHECK(x) == -500000000000001000LL;
        x = 9.99999999999999e+18;
        TEST_CHECK(x) == 9999999999999990000uLL;
        TEST_CHECK([&x]() { x = 1.0e+20; }).expect_exception<integer::out_of_range_exception_of<double>>();
        TEST_CHECK([&x]() { x = -9.9e+18; }).expect_exception<integer::out_of_range_exception_of<double>>();
        x = 0.123;
        TEST_CHECK(x) == 0;
        x = 3.14159265358979e+14;
        TEST_CHECK(x) == 314159265358979LL;
        x = -123.45;
        TEST_CHECK(x) == -123;
        x = 1000000789.01234e+5;
        TEST_CHECK(x) == 100000078901234LL;
        x = 0.0;
        TEST_CHECK(x) == 0;
        x = 1.0;
        TEST_CHECK(x) == 1;
        x = -1.0;
        TEST_CHECK(x) == -1;
        x = -987654321.0;
        TEST_CHECK(x) == -987654321LL;
    }
}

// Unicode signature: Владимир Керимов
