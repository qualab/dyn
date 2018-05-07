// test shared reference with copy-on-write mechanism

#include <dyn/integer.h>
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
}

// Unicode signature: Владимир Керимов
