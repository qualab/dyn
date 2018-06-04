// Test common integer class for basic operations

#include <dyn/integer.h>
#include <limits>
#include "test.h"

namespace dyn
{
    TEST_SUITE(test_integer_default)
    {
        integer none;
        TEST_CHECK(none) == 0;
        TEST_CHECK(none).is_false();
        TEST_CHECK(!none).is_true();
        integer zero;
        TEST_CHECK(zero) == 0;
        TEST_CHECK(none) == 0;
        TEST_CHECK(zero) == none;
    }

    TEST_SUITE(test_integer_initialization)
    {
        integer i64 = 1234567890123456789LL;
        TEST_CHECK(i64) == 1234567890123456789LL;
        integer s64 = -1234567890123456789LL;
        TEST_CHECK(s64) == -1234567890123456789LL;
        integer u64 = 12345678901234567890uLL;
        TEST_CHECK(u64) == 12345678901234567890uLL;
        integer i32 = 1234567890;
        TEST_CHECK(i32) == 1234567890;
        integer s32 = -1234567890;
        TEST_CHECK(s32) == -1234567890;
        integer u32 = 12345678901u;
        TEST_CHECK(u32) == 12345678901u;
        integer i16 = std::int16_t(12345);
        TEST_CHECK(i16) == std::int16_t(12345);
        integer s16 = std::int16_t(-12345);
        TEST_CHECK(s16) == std::int16_t(-12345);
        integer u16 = std::uint16_t(65432);
        TEST_CHECK(u16) == std::uint16_t(65432);
        integer i8 = std::int8_t(123);
        TEST_CHECK(i8) == std::int8_t(123);
        integer s8 = std::int8_t(-123);
        TEST_CHECK(s8) == std::int8_t(-123);
        integer u8 = std::uint8_t(234);
        TEST_CHECK(u8) == std::uint16_t(234);
    }

    TEST_SUITE(test_integer_assignment)
    {
        integer number;
        number = 1234567890123456789LL;
        TEST_CHECK(number) == 1234567890123456789LL;
        number = -1234567890123456789LL;
        TEST_CHECK(number) == -1234567890123456789LL;
        number = 12345678901234567890uLL;
        TEST_CHECK(number) == 12345678901234567890uLL;
        number = 1234567890;
        TEST_CHECK(number) == 1234567890;
        number = -1234567890;
        TEST_CHECK(number) == -1234567890;
        number = 12345678901u;
        TEST_CHECK(number) == 12345678901u;
        number = std::int16_t(12345);
        TEST_CHECK(number) == std::int16_t(12345);
        number = std::int16_t(-12345);
        TEST_CHECK(number) == std::int16_t(-12345);
        number = std::uint16_t(65432);
        TEST_CHECK(number) == std::uint16_t(65432);
        number = std::int8_t(123);
        TEST_CHECK(number) == std::int8_t(123);
        number = std::int8_t(-123);
        TEST_CHECK(number) == std::int8_t(-123);
        number = std::uint8_t(234);
        TEST_CHECK(number) == std::uint16_t(234);
    }

    TEST_SUITE(test_integer_addition)
    {
        integer o = 0;
        integer l = 1;
        TEST_CHECK(o + l) == 1;
        TEST_CHECK(l + o) == 1;
        TEST_CHECK(l + l) == 2;
        TEST_CHECK(o + o) == 0;
        integer x = 123456789012345678uLL;
        integer y = -23456789012345678LL;
        TEST_CHECK(x + y) == 100000000000000000uLL;
        integer z = 12345678901234567890uLL;
        TEST_CHECK_OPERATION(z + z).expect_exception<integer::arithmetic_overflow_exception>();
        integer U64max = std::numeric_limits<std::uint64_t>::max();
        TEST_CHECK_OPERATION(U64max + 1).expect_exception<integer::arithmetic_overflow_exception>();
        integer I64min = std::numeric_limits<std::int64_t>::min();
        integer I64max = std::numeric_limits<std::int64_t>::max();
        TEST_CHECK(U64max + I64min) == std::numeric_limits<std::int64_t>::max();
        TEST_CHECK(I64min + I64max) == -1;
        TEST_CHECK(I64min + l) == 1 + I64min;
        TEST_CHECK(l + I64min) == I64min + 1;
        TEST_CHECK(-1 + I64max) == I64max - l;
        integer big = 10000000000000000000uLL;
        integer neg = -1000000000000000000LL;
        TEST_CHECK(big + neg) == 9000000000000000000LL;
        TEST_CHECK(neg + big) == 9000000000000000000LL;
        TEST_CHECK_OPERATION(big + big).expect_exception<integer::arithmetic_overflow_exception>();
        TEST_CHECK(neg + neg) == -2000000000000000000LL;
        TEST_CHECK(big + 1.0e+19f) == 2.0e+19f;
        TEST_CHECK(neg + 1.1e+19) == 1.0e+19;
        TEST_CHECK(0.5f + l) == 1.5f;
        TEST_CHECK(0.1234567 + l) == 1.1234567;
        TEST_CHECK(123.456 + o) == 123.456;
        TEST_CHECK(o + 12.34f) == 12.34f;
    }

