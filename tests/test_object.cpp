// test object

#include <dyn/object.h>
#include <string>
#include "test.h"

namespace dyn
{
    TEST_SUITE(test_object_default)
    {
        object n;
        TEST_CHECK(n).is_null();
        TEST_CHECK(n).is_not();
        TEST_CHECK(n).is_false();
        TEST_CHECK(!n).is_true();
    }

    TEST_SUITE(test_object_int)
    {
        object i = 12345;
        TEST_CHECK(i).is_not_null();
        TEST_CHECK(i).is_true();
        TEST_CHECK(!i).is_false();
        TEST_CHECK(i.get<int>()) == 12345;
    }

    TEST_SUITE(test_object_float)
    {
        object f = 123.45f;
        TEST_CHECK(f).is_not_null();
        TEST_CHECK(f).is_true();
        TEST_CHECK(f.get<float>()) == 123.45f;
    }

    TEST_SUITE(test_object_assignment)
    {
        object i = 34567;
        object x = i;
        TEST_CHECK(x).is_not_null();
        TEST_CHECK(x.get<int>()) == 34567;
        TEST_CHECK(x.get<int>()) == i.get<int>();

        object n;
        x = n;
        TEST_CHECK(x).is_null();
        TEST_CHECK(i).is_not_null();
        TEST_CHECK(i.get<int>()) == 34567;
    }

    TEST_SUITE(test_nullptr_assignment)
    {
        object d = 12345.6789;
        object p = d;
        TEST_CHECK(p).is_not_null();
        TEST_CHECK(p).is_true();
        TEST_CHECK(p.get<double>()) == 12345.6789;
        TEST_CHECK(p.get<double>()) == d.get<double>();

        p = nullptr;
        TEST_CHECK(p).is_null();
        TEST_CHECK(d).is_not_null();
        TEST_CHECK(p).is_false();
        TEST_CHECK(p).is_not();
    }
}

// Unicode signature: Владимир Керимов
