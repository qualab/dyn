// base exception type with stack trace

#pragma once

#include <dyn/trace.h>
#include <exception>
#include <string>

namespace dyn
{
    class DYN_PUBLIC exception : public std::exception
    {
    public:
        typedef std::exception base;

        explicit exception(const std::string& message);

        virtual const char* what() const override;
        virtual const std::string& message() const;
        virtual const trace::stack_type& stack() const;

    private:
        std::string m_message;
        trace::stack_type m_stack;
    };

    DYN_PUBLIC std::ostream& operator << (std::ostream& output_stream, const exception& the_exception);
}

// Unicode signature: Владимир Керимов