    TEST_SUITE(test_integer_subtraction)
    {
        integer o = 0;
        integer l = 1;
        TEST_CHECK(o - l) == -1;
        TEST_CHECK(l - o) == 1;
        TEST_CHECK(l - l) == 0;
        TEST_CHECK(o - o) == 0;
        integer I64min = std::numeric_limits<std::int64_t>::min();
        integer I64max = std::numeric_limits<std::int64_t>::max();
        TEST_CHECK_OPERATION(I64min - 1).expect_exception<integer::arithmetic_overflow_exception>();
        TEST_CHECK(I64max - l) == I64max - 1;
        TEST_CHECK(1 - I64max) == l - I64max;
        integer big = 10000000000000000000uLL;
        integer neg = -1000000000000000000LL;
        TEST_CHECK(big - neg) == 11000000000000000000uLL;
        TEST_CHECK_OPERATION(neg - big).expect_exception<integer::arithmetic_overflow_exception>();
        TEST_CHECK(big - big) == 0;
        TEST_CHECK(neg - neg) == 0;
        integer bigP1 = big + 1;
        integer negM1 = neg - 1;
        TEST_CHECK(big - bigP1) == -1;
        TEST_CHECK(neg - negM1) == 1;
        TEST_CHECK(bigP1 - big) == 1;
        TEST_CHECK(negM1 - neg) == -1;
        TEST_CHECK(big - 2.0e+19f) == -1.0e+19f;
        TEST_CHECK(neg - 1.0e+18) == -2.0e+18;
        TEST_CHECK(1.125f - l) == 0.125f;
        TEST_CHECK(321.0 - l) == 320.0;
        TEST_CHECK(123.456 - 0) == 123.456;
        TEST_CHECK(0 - 12.34f) == -12.34f;
    }

