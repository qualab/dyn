// test object

#include <dyn/object.h>
#include <string>
#include "test.h"

namespace dyn
{
    TEST_SUITE(test_object)
    {
        object n;
        test::is_null<test::fail>(n);

        object i = 12345;
        test::is_not_null<test::fail>(i);

        object f = 123.45f;
        test::is_not_null<test::fail>(f);

        object x = i;
        test::is_not_null<test::fail>(x);

        x = n;
        test::is_null<test::fail>(x);
        test::is_not_null<test::fail>(i);
    }
}

// Unicode signature: Владимир Керимов
