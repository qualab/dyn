// dynamically typified object

#include <dyn/object.h>
#include <dyn/scalar.h>
#include <typeinfo>
#include <iostream>
#include <utility>

namespace dyn
{
    object::object()
        : m_data(nullptr)
    {
    }

    object::~object()
    {
        reset();
    }

    object::object(const object& another)
        : m_data(nullptr)
    {
        *this = another;
    }

    object::object(object&& temporary)
        : m_data(nullptr)
    {
        *this = std::move(temporary);
    }

    object& object::operator = (const object& another)
    {
        reset();
        if (another.m_data)
            m_data = another.m_data->copy_to(m_buffer);
        return *this;
    }

    object& object::operator = (object&& temporary)
    {
        reset();
        if (temporary.m_data)
            m_data = temporary.m_data->move_to(m_buffer);
        return *this;
    }

    void object::reset()
    {
        if (m_data)
        {
            m_data->~data();
            m_data = nullptr;
        }
    }

    bool object::is_null() const
    {
        return m_data == nullptr;
    }

    bool object::is_not_null() const
    {
        return !is_null();
    }

    const object::data* object::get_data() const
    {
        return m_data;
    }

    const char* object::data::name() const
    {
        return typeid(*this).name();
    }

    void object::output_data(std::ostream& stream) const
    {
        if (m_data)
            m_data->output(stream);
        else
            stream << "null";
    }

    std::ostream& operator << (std::ostream& stream, const object& argument)
    {
        stream << "object{";
        argument.output_data(stream);
        return stream << '}';
    }

    template <> object& object::operator = (std::int64_t value)
    {
        initialize<scalar<std::int64_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (std::int32_t value)
    {
        initialize<scalar<std::int32_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (std::int16_t value)
    {
        initialize<scalar<std::int16_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (std::int8_t value)
    {
        initialize<scalar<std::int8_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (std::uint64_t value)
    {
        initialize<scalar<std::uint64_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (std::uint32_t value)
    {
        initialize<scalar<std::uint32_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (std::uint16_t value)
    {
        initialize<scalar<std::uint16_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (std::uint8_t value)
    {
        initialize<scalar<std::uint8_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (double value)
    {
        initialize<scalar<double>::data>(value);
        return *this;
    }

    template <> object& object::operator = (float value)
    {
        initialize<scalar<float>::data>(value);
        return *this;
    }

    template <> object& object::operator = (std::nullptr_t)
    {
        reset();
        return *this;
    }
}

// Unicode signature: Владимир Керимов
