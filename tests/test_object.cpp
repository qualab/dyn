// test object

#include <dyn/object.h>
#include <string>
#include "test.h"

namespace dyn
{
    TEST_SUITE(test_object)
    {
        object n;
        test::is_true(n.is_null(), "Null expected after default construcor of object.");
    }
}

// Unicode signature: Владимир Керимов
