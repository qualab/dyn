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
        TEST_CHECK([i]() {
            i.get<float>();
        }).expect_exception<object::representation_exception_of<scalar<float>::data>>();
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
        TEST_CHECK([f]() {
            f.get<int>();
        }).expect_exception<object::representation_exception_of<scalar<int>::data>>();
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
        TEST_CHECK([u]() {
            u.get<long long>();
        }).expect_exception<object::representation_exception_of<scalar<long long>::data>>();
    }

    TEST_SUITE(test_scalar_char)
    {
        scalar<char> c = '*';
        TEST_CHECK(c) == '*';
        TEST_CHECK(c) > '\0';
        TEST_CHECK(c) < '0';
        TEST_CHECK(c.get<char>()) == '*';
        TEST_CHECK([c]() {
            c.get<unsigned char>();
        }).expect_exception<object::representation_exception_of<scalar<unsigned char>::data>>();
    }

    struct biggest_good
    {
        // object::max_data_size - sizeof(virtual table pointer)
        static const size_t size = object::max_data_size - sizeof(void*);
        char bytes[size];
        operator bool() const { return true; }
    };

    struct least_bad
    {
        static const size_t size = biggest_good::size + 1;
        char bytes[size];
        operator bool() const { return true; }
    };

    template<> object& object::operator = (const biggest_good&) { return *this; }
    template<> object& object::operator = (const least_bad&) { return *this; }

    std::ostream& operator << (std::ostream& output, const biggest_good&) { return output; }
    std::ostream& operator << (std::ostream& output, const least_bad&) { return output; }

    TEST_SUITE(test_scalar_biggest_data)
    {
        TEST_CHECK([]() {
            scalar<biggest_good> good;
        }).no_exception();
        TEST_CHECK([]() {
            scalar<least_bad> bad;
        }).expect_exception<object::data_size_exception_of<scalar<least_bad>::data>>();
    }
}

// Unicode signature: Владимир Керимов
