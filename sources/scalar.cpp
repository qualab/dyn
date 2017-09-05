// dynamically typified object

#include <dyn/scalar.h>
#include <new>

namespace dyn
{
    template<> object& object::operator = (std::int64_t value)
    {
        reset();
        m_data = new(m_buffer) scalar<std::int64_t>::data(value);
        return *this;
    }

    template<> object& object::operator = (std::int32_t value)
    {
        reset();
        m_data = new(m_buffer) scalar<std::int32_t>::data(value);
        return *this;
    }

    template<> object& object::operator = (std::int16_t value)
    {
        reset();
        m_data = new(m_buffer) scalar<std::int16_t>::data(value);
        return *this;
    }

    template<> object& object::operator = (std::int8_t value)
    {
        reset();
        m_data = new(m_buffer) scalar<std::int8_t>::data(value);
        return *this;
    }

    template<> object& object::operator = (std::uint64_t value)
    {
        reset();
        m_data = new(m_buffer) scalar<std::uint64_t>::data(value);
        return *this;
    }

    template<> object& object::operator = (std::uint32_t value)
    {
        reset();
        m_data = new(m_buffer) scalar<std::uint32_t>::data(value);
        return *this;
    }

    template<> object& object::operator = (std::uint16_t value)
    {
        reset();
        m_data = new(m_buffer) scalar<std::uint16_t>::data(value);
        return *this;
    }

    template<> object& object::operator = (std::uint8_t value)
    {
        reset();
        m_data = new(m_buffer) scalar<std::uint8_t>::data(value);
        return *this;
    }

    template<> object& object::operator = (double value)
    {
        reset();
        m_data = new(m_buffer) scalar<double>::data(value);
        return *this;
    }

    template<> object& object::operator = (float value)
    {
        reset();
        m_data = new(m_buffer) scalar<float>::data(value);
        return *this;
    }

    template<> object& object::operator = (bool value)
    {
        reset();
        m_data = new(m_buffer) scalar<bool>::data(value);
        return *this;
    }

    template<> object& object::operator = (char value)
    {
        reset();
        m_data = new(m_buffer) scalar<char>::data(value);
        return *this;
    }

    template<> object& object::operator = (wchar_t value)
    {
        reset();
        m_data = new(m_buffer) scalar<wchar_t>::data(value);
        return *this;
    }

    template<> object& object::operator = (std::nullptr_t)
    {
        reset();
        return *this;
    }
}

// Unicode signature: Владимир Керимов
