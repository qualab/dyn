// test scalar

#include <dyn/scalar.h>
#include <string>
#include "test.h"

namespace dyn
{
    TEST_SUITE(test_scalar_int)
    {
        scalar<int> i = 1234;
        TEST_CHECK(i) == 1234;
        TEST_CHECK(i) > 1233;
        TEST_CHECK(i) < 1235;
        TEST_CHECK_OPERATION(i.get<float>()).expect_exception<typecast_exception>();
        TEST_CHECK(i).is_true();
        TEST_CHECK(i.get<int>()) == 1234;
    }

    TEST_SUITE(test_scalar_float)
    {
        scalar<float> f = 56.789f;
        TEST_CHECK(f) == 56.789f;
        TEST_CHECK(f) != 56.788f;
        TEST_CHECK(f) >= 56.788f;
        TEST_CHECK(f) != 56.79f;
        TEST_CHECK(f) <= 56.79f;
        TEST_CHECK(f).is_true();
        TEST_CHECK(f.get<float>()) == 56.789f;
        TEST_CHECK_OPERATION(f.get<int>()).expect_exception<typecast_exception>();
    }

    TEST_SUITE(test_scalar_bool)
    {
        scalar<bool> b = true;
        TEST_CHECK(b).is_true();
        TEST_CHECK(!b).is_false();

        b = false;
        TEST_CHECK(b).is_false();
        TEST_CHECK(b).is_not();
    }

    TEST_SUITE(test_scalar_uint64)
    {
        scalar<unsigned long long> u = 1234567890uLL;
        TEST_CHECK(u) == 1234567890uLL;
        TEST_CHECK(u.get<unsigned long long>()) == 1234567890uLL;
        TEST_CHECK_OPERATION(u.get<long long>()).expect_exception<typecast_exception>();
    }

    TEST_SUITE(test_scalar_char)
    {
        scalar<char> c = '*';
        TEST_CHECK(c) == '*';
        TEST_CHECK(c) > '\0';
        TEST_CHECK(c) < '0';
        TEST_CHECK(c.get<char>()) == '*';
        TEST_CHECK_OPERATION(c.get<unsigned char>()).expect_exception<typecast_exception>();
    }

    struct biggest_good
    {
        // object::max_data_size - sizeof(virtual table pointer)
        static const size_t size = object::max_data_size - sizeof(void*);
        char bytes[size];
        operator bool() const { return true; }
    };

    template<> const char* const scalar<biggest_good>::class_name = "scalar<biggest_good>";
    template<> const char* const scalar<biggest_good>::data::class_name = "scalar<biggest_good>::data";

    template<> object& object::operator = (const biggest_good&) { return *this; }

    std::ostream& operator << (std::ostream& output, const biggest_good&) { return output; }

    TEST_SUITE(test_scalar_biggest_data)
    {
        TEST_CHECK_OPERATION(scalar<biggest_good> good).no_exception();
    }
}

// Unicode signature: Владимир Керимов
