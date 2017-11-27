// test mechanism base constructions

#include <dyn/public.h>
#include <functional>
#include <exception>
#include <iostream>
#include <utility>
#include <sstream>
#include <string>

namespace dyn
{
    class test
    {
    public:
        class suite;

        template <typename fail_type, typename argument_type>
        class check;

        class fail;         // fails single check
        class error;        // fails suite run
        class fatal_error;  // fails whole test run

        template <typename fail_type, typename argument_type>
        static check<fail_type, argument_type> make_check(const argument_type& argument,
                                                          const char* file,
                                                          int line);

        template <typename fail_type>
        class unhandled_exception;

        template <typename fail_type>
        class nonstandard_unhandled_exception;

        template <typename exception_type, typename fail_type>
        class exception_expected;

        static void output(std::ostream& output);
        static std::ostream& output();

        static void add(suite* new_suite);
        static void run(const std::string& name = "");

        template <typename fail_type, typename... argument_types>
        static void assert(const std::function<bool(const argument_types&... arguments)>& predicate,
                           const std::string& description,
                           const argument_types&... arguments);

        static void store_current_position(const char* file, int line);
        static void clear_current_position();
        static void output_current_position(std::ostream& output_stream);

        static void output_description(std::ostream& output_stream,
                                       const std::string& description);

        template <typename next_argument_type, typename ...argument_types>
        static void output_description(std::ostream& output_stream,
                                       const std::string& description,
                                       const next_argument_type& next_argument,
                                       const argument_types&... arguments);

        template <typename fail_type, typename ...argument_types>
        static void handle_fail(const argument_types&... arguments);

        template <typename fail_type, typename argument_type>
        static void is_true(const argument_type& argument,
                            const std::string& description = "");

        template <typename fail_type, typename argument_type>
        static void is_false(const argument_type& argument,
                             const std::string& description = "");

        template <typename fail_type, typename argument_type>
        static void is_not(const argument_type& argument,
                           const std::string& description = "");

        template <typename fail_type, typename argument_type>
        static void is_null(const argument_type& argument,
                            const std::string& description = "");

        template <typename fail_type, typename argument_type>
        static void is_not_null(const argument_type& argument,
                                const std::string& description = "");

        template <typename fail_type, typename left_argument_type, typename right_argument_type>
        static void equal(const left_argument_type& left_argument,
                          const right_argument_type& right_argument,
                          const std::string& description = "");

        template <typename fail_type, typename left_argument_type, typename right_argument_type>
        static void not_equal(const left_argument_type& left_argument,
                              const right_argument_type& right_argument,
                              const std::string& description = "");

        template <typename fail_type, typename left_argument_type, typename right_argument_type>
        static void less(const left_argument_type& left_argument,
                         const right_argument_type& right_argument,
                         const std::string& description = "");

        template <typename fail_type, typename left_argument_type, typename right_argument_type>
        static void greater(const left_argument_type& left_argument,
                            const right_argument_type& right_argument,
                            const std::string& description = "");

        template <typename fail_type, typename left_argument_type, typename right_argument_type>
        static void not_greater(const left_argument_type& left_argument,
                                const right_argument_type& right_argument,
                                const std::string& description = "");

        template <typename fail_type, typename left_argument_type, typename right_argument_type>
        static void not_less(const left_argument_type& left_argument,
                             const right_argument_type& right_argument,
                             const std::string& description = "");

        template <typename fail_type, typename result_type, typename... argument_types>
        static result_type no_exception(const std::function<result_type(const argument_types&... arguments)>& action,
                                        const argument_types&... arguments);

        template <typename exception_type, typename fail_type, typename result_type, typename... argument_types>
        static void expect_exception(const std::function<result_type(const argument_types&... arguments)>& action,
                                     const argument_types&... arguments);
    };

    class test::suite
    {
    public:
        suite();
        virtual const char* name() const = 0;
        virtual void run() = 0;
    };

#define TEST_SUITE(suite_name) \
class test_suite_##suite_name : public test::suite \
{ \
public: \
    virtual const char* name() const override { return #suite_name; } \
    virtual void run() override; \
} g_test_suite_##suite_name; \
 \
void test_suite_##suite_name::run()

    template <typename fail_type, typename argument_type>
    class test::check
    {
    public:
        check(const argument_type& argument, const char* file, int line);
        check(check&& temporary);
        ~check();

        template <typename another_type>
        void operator == (const another_type& another) const;

