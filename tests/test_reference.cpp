// test shared reference with copy-on-write mechanism

#include <dyn/reference.h>
#include <string>
#include "test.h"

namespace dyn
{
    TEST_SUITE(test_reference_count)
    {
        reference<std::string> s;
        TEST_CHECK(s.is_unique()).is_true();
        reference<std::string> t = s;
        TEST_CHECK(s.is_unique()).is_false();
        TEST_CHECK(t.is_unique()).is_false();
        TEST_CHECK(s.shared_count()) == 2;
        TEST_CHECK(s.shared_count()) == t.shared_count();
    }

    TEST_SUITE(test_reference_assignment)
    {
        reference<std::string> s = "Who is your daddy?!";
        TEST_CHECK(*s) == "Who is your daddy?!";
        const reference<std::string> c = s;
        TEST_CHECK(c.shared_count()) == 2;
        TEST_CHECK(c->substr(12)) == "daddy?!";
        TEST_CHECK(c.shared_count()) == 2;
    }
}

// Unicode signature: Владимир Керимов
