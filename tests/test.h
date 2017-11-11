// test scalar

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
        class fail;

        template <class exception_type>
        class exception_expected_type;

        static void output(std::ostream& output);
        static std::ostream& output();

        static void add(suite* new_suite);
        static void run();

        template <typename ...argument_types>
        static void assert(const std::function<bool(argument_types... arguments)>& predicate,
            const std::string& description, argument_types... arguments);

        static void output_description(std::ostream& output_stream, const std::string& description);

        template <typename next_argument_type, typename ...argument_types>
        static void output_description(std::ostream& output_stream, const std::string& description,
            next_argument_type next_argument, argument_types... argument);

        template <typename argument_type>
        static void is_true(const argument_type& argument, const std::string& description = "");

        template <typename argument_type>
        static void is_false(const argument_type& argument, const std::string& description = "");

        static void is_null(object argument, const std::string& description = "");
        static void is_not_null(object argument, const std::string& description = "");

        template <typename left_argument_type, typename right_argument_type>
        static void equal(left_argument_type left_argument, right_argument_type right_argument, const std::string& description = "");

        template <typename left_argument_type, typename right_argument_type>
        static void not_equal(left_argument_type left_argument, right_argument_type right_argument, const std::string& description = "");

        template <typename left_argument_type, typename right_argument_type>
        static void less(left_argument_type left_argument, right_argument_type right_argument, const std::string& description = "");

        template <typename left_argument_type, typename right_argument_type>
        static void greater(left_argument_type left_argument, right_argument_type right_argument, const std::string& description = "");

        template <typename left_argument_type, typename right_argument_type>
        static void not_greater(left_argument_type left_argument, right_argument_type right_argument, const std::string& description = "");

        template <typename left_argument_type, typename right_argument_type>
        static void not_less(left_argument_type left_argument, right_argument_type right_argument, const std::string& description = "");

        template <typename result_type, typename ...argument_types>
        static result_type no_exeption(const std::function<result_type(argument_types... arguments)>& action, argument_types... arguments);

        template <typename exception_type, typename result_type, typename ...argument_types>
        static void expect_exception(const std::function<result_type(argument_types... arguments)>& action, argument_types... arguments);
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

    class test::fail : public std::exception
    {
    public:
        fail(const std::string& message);
        fail(std::string&& message);

        virtual const char* what() const override;
        virtual const std::string& message() const;

    private:
        std::string m_message;
    };

    template <typename exception_type>
    class exception_expected_type : public fail
    {
    public:
        exception_expected_type();
    };

    template <typename ...argument_types>
    void test::assert(const std::function<bool(argument_types... arguments)>& predicate, const std::string& description, argument_types... arguments)
    {
        bool complete = false;
        try
        {
            complete = predicate(arguments...);
        }
        catch (std::exception& unhandled_exception)
        {
            std::stringstream message_stream;
            message_stream << "Unhandled exception: \"" << unhandled_exception.what()
                << "\" due execution of ";
            output_description(message_stream, description, arguments...);
            throw fail(message_stream.str());
        }
        if (!complete)
        {
            std::stringstream message_stream;
            message_stream << "Failed ";
            output_description(message_stream, description, arguments...);
            throw fail(message_stream.str());
        }
    }

    template <typename next_argument_type, typename ...argument_types>
    static void test::output_description(std::ostream& output_stream, const std::string& description,
        next_argument_type next_argument, argument_types ...arguments)
    {
        static const std::string PLACEMENT = "{}";
        size_t end = description.find(PLACEMENT);
        if (end != std::string::npos)
        {
            std::string before = description.substr(0, end);
            output_stream << before << next_argument;
            std::string after = description.substr(end + PLACEMENT.size());
            output_description(output_stream, after, arguments...);
        }
        else
            output_stream << description;
    }

    template <typename argument_type>
    void test::is_true(const argument_type& argument, const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check is {} true";
        test::assert(
            std::function<bool(argument_type)>(
            [&](argument_type argument) -> bool
            {
                return argument ? true : false;
            }),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            argument
        );
    }

    template <typename argument_type>
    void test::is_false(const argument_type& argument, const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check is {} false";
        test::assert(
            std::function<bool(argument_type)>(
            [&](argument_type argument) -> bool
            {
                return argument ? false : true;
            }),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            argument
        );
    }

    template <typename left_argument_type, typename right_argument_type>
    void test::equal(left_argument_type left_argument, right_argument_type right_argument, const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check is {} == {}";
        test::assert(
            std::function<bool(left_argument_type, right_argument_type)>(
            [&](left_argument_type left_argument, right_argument_type right_argument) -> bool
            {
                return left_argument == right_argument;
            }),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename left_argument_type, typename right_argument_type>
    void test::not_equal(left_argument_type left_argument, right_argument_type right_argument, const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check is {} != {}";
        test::assert(
            std::function<bool(left_argument_type, right_argument_type)>(
            [&](left_argument_type left_argument, right_argument_type right_argument) -> bool
            {
                return left_argument != right_argument;
            }),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename left_argument_type, typename right_argument_type>
    void test::less(left_argument_type left_argument, right_argument_type right_argument, const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check is {} < {}";
        test::assert(
            std::function<bool(left_argument_type, right_argument_type)>(
            [&](left_argument_type left_argument, right_argument_type right_argument) -> bool
            {
                return left_argument < right_argument;
            }),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename left_argument_type, typename right_argument_type>
    void test::greater(left_argument_type left_argument, right_argument_type right_argument, const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check is {} > {}";
        test::assert(
            std::function<bool(left_argument_type, right_argument_type)>(
            [&](left_argument_type left_argument, right_argument_type right_argument) -> bool
            {
                return left_argument > right_argument;
            }),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename left_argument_type, typename right_argument_type>
    void test::not_greater(left_argument_type left_argument, right_argument_type right_argument, const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check is {} <= {}";
        test::assert(
            std::function<bool(left_argument_type, right_argument_type)>(
            [&](left_argument_type left_argument, right_argument_type right_argument) -> bool
            {
                return left_argument <= right_argument;
            }),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename left_argument_type, typename right_argument_type>
    void test::not_less(left_argument_type left_argument, right_argument_type right_argument, const std::string& description)
    {
        static const std::string DEFAULT_DESCRIPTION = "check is {} >= {}";
        test::assert(
            std::function<bool(left_argument_type, right_argument_type)>(
            [&](left_argument_type left_argument, right_argument_type right_argument) -> bool
            {
                return left_argument >= right_argument;
            }),
            description.empty() ? DEFAULT_DESCRIPTION : description,
            left_argument, right_argument
        );
    }

    template <typename result_type, typename ...argument_types>
    result_type test::no_exeption(const std::function<result_type(argument_types... arguments)>& action, argument_types... arguments)
    {
        static const std::string FAIL_MESSAGE = "No exception expected, but exception caught. ";
        try
        {
            return action(arguments...);
        }
        catch (std::exception& unexpected_exception)
        {
            throw fail(FAIL_MESSAGE + unexpected_exception.what());
        }
        catch (...)
        {
            throw fail(FAIL_MESSAGE);
        }
    }

    template <typename exception_type, typename result_type, typename ...argument_types>
    void test::expect_exception(const std::function<result_type(argument_types... arguments)>& action, argument_types... arguments)
    {
        try
        {
            action(arguments...);
        }
        catch (exception_type&)
        {
            return;
        }
        catch (...)
        {
        }
        throw exception_expected_type<exception_type>();
    }

    template <typename exception_type>
    exception_expected_type<exception_type>::exception_expected_type()
        : fail("Exception expected of the type specified, but not been caught.")
    {
    }
}

// Unicode signature: Владимир Керимов