        template <typename another_type>
        void operator != (const another_type& another) const;

        template <typename another_type>
        void operator < (const another_type& another) const;

        template <typename another_type>
        void operator > (const another_type& another) const;

        template <typename another_type>
        void operator <= (const another_type& another) const;

        template <typename another_type>
        void operator >= (const another_type& another) const;

        void is_true() const;
        void is_false() const;
        void is_not() const;
        void is_null() const;
        void is_not_null() const;

        template <typename... parameter_types>
        void no_exception(const parameter_types&... parameters) const;

        template <typename exception_type, typename... parameter_types>
        void expect_exception(const parameter_types&... parameters) const;

    private:
        const argument_type& m_argument;
        bool m_clear_position;

        check(const check& restricted);
    };

    template <typename fail_type, typename argument_type>
    test::check<fail_type, argument_type> test::make_check(const argument_type& argument,
                                                           const char* file,
                                                           int line)
    {
        return test::check<fail_type, argument_type>(argument, file, line);
    }

#define TEST_CHECK(argument) test::make_check<test::fail>(argument, __FILE__, __LINE__)
#define TEST_CRITICAL_CHECK(argument) test::make_check<test::error>(argument, __FILE__, __LINE__)
#define TEST_RUN_CRITICAL_CHECK(argument) test::make_check<test::fatal_error>(argument, __FILE__, __LINE__)

    class test::fail : public std::exception
    {
    public:
        fail(const std::string& message);
        virtual ~fail();

        virtual const char* what() const override;
        virtual const std::string& message() const;

        virtual const char* label() const;
        virtual void handle() const;

    private:
        std::string m_message;
    };

    class test::error : public test::fail
    {
    public:
        error(const std::string& message);
        virtual const char* label() const override;
        virtual void handle() const override;
    };

    class test::fatal_error : public test::error
    {
    public:
        fatal_error(const std::string& message);
        virtual const char* label() const override;
        virtual void handle() const override;
    };

    template <typename fail_type>
    class test::unhandled_exception : public fail_type
    {
    public:
        unhandled_exception(const std::string& message);
    };

    template <typename fail_type>
    class test::nonstandard_unhandled_exception : public test::unhandled_exception<fail_type>
    {
    public:
        nonstandard_unhandled_exception();
    };

    template <typename exception_type, typename fail_type>
    class test::exception_expected : public fail_type
    {
    public:
        exception_expected();
    };

    template <typename fail_type, typename... argument_types>
    void test::assert(const std::function<bool(const argument_types&... arguments)>& predicate,
                      const std::string& description,
                      const argument_types&... arguments)
    {
        bool complete = false;
        try
        {
            complete = predicate(arguments...);
        }
        catch (std::exception& unexpected_exception)
        {
            test::handle_fail<test::unhandled_exception<test::error>>(unexpected_exception.what());
        }
        catch (...)
        {
            test::handle_fail<test::nonstandard_unhandled_exception<test::error>>();
        }
        if (!complete)
        {
            std::stringstream message_stream;
            test::output_current_position(message_stream);
            test::output_description(message_stream, description, arguments...);
            test::handle_fail<fail_type>(message_stream.str());
        }
    }

    template <typename next_argument_type, typename... argument_types>
    void test::output_description(std::ostream& output_stream,
                                  const std::string& description,
                                  const next_argument_type& next_argument,
                                  const argument_types&... arguments)
    {
        static const std::string PLACEMENT = "{}";
        size_t end = description.find(PLACEMENT);
        if (end != std::string::npos)
        {
            std::string before = description.substr(0, end);
            output_stream << before << next_argument;
            std::string after = description.substr(end + PLACEMENT.size());
            test::output_description(output_stream, after, arguments...);
        }
        else
        {
            output_stream << description;
        }
    }

    template <typename fail_type, typename ...argument_types>
    void test::handle_fail(const argument_types&... arguments)
    {
        fail_type failure(arguments...);
        failure.handle();
    }

    template <typename fail_type, typename argument_type>
    void test::is_true(const argument_type& argument,
                       const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check {} is true";
        test::assert<fail_type>(
            std::function<bool(const argument_type&)>(
                [](const argument_type& argument) -> bool
                {
                    return argument ? true : false;
                }
            ),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            argument
        );
    }

    template <typename fail_type, typename argument_type>
    void test::is_false(const argument_type& argument,
                        const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check {} is false";
        test::assert<fail_type>(
            std::function<bool(const argument_type&)>(
                [](const argument_type& argument) -> bool
                {
                    return argument ? false : true;
                }
            ),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            argument
        );
    }

