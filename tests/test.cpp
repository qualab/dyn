﻿// test scalar

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

    void test::run()
    {
        std::find_if(test_suites.begin(), test_suites.end(),
            // return true to terminate test run
            [&](test::suite* current_suite)
            {
                bool stop_run = false;
                output() << "RUNNING " << current_suite->name() << " - ";
                try
                {
                    current_suite->run();
                }
                catch (test::fatal_error&)
                {
                    stop_run = true;
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
                    output() << test_fails.back()->label();
                    std::for_each(test_fails.begin(), test_fails.end(),
                        [&](const std::unique_ptr<const test::fail>& failure)
                        {
                            output() << "\n !> " << failure->label() << ": " << failure->message();
                        }
                    );
                    test_fails.clear();
                }
                output() << std::endl;
                return stop_run;
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

    test::fail::~fail()
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
