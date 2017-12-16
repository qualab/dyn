// dynamically typified object

#include <dyn/trace.h>
#include <algorithm>
#include <iostream>
#include <utility>

namespace dyn
{
    thread_local trace::stack_type trace::m_stack;
    const std::string trace::scope::global_name = "global";

    std::ostream& operator << (std::ostream& output_stream, const trace::stack_type& the_stack)
    {
        std::for_each(the_stack.begin(), the_stack.end(),
            [&](const trace::scope& the_scope)
            {
                output_stream << "\n -> " << the_scope;
            }
        );
        return output_stream;
    }

    trace::scope::scope()
        : m_requires_pop(false),
          m_name(global_name),
          m_file(),
          m_line()
    {
    }

    trace::scope::scope(const std::string& name, const std::string& file, int line)
        : m_requires_pop(true),
          m_name(name),
          m_file(file),
          m_line(line)
    {
        trace::m_stack.push_front(scope(*this));
    }

    trace::scope::~scope()
    {
        pop_if_required();
    }

    void trace::scope::pop_if_required()
    {
        if (m_requires_pop)
        {
            trace::m_stack.pop_front();
            m_requires_pop = false;
        }
    }

    trace::scope::scope(const trace::scope& another)
        : m_requires_pop(false),
          m_name(another.m_name),
          m_file(another.m_file),
          m_line(another.m_line)
    {
    }

    trace::scope& trace::scope::operator = (const trace::scope& another)
    {
        pop_if_required();
        m_name = another.m_name;
        m_file = another.m_file;
        m_line = another.m_line;
        return *this;
    }

    trace::scope::scope(trace::scope&& temporary)
        : m_requires_pop(temporary.m_requires_pop),
          m_name(std::move(temporary.m_name)),
          m_file(std::move(temporary.m_file)),
          m_line(temporary.m_line)
    {
        temporary.m_requires_pop = false;
    }

    trace::scope& trace::scope::operator = (trace::scope&& temporary)
    {
        pop_if_required();
        m_requires_pop = temporary.m_requires_pop;
        m_name = std::move(temporary.m_name);
        m_file = std::move(temporary.m_file);
        m_line = temporary.m_line;
        temporary.m_requires_pop = false;
        return *this;
    }

    const std::string& trace::scope::name() const
    {
        return m_name;
    }

    const std::string& trace::scope::file() const
    {
        return m_file;
    }

    int trace::scope::line() const
    {
        return m_line;
    }

    std::ostream& operator << (std::ostream& output_stream, const trace::scope& the_scope)
    {
        output_stream << the_scope.name();
        if (!the_scope.file().empty())
        {
            output_stream << " -- " << the_scope.file();
            if (the_scope.line() >= 0)
            {
                output_stream << '(' << the_scope.line() << ')';
            }
        }
        return output_stream;
    }
}

// Unicode signature: Владимир Керимов
