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
        TEST_CHECK(s.const_instance()) == "Who is your daddy?!";
        const reference<std::string> c = s;
        TEST_CHECK(c.shared_count()) == 2;
        TEST_CHECK(c->substr(12)) == "daddy?!";
        TEST_CHECK(c.shared_count()) == 2;
        reference<std::string> t = s;
        TEST_CHECK(t.shared_count()) == 3;
        TEST_CHECK(c.shared_count()) == t.shared_count();
        TEST_CHECK(s.shared_count()) == t.shared_count();
        TEST_CHECK_OPERATION(t->at(t->size() - 1u) = '?').no_exception();
        TEST_CHECK(t.const_instance()) == "Who is your daddy??";
        TEST_CHECK(s.const_instance()) == "Who is your daddy?!";
        TEST_CHECK(t.is_unique()).is_true();
        TEST_CHECK(t.shared_count()) != s.shared_count();
        TEST_CHECK(c.shared_count()) == s.shared_count();
        TEST_CHECK(s.shared_count()) == 2;
    }

    struct release_checker
    {
        release_checker() { ++staying_alive; }
        release_checker(const release_checker&) { ++staying_alive; }
        ~release_checker() { --staying_alive; }
        void nonconst_method() { ++nonconst_calls; }
        void const_method() const { ++const_calls; }

        static int staying_alive;
        static int nonconst_calls;
        static int const_calls;
    };

    template<> const char* const reference<release_checker>::class_name = "reference<release_checker>";
    template<> const char* const reference<release_checker>::data::class_name = "reference<release_checker>::data";

	inline std::ostream& operator << (std::ostream& output, const release_checker&)
	{
		return output;
	}

    int release_checker::staying_alive = 0;
    int release_checker::nonconst_calls = 0;
    int release_checker::const_calls = 0;

    TEST_SUITE(test_reference_release)
    {
        TEST_CRITICAL_CHECK(release_checker::staying_alive) == 0;
        TEST_CRITICAL_CHECK(release_checker::nonconst_calls) == 0;
        TEST_CRITICAL_CHECK(release_checker::const_calls) == 0;
        {
            reference<release_checker> checker;
            TEST_CHECK(release_checker::staying_alive) == 1;
            const reference<release_checker> referrer = checker;
            TEST_CHECK(release_checker::staying_alive) == 1;
            reference<release_checker> another = referrer;
            TEST_CHECK(release_checker::staying_alive) == 1;
            another->nonconst_method();
            TEST_CHECK(release_checker::nonconst_calls) == 1;
            TEST_CHECK(release_checker::staying_alive) == 2;
            another->nonconst_method();
            TEST_CHECK(release_checker::nonconst_calls) == 2;
            TEST_CHECK(release_checker::staying_alive) == 2;
            referrer->const_method();
            TEST_CHECK(release_checker::const_calls) == 1;
            TEST_CHECK(release_checker::staying_alive) == 2;
            {
                reference<release_checker> temporary;
                TEST_CHECK(release_checker::staying_alive) == 3;
                TEST_CHECK(release_checker::nonconst_calls) == 2;
                TEST_CHECK(release_checker::const_calls) == 1;
                reference<release_checker> temp_ref = another;
                TEST_CHECK(release_checker::staying_alive) == 3;
                temporary->nonconst_method();
                TEST_CHECK(release_checker::staying_alive) == 3;
                temp_ref->nonconst_method();
                TEST_CHECK(release_checker::staying_alive) == 4;
            }
            TEST_CHECK(release_checker::staying_alive) == 2;
        }
        TEST_CHECK(release_checker::staying_alive) == 0;
    }
}

// Unicode signature: Владимир Керимов
