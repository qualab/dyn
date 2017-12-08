// trace mechanism based on stacked scopes

#pragma once

#include <dyn/public.h>
#include <iosfwd>
#include <string>
#include <deque>

namespace dyn
{
    class trace
    {
    public:
        class scope;

        typedef std::deque<scope> stack_type;

        static inline const stack_type& stack();

    private:
        static thread_local stack_type m_stack;
        friend class scope;
    };

    DYN_PUBLIC std::ostream& operator << (std::ostream& output_stream, const trace::stack_type& the_stack);

    class DYN_PUBLIC trace::scope
    {
    public:
        scope(const std::string& name, const std::string& file, int line);
        virtual ~scope();

        scope(const scope& another);
        scope& operator = (const scope& another);

        scope(scope&& temporary);
        scope& operator = (scope&& temporary);

        const std::string& name() const;
        const std::string& file() const;
        int line() const;

    private:
        bool m_requires_pop;
        std::string m_name;
        std::string m_file;
        int m_line;

        void pop_if_required();
    };

    DYN_PUBLIC std::ostream& operator << (std::ostream& output_stream, const trace::scope& the_scope);

    const trace::stack_type& trace::stack()
    {
        return m_stack;
    }
}

// Unicode signature: Владимир Керимов
