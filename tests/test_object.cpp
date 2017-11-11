// test object

#include <dyn/object.h>
#include <string>
#include "test.h"

namespace dyn
{
    TEST_SUITE(test_object)
    {
        object n;
        test::is_null(n);

        object i = 12345;
        test::is_not_null(i);

        object f = 123.45f;
        test::is_not_null(f);

        object x = i;
        test::is_not_null(x);
        x = n;
        test::is_null(x);
        test::is_null(n);
        test::is_not_null(i);
    }
}

// Unicode signature: Владимир Керимов
