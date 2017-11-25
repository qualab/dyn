// test scalar

#include <dyn/scalar.h>
#include <string>
#include "test.h"

namespace dyn
{
    TEST_SUITE(test_scalar_int)
    {
        scalar<int> i = 1234;
        test::equal<test::fail>(i, 1234);
        test::greater<test::fail>(i, 1233);
        test::less<test::fail>(i, 1235);
        test::expect_exception<object::representation_exception<scalar<float>::data>, test::fail>(
            std::function<void()>(
                [i]()
                {
                    i.get<float>();
                }
            )
        );
        test::is_true<test::fail>(i);
        test::equal<test::fail>(i.get<int>(), 1234);
    }

    TEST_SUITE(test_scalar_float)
    {
        scalar<float> f = 56.789f;
        test::equal<test::fail>(f, 56.789f);
        test::not_less<test::fail>(f, 56.788f);
        test::not_greater<test::fail>(f, 56.790f);
        test::is_true<test::fail>(f);
        test::equal<test::fail>(f.get<float>(), 56.789f);

        test::expect_exception<object::representation_exception<scalar<int>::data>, test::fail>(
            std::function<void()>(
                [f]()
                {
                    f.get<int>();
                }
            )
        );
    }

    TEST_SUITE(test_scalar_bool)
    {
        scalar<bool> b = true;
        test::is_true<test::fail>(b);
        test::is_false<test::fail>(!b);

        b = false;
        test::is_false<test::fail>(b);
        test::is_true<test::fail>(!b);
    }

    TEST_SUITE(test_scalar_uint64)
    {
        scalar<unsigned long long> u = 1234567890uLL;
        test::equal<test::fail>(u, 1234567890uLL);
        test::equal<test::fail>(u.get<unsigned long long>(), 1234567890uLL);

        test::expect_exception<object::representation_exception<scalar<long long>::data>, test::fail>(
            std::function<void()>(
                [u]()
                {
                    u.get<long long>();
                }
            )
        );
    }

    TEST_SUITE(test_scalar_char)
    {
        scalar<char> c = '*';
        test::equal<test::fail>(c, '*');
        test::equal<test::fail>(c.get<char>(), '*');

        test::expect_exception<object::representation_exception<scalar<unsigned char>::data>, test::fail>(
            std::function<void()>(
                [c]()
                {
                    c.get<unsigned char>();
                }
            )
        );
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
        test::no_exeption<test::fail>(
            std::function<void()>([&]()
            {
                scalar<biggest_good> good;
            })
        );

        test::expect_exception<object::data_size_exception<scalar<least_bad>::data>, test::fail>(
            std::function<void()>([&]()
            {
                scalar<least_bad> bad;
            })
        );
    }
}

// Unicode signature: Владимир Керимов
