// Base exception type with stack trace

#pragma once

#include <dyn/trace.h>
#include <dyn/type.h>
#include <exception>
#include <sstream>
#include <string>

namespace dyn
{
    // every exception class in dyn:: must be derived from this class

    class DYN_PUBLIC exception : public std::exception
    {
    public:
        typedef std::exception base;
            
        explicit exception(const std::string& message);

        template <typename derived_type>
        bool is() const;

        template <typename derived_type>
        bool is_not() const;

        template <typename derived_type>
        derived_type& as();

        template <typename derived_type>
        const derived_type& as() const;

        virtual const char* what() const override;
        virtual const std::string& message() const;
        virtual const trace::stack_type& stack() const;
        virtual const trace::scope& scope() const;

        static const char* const class_name;
        virtual const char* const get_class_name() const;

    private:
        std::string m_message;
        trace::stack_type m_stack;
    };

    DYN_PUBLIC std::ostream& operator << (std::ostream& output_stream, const exception& the_exception);

    // base exception class "is_class" template specification

    template <>
    struct is_class<exception>
    {
        template <typename base_type>
        static bool of()
        {
            return exception::class_name == base_type::class_name;
        }
    };

    // type cast exception for all invalid type casts
    // which are not compatible class hierarchy tree

    class DYN_PUBLIC typecast_exception : public dyn::exception
    {
    public:
        typedef dyn::exception base;

        explicit typecast_exception(const std::string& message);

        static const char* const class_name;
        virtual const char* const get_class_name() const override;
    };

    // safe type cast with exception in case when it not compatible with inheritance hierarchy

    template <typename derived_type>
    struct typecast_to
    {
        template <typename base_type>
        static const derived_type& from(const base_type& instance)
        {
            if (!is_instance(instance).of<base_type>())
            {
                std::stringstream exception_output;
                exception_output << "Unable to cast instance of type: '" << instance.get_class_name()
                    << "' to type: '" << derived_type::class_name
                    << "' instance must implement this type.";
                throw typecast_exception(exception_output.str());
            }
            return static_cast<const derived_type&>(instance);
        }

        template <typename base_type>
        static derived_type& from(base_type& instance)
        {
            return const_cast<derived_type&>(
                from(static_cast<const base_type&>(instance))
            );
        }
    };

    template <typename derived_type>
    bool exception::is() const
    {
        return is_instance(*this)::of<derived_type>();
    }

    template <typename derived_type>
    bool exception::is_not() const
    {
        return !is<derived_type>();
    }

    template <typename derived_type>
    const derived_type& exception::as() const
    {
        return typecast_to<derived_type>::from(*this);
    }

    template <typename derived_type>
    derived_type& exception::as()
    {
        return typecast_to<derived_type>::from(*this);
    }
}

// Unicode signature: Владимир Керимов
