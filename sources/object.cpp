// dynamically typified object

#include <dyn/object.h>
#include <stdexcept>
#include <utility>

namespace dyn
{
    object::object()
        : m_data(nullptr)
    {
    }

    object::~object()
    {
        if (m_data)
            m_data->~data();
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
        return m_data != nullptr;
    }

    object::data* object::initialize(object::data* derived)
    {
        if (static_cast<void*>(derived) != static_cast<void*>(m_buffer))
            std::runtime_error("Unable to initialize the object by somehow instead of placement new into internal buffer.");
        m_data = derived;
        return m_data;
    }

}

// Unicode signature: Владимир Керимов
