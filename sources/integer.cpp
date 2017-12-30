// dynamically typified object

#include <dyn/integer.h>
#include <sstream>
#include <limits>
#include <cmath>

namespace dyn
{
    namespace
    {
        const std::uint64_t tail_top_bit = static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::min());

        const float max_float_to_head = static_cast<float>(std::numeric_limits<std::int64_t>::max());
        const float min_float_to_head = static_cast<float>(std::numeric_limits<std::int64_t>::min());
        const float max_float_to_tail = static_cast<float>(std::numeric_limits<std::uint64_t>::max());

        const float float_to_integer_base = max_float_to_tail + 1.0f;
        const float max_float_to_integer = max_float_to_head * float_to_integer_base + max_float_to_tail;
        const float min_float_to_integer = min_float_to_head * float_to_integer_base - max_float_to_tail;

        const double max_double_to_head = static_cast<double>(std::numeric_limits<std::int64_t>::max());
        const double min_double_to_head = static_cast<double>(std::numeric_limits<std::int64_t>::min());
        const double max_double_to_tail = static_cast<double>(std::numeric_limits<std::uint64_t>::max());

        const double double_to_integer_base = max_double_to_tail + 1.0;
        const double max_double_to_integer = max_double_to_head * double_to_integer_base + max_double_to_tail;
        const double min_double_to_integer = min_double_to_head * double_to_integer_base - max_double_to_tail;

        std::string float_to_string(float value)
        {
            std::stringstream result;
            result << value;
            return result.str();
        }

        std::string double_to_string(double value)
        {
            std::stringstream result;
            result << value;
            return result.str();
        }
    }

    integer::integer()
        : m_data(initialize<data>())
    {
    }

    integer::integer(std::int64_t value)
        : m_data(initialize<data>(value))
    {
    }

    integer::integer(std::int32_t value)
        : m_data(initialize<data>(static_cast<std::int64_t>(value)))
    {
    }

    integer::integer(std::int16_t value)
        : m_data(initialize<data>(static_cast<std::int64_t>(value)))
    {
    }

    integer::integer(std::int8_t value)
        : m_data(initialize<data>(static_cast<std::int64_t>(value)))
    {
    }

    integer::integer(std::uint64_t value)
        : m_data(initialize<data>(0, value))
    {
    }

    integer::integer(std::uint32_t value)
        : m_data(initialize<data>(static_cast<std::int64_t>(value)))
    {
    }

    integer::integer(std::uint16_t value)
        : m_data(initialize<data>(static_cast<std::int64_t>(value)))
    {
    }

    integer::integer(std::uint8_t value)
        : m_data(initialize<data>(static_cast<std::int64_t>(value)))
    {
    }

    integer::integer(double value)
        : m_data(initialize<data>(value))
    {
    }

    integer::integer(float value)
        : m_data(initialize<data>(value))
    {
    }

    integer::integer(char value)
        : m_data(initialize<data>(static_cast<std::int64_t>(value)))
    {
    }

    integer::integer(bool value)
        : m_data(initialize<data>(value ? 1LL : 0LL))
    {
    }

    integer::data::data(std::int64_t head, std::uint64_t tail)
        : m_head(head), m_tail(tail)
    {
        if (!m_head && !(m_tail & tail_top_bit))
        {
            m_head = static_cast<std::int64_t>(m_tail);
            m_tail = 0;
        }
    }

    integer::data::data(double value)
        : m_head(), m_tail()
    {
        if (value >= 0)
        {
            if (value <= max_double_to_head)
            {
                m_head = static_cast<std::int64_t>(value);
            }
            else if (value <= max_double_to_integer)
            {
                m_head = static_cast<std::int64_t>(value / double_to_integer_base);
                m_tail = static_cast<std::int64_t>(fmod(value, double_to_integer_base));
            }
            else
            {
                throw integer::out_of_range_exception_of<double>(value);
            }
        }
        else
        {
            if (value >= min_double_to_head)
            {
                m_head = static_cast<std::int64_t>(value);
            }
            else if (value >= min_double_to_integer)
            {
                m_head = static_cast<std::int64_t>(value / double_to_integer_base);
                m_tail = static_cast<std::int64_t>(fmod(value, double_to_integer_base));
            }
            else
            {
                throw integer::out_of_range_exception_of<double>(value);
            }
        }
    }

    integer::data::data(float value)
        : m_head(), m_tail()
    {
        if (value >= 0)
        {
            if (value <= max_float_to_head)
            {
                m_head = static_cast<std::int64_t>(value);
            }
            else if (value <= max_float_to_integer)
            {
                m_head = static_cast<std::int64_t>(value / float_to_integer_base);
                m_tail = static_cast<std::int64_t>(fmod(value, float_to_integer_base));
            }
            else
            {
                throw integer::out_of_range_exception_of<float>(value);
            }
        }
        else
        {
            if (value >= min_float_to_head)
            {
                m_head = static_cast<std::int64_t>(value);
            }
            else if (value >= min_float_to_integer)
            {
                m_head = static_cast<std::int64_t>(value / float_to_integer_base);
                m_tail = static_cast<std::int64_t>(fmod(value, float_to_integer_base));
            }
            else
            {
                throw integer::out_of_range_exception_of<float>(value);
            }
        }
    }

    object::data* integer::data::move_to(void* buffer)
    {
        return new(buffer) integer::data(*this);
    }

    object::data* integer::data::copy_to(void* buffer)
    {
        return new(buffer) integer::data(*this);
    }

    const char* integer::data::name() const
    {
        return "integer";
    }

    bool integer::data::as_bool() const
    {
        return m_head || m_tail;
    }

    void integer::data::output(std::ostream& stream) const
    {
        if (!m_tail)
        {
            stream << m_head;
        }
        else
        {
            double value = m_head * double_to_integer_base + m_tail;
            stream << value;
        }
    }

    integer::out_of_range_exception::out_of_range_exception(double value)
        : base("Value " + double_to_string(value) + " is out of range to be represented as integer.")
    {
    }

    integer::out_of_range_exception::out_of_range_exception(float value)
        : base("Value " + float_to_string(value) + " is out of range to be represented as integer.")
    {
    }
}

// Unicode signature: Владимир Керимов
