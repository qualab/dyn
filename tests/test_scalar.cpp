﻿// test scalar

#include <dyn/scalar.h>
#include <string>
#include "test.h"

namespace dyn
{
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
    }
}

// Unicode signature: Владимир Керимов
