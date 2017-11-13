// test scalar

#include <dyn/scalar.h>
#include <string>
#include "test.h"

namespace dyn
{
    struct biggest_good
    {
        // object::max_data_size - sizeof(virtual table pointer)
        static const size_t size = object::max_data_size - sizeof(void*);
        char bytes[size];
    };

    struct least_bad
    {
        static const size_t size = biggest_good::size + 1;
        char bytes[size];
    };

    template<> object& object::operator = (biggest_good) { return *this; }
    template<> object& object::operator = (least_bad) { return *this; }

    TEST_SUITE(test_scalar)
    {
        scalar<int> i = 1234;
        test::equal<test::fail>(i, 1234);
        test::greater<test::fail>(i, 1233);
        test::less<test::fail>(i, 1235);
        test::is_true<test::fail>(i);

        scalar<float> f = 56.789f;
        test::equal<test::fail>(f, 56.789f);
        test::not_less<test::fail>(f, 56.788f);
        test::not_greater<test::fail>(f, 56.790f);
        test::is_true<test::fail>(f);

        scalar<bool> b = true;
        test::is_true<test::fail>(b);

        scalar<unsigned long long> u = 1234567890uLL;
        test::equal<test::fail>(u, 1234567890uLL);

        scalar<char> c = '*';
        test::equal<test::fail>(c, '*');

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