    TEST_SUITE(test_integer_negation)
    {
        integer o = 0;
        integer l = 1;
        integer m = -1;
        TEST_CHECK(-o) == 0;
        TEST_CHECK(-l) == -1;
        TEST_CHECK(-m) == 1;
        integer I64min = std::numeric_limits<std::int64_t>::min();
        integer I64max = std::numeric_limits<std::int64_t>::max();
        TEST_CHECK(-I64min) == static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::min());
        TEST_CHECK(-I64max) == -std::numeric_limits<std::int64_t>::max();
        integer big = 10000000000000000000uLL;
        integer neg = -1000000000000000000LL;
        TEST_CHECK_OPERATION(-big).expect_exception<integer::arithmetic_overflow_exception>();
        TEST_CHECK(-neg) == 1000000000000000000LL;
    }

    TEST_SUITE(test_integer_multiplication)
    {
        integer o = 0, l = 1, m = -1;
        TEST_CHECK(o * l) == 0;
        TEST_CHECK(l * o) == 0;
        TEST_CHECK(o * m) == 0;
        TEST_CHECK(m * o) == 0;
        TEST_CHECK(o * o) == 0;
        TEST_CHECK(l * l) == 1;
        TEST_CHECK(m * l) == -1;
        TEST_CHECK(l * m) == -1;
        TEST_CHECK(m * m) == 1;
        integer U64max = std::numeric_limits<std::uint64_t>::max();
        TEST_CHECK(U64max * 1) == std::numeric_limits<std::uint64_t>::max();
        TEST_CHECK(1 * U64max) == std::numeric_limits<std::uint64_t>::max();
        TEST_CHECK(U64max * 0) == 0;
        TEST_CHECK(0 * U64max) == 0;
        TEST_CHECK_OPERATION(U64max * (-1)).expect_exception<integer::arithmetic_overflow_exception>();
        TEST_CHECK_OPERATION(-1 * U64max).expect_exception<integer::arithmetic_overflow_exception>();
        integer I64min = std::numeric_limits<std::int64_t>::min();
		integer I64max = std::numeric_limits<std::int64_t>::max();
		TEST_CHECK(I64min * 1) == std::numeric_limits<std::int64_t>::min();
		TEST_CHECK(-1 * I64min) == static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::min());
		TEST_CHECK(1 * I64max) == std::numeric_limits<std::int64_t>::max();
		TEST_CHECK(I64max * (-1)) == -std::numeric_limits<std::int64_t>::max();
		integer I32min = std::numeric_limits<std::int32_t>::min();
		integer I32max = std::numeric_limits<std::int32_t>::max();
		TEST_CHECK(I32min * I32min) == 1uLL << 62;
		TEST_CHECK(I32max * I32max) == (1uLL << 62) - (1uLL << 32) + 1;
		TEST_CHECK(I32max * I32min) == -((1LL << 62) - (1LL << 31));
		TEST_CHECK(I32min * I32max) == -((1LL << 62) - (1LL << 31));
		integer U32max = std::numeric_limits<std::uint32_t>::max();
		integer U32lim = 1uLL << 32;
		TEST_CHECK(U32max * U32max) == (1uLL << 33) * ((1uLL << 31) - 1) + 1;
		TEST_CHECK_OPERATION(U32lim * U32lim).expect_exception<integer::arithmetic_overflow_exception>();
		TEST_CHECK(U32max * U32lim) == (1uLL << 32) * ((1uLL << 32) - 1);
		integer big = 10000000000000000000uLL;
		integer neg = -1000000000000000000LL;
		TEST_CHECK_OPERATION(big * neg).expect_exception<integer::arithmetic_overflow_exception>();
		TEST_CHECK(big * 1) == 10000000000000000000uLL;
        TEST_CHECK(big * 0) == 0;
        TEST_CHECK_OPERATION(big * 10).expect_exception<integer::arithmetic_overflow_exception>();
		TEST_CHECK_OPERATION(big * (-1)).expect_exception<integer::arithmetic_overflow_exception>();
		TEST_CHECK(1 * neg) == -1000000000000000000LL;
		TEST_CHECK_OPERATION(10 * neg).expect_exception<integer::arithmetic_overflow_exception>();
		TEST_CHECK(-10 * neg) == 10000000000000000000uLL;
	}

    TEST_SUITE(test_integer_division)
    {
        integer o = 0;
        integer l = 1;
        integer m = -1;
        TEST_CHECK(o / l) == 0;
        TEST_CHECK_OPERATION(l / o).expect_exception<integer::arithmetic_overflow_exception>();
        TEST_CHECK(o / m) == 0;
        TEST_CHECK_OPERATION(m / o).expect_exception<integer::arithmetic_overflow_exception>();
        TEST_CHECK(l / m) == -1;
        TEST_CHECK(m / l) == -1;
        TEST_CHECK(l / l) == 1;
        TEST_CHECK(m / m) == 1;
        TEST_CHECK_OPERATION(o / o).expect_exception<integer::arithmetic_overflow_exception>();
        integer I64min = std::numeric_limits<std::int64_t>::min();
        integer I64max = std::numeric_limits<std::int64_t>::max();
        TEST_CHECK(I64max / I64min) == 0;
        TEST_CHECK(I64min / I64max) == -1;
        TEST_CHECK(I64max / 1) == std::numeric_limits<std::int64_t>::max();
        TEST_CHECK(I64min / 1) == std::numeric_limits<std::int64_t>::min();
        TEST_CHECK(I64max / 128) == (1LL << 56) - 1;
        TEST_CHECK(I64min / 32) == -(1LL << 58);
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
        TEST_CHECK_OPERATION(x = 1.0e+20f).expect_exception<integer::out_of_range_exception_of<float>>();
        TEST_CHECK_OPERATION(x = -9.9e+18f).expect_exception<integer::out_of_range_exception_of<float>>();
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
        TEST_CHECK_OPERATION(x = 1.0e+20).expect_exception<integer::out_of_range_exception_of<double>>();
        TEST_CHECK_OPERATION(x = -9.9e+18).expect_exception<integer::out_of_range_exception_of<double>>();
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