    template <typename fail_type, typename argument_type>
    void test::is_not(const argument_type& argument,
                      const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check is not {}";
        test::assert<fail_type>(
            std::function<bool(const argument_type&)>(
                [](const argument_type& argument) -> bool
                {
                    return !argument;
                }
            ),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            argument
        );
    }

    template <typename fail_type, typename argument_type>
    void test::is_null(const argument_type& argument,
                       const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check {} is null";
        test::assert<fail_type>(
            std::function<bool(const argument_type&)>(
                [&](const argument_type& argument) -> bool
                {
                    return argument.is_null();
                }
            ),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            argument
        );
    }

    template <typename fail_type, typename argument_type>
    void test::is_not_null(const argument_type& argument,
                           const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check {} is not null";
        test::assert<fail_type>(
            std::function<bool(const argument_type&)>(
                [](const argument_type& argument) -> bool
                {
                    return argument.is_not_null();
                }
            ),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            argument
        );
    }

    template <typename fail_type, typename left_argument_type, typename right_argument_type>
    void test::equal(const left_argument_type& left_argument,
                     const right_argument_type& right_argument,
                     const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check {} == {}";
        test::assert<fail_type>(
            std::function<bool(const left_argument_type&, const right_argument_type&)>(
                [](const left_argument_type& left_argument, const right_argument_type& right_argument) -> bool
                {
                    return left_argument == right_argument;
                }
            ),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename fail_type, typename left_argument_type, typename right_argument_type>
    void test::not_equal(const left_argument_type& left_argument,
                         const right_argument_type& right_argument,
                         const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check {} != {}";
        test::assert<fail_type>(
            std::function<bool(const left_argument_type&, const right_argument_type&)>(
                [](const left_argument_type& left_argument, const right_argument_type& right_argument) -> bool
                {
                    return left_argument != right_argument;
                }
            ),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename fail_type, typename left_argument_type, typename right_argument_type>
    void test::less(const left_argument_type& left_argument,
                    const right_argument_type& right_argument,
                    const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check {} < {}";
        test::assert<fail_type>(
            std::function<bool(const left_argument_type&, const right_argument_type&)>(
                [](const left_argument_type& left_argument, const right_argument_type& right_argument) -> bool
                {
                    return left_argument < right_argument;
                }
            ),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename fail_type, typename left_argument_type, typename right_argument_type>
    void test::greater(const left_argument_type& left_argument,
                       const right_argument_type& right_argument,
                       const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check {} > {}";
        test::assert<fail_type>(
            std::function<bool(const left_argument_type&, const right_argument_type&)>(
                [](const left_argument_type& left_argument, const right_argument_type& right_argument) -> bool
                {
                    return left_argument > right_argument;
                }
            ),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename fail_type, typename left_argument_type, typename right_argument_type>
    void test::not_greater(const left_argument_type& left_argument,
                           const right_argument_type& right_argument,
                           const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check {} <= {}";
        test::assert<fail_type>(
            std::function<bool(const left_argument_type&, const right_argument_type&)>(
                [](const left_argument_type& left_argument, const right_argument_type& right_argument) -> bool
                {
                    return left_argument <= right_argument;
                }
            ),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename fail_type, typename left_argument_type, typename right_argument_type>
    void test::not_less(const left_argument_type& left_argument,
                        const right_argument_type& right_argument,
                        const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check {} >= {}";
        test::assert<fail_type>(
            std::function<bool(const left_argument_type&, const right_argument_type&)>(
                [](const left_argument_type& left_argument, const right_argument_type& right_argument) -> bool
                {
                    return left_argument >= right_argument;
                }
            ),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename fail_type, typename result_type, typename ...argument_types>
    result_type test::no_exception(const std::function<result_type(const argument_types&... arguments)>& action,
                                   const argument_types&... arguments)
    {
        try
        {
            return action(arguments...);
        }
        catch (std::exception& unexpected_exception)
        {
            test::handle_fail<test::unhandled_exception<fail_type>>(unexpected_exception.what());
        }
        catch (...)
        {
            test::handle_fail<test::nonstandard_unhandled_exception<fail_type>>();
        }
    }

    template <typename exception_type, typename fail_type, typename result_type, typename ...argument_types>
    void test::expect_exception(const std::function<result_type(const argument_types&... arguments)>& action,
                                const argument_types&... arguments)
    {
        try
        {
            action(arguments...);
        }
        catch (exception_type&)
        {
            return;
        }
        catch (std::exception& unexpected_exception)
        {
            test::handle_fail<test::unhandled_exception<test::error>>(unexpected_exception.what());
        }
        catch (...)
        {
            test::handle_fail<test::nonstandard_unhandled_exception<test::error>>();
        }
        throw exception_expected<exception_type, fail_type>();
    }

    template <typename fail_type, typename argument_type>
    test::check<fail_type, argument_type>::check(const argument_type& argument, const char* file, int line)
        : m_argument(argument), m_clear_position(true)
    {
        test::store_current_position(file, line);
    }

    template <typename fail_type, typename argument_type>
    test::check<fail_type, argument_type>::check(check<fail_type, argument_type>&& temporary)
        : m_argument(temporary.m_argument), m_clear_position(temporary.m_clear_position)
    {
        temporary.m_clear_position = false;
    }

    template <typename fail_type, typename argument_type>
    test::check<fail_type, argument_type>::~check()
    {
        if (m_clear_position)
            test::clear_current_position();
    }

    template <typename fail_type, typename argument_type>
    template <typename another_type>
    void test::check<fail_type, argument_type>::operator == (const another_type& another) const
    {
        test::equal<fail_type>(m_argument, another);
    }

    template <typename fail_type, typename argument_type>
    template <typename another_type>
    void test::check<fail_type, argument_type>::operator != (const another_type& another) const
    {
        test::not_equal<fail_type>(m_argument, another);
    }

    template <typename fail_type, typename argument_type>
    template <typename another_type>
    void test::check<fail_type, argument_type>::operator < (const another_type& another) const
    {
        test::less<fail_type>(m_argument, another);
    }

    template <typename fail_type, typename argument_type>
    template <typename another_type>
    void test::check<fail_type, argument_type>::operator > (const another_type& another) const
    {
        test::greater<fail_type>(m_argument, another);
    }

    template <typename fail_type, typename argument_type>
    template <typename another_type>
    void test::check<fail_type, argument_type>::operator <= (const another_type& another) const
    {
        test::not_greater<fail_type>(m_argument, another);
    }

    template <typename fail_type, typename argument_type>
    template <typename another_type>
    void test::check<fail_type, argument_type>::operator >= (const another_type& another) const
    {
        test::not_less<fail_type>(m_argument, another);
    }

    template <typename fail_type, typename argument_type>
    void test::check<fail_type, argument_type>::is_true() const
    {
        test::is_true<fail_type>(m_argument);
    }

    template <typename fail_type, typename argument_type>
    void test::check<fail_type, argument_type>::is_false() const
    {
        test::is_false<fail_type>(m_argument);
    }

    template <typename fail_type, typename argument_type>
    void test::check<fail_type, argument_type>::is_not() const
    {
        test::is_not<fail_type>(m_argument);
    }

    template <typename fail_type, typename argument_type>
    void test::check<fail_type, argument_type>::is_null() const
    {
        test::is_null<fail_type>(m_argument);
    }

    template <typename fail_type, typename argument_type>
    void test::check<fail_type, argument_type>::is_not_null() const
    {
        test::is_not_null<fail_type>(m_argument);
    }

    template <typename fail_type, typename argument_type>
    template <typename... parameter_types>
    void test::check<fail_type, argument_type>::no_exception(const parameter_types&... parameters) const
    {
        test::no_exception<fail_type>(
            std::function<void(const parameter_types&...)>(m_argument), parameters...);
    }

    template <typename fail_type, typename argument_type>
    template <typename exception_type, typename... parameter_types>
    void test::check<fail_type, argument_type>::expect_exception(const parameter_types&... parameters) const
    {
        test::expect_exception<exception_type, fail_type>(
            std::function<void(const parameter_types&...)>(m_argument), parameters...);
    }

    template <typename exception_type, typename fail_type>
    test::exception_expected<exception_type, fail_type>::exception_expected()
        : fail_type("expected exception of the type specified")
    {
    }

    template <typename fail_type>
    test::unhandled_exception<fail_type>::unhandled_exception(const std::string &message)
        : fail_type("UNHANDLED EXCEPTION: " + message)
    {
    }

    template <typename fail_type>
    test::nonstandard_unhandled_exception<fail_type>::nonstandard_unhandled_exception()
        : unhandled_exception("non-standard exception class")
    {
    }
}

// Unicode signature: Владимир Керимов
