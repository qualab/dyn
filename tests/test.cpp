// test mechanism implementation

#include <dyn/object.h>
#include <list>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>
#include <utility>
#include "test.h"

namespace dyn
{
    namespace
    {
        std::list<test::suite*> test_suites;
        std::ostream* test_output = &std::cout;
        thread_local std::list<std::unique_ptr<const test::fail>> test_fails;

        template <typename fail_type, typename ...argument_types>
        void register_fail(argument_types... arguments)
        {
            test_fails.push_back(std::make_unique<const fail_type>(arguments...));
        }
    }

    void test::output(std::ostream& output)
    {
        test_output = &output;
    }

    std::ostream& test::output()
    {
        return *test_output;
    }

    void test::output_description(std::ostream& output_stream, const std::string& description)
    {
        output_stream << description;
    }

    void test::add(test::suite* new_suite)
    {
        test_suites.push_back(new_suite);
    }

    void test::run(const std::string& run_name)
    {
        static const std::string DEFAULT_NAME = "testing";
        static const std::string RUN_DELIMITER = " - - -\n";
        const std::string& name = run_name.empty() ? DEFAULT_NAME : run_name;

        struct test_run_results
        {
            bool        test_run_OK;
            size_t      test_suites_run_count;
            size_t      test_check_failure_count;
            size_t      test_suite_failure_count;
            size_t      test_suite_interruption_count;
            std::string test_run_interrupted_at;

            test_run_results()
                : test_run_OK(true),
                  test_suites_run_count(0),
                  test_check_failure_count(0),
                  test_suite_failure_count(0),
                  test_suite_interruption_count(0),
                  test_run_interrupted_at()
            {
            }
        } results;

        output() << "TEST RUN '" << name << "'\n" << RUN_DELIMITER;
        std::find_if(test_suites.begin(), test_suites.end(),
            // return true to terminate test run
            [&](test::suite* current_suite)
            {
                output() << "RUNNING " << current_suite->name() << " - ";
                bool test_run_is_interrupted = false;
                bool test_suite_interruption = true;
                try
                {
                    ++results.test_suites_run_count;
                    current_suite->scope_run();
                    test_suite_interruption = false;
                }
                catch (test::fatal_error&)
                {
                    test_run_is_interrupted = true;
                    results.test_run_interrupted_at = current_suite->name();
                }
                catch (test::error&)
                {
                }
                catch (std::exception& unexpected_exception)
                {
                    register_fail<test::unhandled_exception<test::error>>(unexpected_exception.what());
                }
                catch (...)
                {
                    register_fail<test::nonstandard_unhandled_exception<test::error>>();
                }
                if (test_fails.empty())
                {
                    output() << "OK";
                }
                else
                {
                    results.test_run_OK = false;
                    results.test_check_failure_count += test_fails.size();
                    ++results.test_suite_failure_count;
                    if (test_suite_interruption)
                        ++results.test_suite_interruption_count;

                    output() << test_fails.back()->label();
                    std::for_each(test_fails.begin(), test_fails.end(),
                        [&](const std::unique_ptr<const test::fail>& failure)
                        {
                            output() << "\n !> " << failure->label() << ": " << *failure;
                        }
                    );
                    test_fails.clear();
                }
                output() << std::endl;
                return test_run_is_interrupted;
            }
        );
        output() << RUN_DELIMITER;
        output() << "TEST RUN (test suites: " << results.test_suites_run_count << ") - "
                 << (results.test_run_OK ? "OK" : "FAIL");
        if (!results.test_run_interrupted_at.empty())
        {
            output() << "\n !> INTERRUPTED AT: " << results.test_run_interrupted_at;
            output() << "\n !> Test suite expected to run: " << test_suites.size();
        }
        if (results.test_check_failure_count)
        {
            output() << "\n !> Test check failure count: " << results.test_check_failure_count;
            output() << "\n !> Test suite failure count: " << results.test_suite_failure_count;
            if (results.test_suite_interruption_count)
            {
                output() << "\n !> Test suite interruption count: " << results.test_suite_interruption_count;
            }
        }
        output() << "\n" << RUN_DELIMITER << std::flush;
    }

    test::suite::suite()
    {
        test::add(this);
    }

    void test::suite::scope_run()
    {
        trace::scope scope(name(), file(), line());
        run();
    }

    test::fail::fail(const std::string& message)
        : base(message)
    {
    }

    const char* test::fail::label() const
    {
        return "FAIL";
    }

    void test::fail::handle() const
    {
        register_fail<test::fail>(*this);
    }

    test::error::error(const std::string& message)
        : test::fail(message)
    {
    }

    const char* test::error::label() const
    {
        return "ERROR";
    }

    void test::error::handle() const
    {
        register_fail<test::error>(*this);
        throw *this;
    }

    test::fatal_error::fatal_error(const std::string& message)
        : test::error(message)
    {
    }

    const char* test::fatal_error::label() const
    {
        return "FATAL ERROR";
    }

    void test::fatal_error::handle() const
    {
        register_fail<test::fatal_error>(*this);
        throw *this;
    }
}

// Unicode signature: Владимир Керимов
