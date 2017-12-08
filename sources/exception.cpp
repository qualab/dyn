// dynamically typified object

#include <dyn/exception.h>
#include <iostream>
#include <sstream>

namespace dyn
{
    exception::exception(const std::string& message)
        : base(message.c_str()), m_message(message), m_stack(trace::stack())
    {
    }

    const char* exception::what() const
    {
        return m_message.c_str();
    }

    const std::string& exception::message() const
    {
        return m_message;
    }

    const trace::stack_type& exception::stack() const
    {
        return m_stack;
    }

    std::ostream& operator << (std::ostream& output_stream, const exception& the_exception)
    {
        output_stream << the_exception.message() << the_exception.stack();
        return output_stream;
    }
}

// Unicode signature: Владимир Керимов
