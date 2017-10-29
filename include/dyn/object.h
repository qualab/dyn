// dynamically typified object

#pragma once

#include <dyn/public.h>
#include <exception>

#ifndef DYN_OBJECT_MAX_DATA_SIZE
#define DYN_OBJECT_MAX_DATA_SIZE 40
#endif

namespace dyn
{
    class DYN_PUBLIC object
    {
    public:
        object();
        virtual ~object();

        object(const object& another);
        object(object&& temporary);

        object& operator = (const object& another);
        object& operator = (object&& temporary);

        bool is_null() const;

        template <typename value_type>
        object(value_type value);

        template <typename value_type>
        object& operator = (value_type value);

        class data;

        static const size_t max_data_size = DYN_OBJECT_MAX_DATA_SIZE;

        template <class derived_data_type>
        class data_size_exception;

    protected:
        template <class derived_data_type, typename... arg_list>
        void initialize(derived_data_type*& derived_data, arg_list... arg);

        const data* get_data() const;
        virtual void reset();

    private:
        char m_buffer[max_data_size];
        data* m_data;
    };

    class DYN_PUBLIC object::data
    {
    public:
        data() { }
        virtual ~data() { }

        virtual data* move_to(void*) = 0;
        virtual data* copy_to(void*) = 0;

        virtual const char* name() const;
    };

    template <typename derived_data>
    class object::data_size_exception : public std::exception
    {
    public:
        const char* what() const override;
    };

    template <typename value_type>
    object::object(value_type value)
    {
        static_assert(false, "Cannot create object using value of this type to object. Implement template specification to accept such creation.");
    }

    template <typename value_type>
    object& object::operator = (value_type value)
    {
        static_assert(false, "Cannot assign value of this type to object. Implement template specification to accept such assignment.");
    }

    template <typename derived_data_type, typename... arg_list>
    void object::initialize(derived_data_type*& derived_data, arg_list... arg)
    {
        reset();
        if (sizeof(derived_data_type) > max_data_size)
            throw data_size_exception<derived_data_type>();
        m_data = derived_data = new(m_buffer) derived_data_type(arg...);
    }

    template <typename derived_data_type>
    const char* object::data_size_exception<derived_data_type>::what() const
    {
        return "Too big data to create instance within internal buffer. Use reference instance .";
    }
}

// Unicode signature: Владимир Керимов
