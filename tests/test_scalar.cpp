// test scalar

#include <dyn/scalar.h>
#include <string>
#include "test.h"

namespace dyn
{
    TEST_SUITE(test_scalar)
    {
        scalar<int> i = 1234;
        test::equal(i, 1234);
        test::greater(i, 1233);
        test::less(i, 1235);
        test::is_true(i);

        scalar<float> f = 56.789f;
        test::equal(f, 56.789f);
        test::not_less(f, 56.788f);
        test::not_greater(f, 56.790f);
        test::is_true(f);

        scalar<bool> b = true;
        test::is_true(b);

        scalar<unsigned long long> u = 1234567890uLL;
        test::equal(u, 1234567890uLL);

        scalar<char> c = '*';
        test::equal(c, '*');
    }
}

// Unicode signature: Владимир Керимов
