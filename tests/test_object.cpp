// test object

#include <dyn/object.h>
#include <string>
#include "test.h"

namespace dyn
{
    TEST_SUITE(test_object_default)
    {
        object n;
        test::is_null<test::fail>(n);
        test::is_not<test::fail>(n);
        test::is_false<test::fail>(n);
        test::is_true<test::fail>(!n);
    }

    TEST_SUITE(test_object_int)
    {
        object i = 12345;
        test::is_not_null<test::fail>(i);
        test::is_true<test::fail>(i);
        test::is_false<test::fail>(!i);
        test::equal<test::fail>(i.get<int>(), 12345);
    }

    TEST_SUITE(test_object_float)
    {
        object f = 123.45f;
        test::is_not_null<test::fail>(f);
        test::is_true<test::fail>(f);
        test::equal<test::fail>(f.get<float>(), 123.45f);
    }

    TEST_SUITE(test_object_assignment)
    {
        object i = 34567;
        object x = i;
        test::is_not_null<test::fail>(x);
        test::equal<test::fail>(x.get<int>(), 34567);
        test::equal<test::fail>(x.get<int>(), i.get<int>());

        object n;
        x = n;
        test::is_null<test::fail>(x);
        test::is_not_null<test::fail>(i);
        test::equal<test::fail>(i.get<int>(), 34567);
    }

    TEST_SUITE(test_nullptr_assignment)
    {
        object d = 12345.6789;
        object p = d;
        test::is_not_null<test::fail>(p);
        test::is_true<test::fail>(p);
        test::equal<test::fail>(p.get<double>(), 12345.6789);
        test::equal<test::fail>(p.get<double>(), d.get<double>());

        p = nullptr;
        test::is_null<test::fail>(p);
        test::is_not_null<test::fail>(d);
        test::is_false<test::fail>(p);
        test::is_true<test::fail>(!p);
    }
}

// Unicode signature: Владимир Керимов
