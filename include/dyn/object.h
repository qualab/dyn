// dynamically typified object

#pragma once

#include <dyn/public.h>
#include <exception>
#include <cstddef>
#include <cstdint>
#include <iosfwd>

#ifndef DYN_OBJECT_MAX_DATA_SIZE
// Class object uses internal memory block for its data
// Memory for virtual table x64 pointer and 4 x64 fields
// It is enough for decimal, vectors and quaternions
// For matrices use reference type with shared instance
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
        bool is_not_null() const;

        template <typename value_type>
        object(value_type value);

        template <typename value_type>
        object& operator = (value_type value);

        class data;

        virtual void output_data(std::ostream& stream) const;

        static const size_t max_data_size = DYN_OBJECT_MAX_DATA_SIZE;

        template <class derived_data_type>
        class data_size_exception;

    protected:
        template <class derived_data_type, typename... arg_list>
        derived_data_type* initialize(arg_list... arg);

        const data* get_data() const;
        virtual void reset();

    private:
        char m_buffer[max_data_size];
        data* m_data;
    };

    DYN_PUBLIC std::ostream& operator << (std::ostream& stream, const object& argument);

    class DYN_PUBLIC object::data
    {
    public:
        data() { }
        virtual ~data() { }

        virtual data* move_to(void*) = 0;
        virtual data* copy_to(void*) = 0;

        virtual void output(std::ostream& stream) const = 0;

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
        : m_data(nullptr)
    {
        *this = value;
    }

    template <typename value_type>
    object& object::operator = (value_type value)
    {
        static_assert(false, "Cannot assign value of this type to object. Implement template specification to accept such assignment.");
    }

    template <typename derived_data_type, typename... arg_list>
    derived_data_type* object::initialize(arg_list... arg)
    {
        derived_data_type* result = nullptr;
        reset();
        if (sizeof(derived_data_type) > max_data_size)
            throw data_size_exception<derived_data_type>();
        m_data = result = new(m_buffer) derived_data_type(arg...);
        return result;
    }

    template <typename derived_data_type>
    const char* object::data_size_exception<derived_data_type>::what() const
    {
        return "Too big data to create instance within internal buffer. Use reference instance .";
    }

    template <> DYN_PUBLIC object& object::operator = (std::int64_t);
    template <> DYN_PUBLIC object& object::operator = (std::int32_t);
    template <> DYN_PUBLIC object& object::operator = (std::int16_t);
    template <> DYN_PUBLIC object& object::operator = (std::int8_t);

    template <> DYN_PUBLIC object& object::operator = (std::uint64_t);
    template <> DYN_PUBLIC object& object::operator = (std::uint32_t);
    template <> DYN_PUBLIC object& object::operator = (std::uint16_t);
    template <> DYN_PUBLIC object& object::operator = (std::uint8_t);

    template <> DYN_PUBLIC object& object::operator = (double);
    template <> DYN_PUBLIC object& object::operator = (float);

    template <> DYN_PUBLIC object& object::operator = (std::nullptr_t);
}

// Unicode signature: Владимир Керимов
