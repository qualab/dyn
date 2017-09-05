// dynamically typified object

#pragma once

#include <dyn/public.h>

#ifndef DYN_OBJECT_MAX_DATA_SIZE
#define DYN_OBJECT_MAX_DATA_SIZE 16
#endif

namespace dyn
{
    class DYN_PUBLIC object
    {
    public:
        object();
        ~object();

        object(const object& another);
        object(object&& temporary);

        object& operator = (const object& another);
        object& operator = (object&& temporary);

        template <typename value_type>
        object(value_type value);

        template <typename value_type>
        object& operator = (value_type value);

        void reset();

        bool is_null() const;

        static const size_t max_data_size = DYN_OBJECT_MAX_DATA_SIZE;

        class data;

    protected:
        void* buffer() { return m_buffer; }
        data* initialize(data* derived);

    private:
        char m_buffer[max_data_size];
        data* m_data;
    };

    class DYN_PUBLIC object::data
    {
    public:
        virtual ~data() { }
        virtual data* move_to(void*) = 0;
        virtual data* copy_to(void*) = 0;
    };

    template <typename value_type>
    object::object(value_type value)
        : m_data(nullptr)
    {
        *this = value;
    }

    template <typename value_type>
    object& object::operator = (value_type value)
    {
        static_assert(false, "The initialization operator template specification must be implemented for this type.");
    }
}

// Unicode signature: Владимир Керимов
