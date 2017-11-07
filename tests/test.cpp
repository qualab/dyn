// test scalar

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

    void test::run()
    {
        std::for_each(test_suites.begin(), test_suites.end(),
            [&](test::suite* current_suite)
            {
                bool succeed = false;
                try
                {
                    output() << "RUN \"" << current_suite->name() << "\" - ";
                    current_suite->run();
                    succeed = true;
                }
                catch (test::fail& failed)
                {
                    output() << "FAIL: " << failed.what();
                }
                catch (std::exception& error)
                {
                    output() << "ERROR: " << error.what();
                }
                if (succeed)
                    output() << "OK";
                output() << std::endl;
            }
        );
    }

    test::suite::suite()
    {
        test::add(this);
    }

    test::fail::fail(const std::string& message)
        : m_message(message)
    {
    }

    test::fail::fail(std::string&& message)
        : m_message(std::move(message))
    {
    }

    const char* test::fail::what() const
    {
        return m_message.c_str();
    }

    const std::string& test::fail::message() const
    {
        return m_message;
    }
}

// Unicode signature: Владимир Керимов
