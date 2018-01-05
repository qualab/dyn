// dynamically typified object

#include <dyn/integer.h>
#include <sstream>
#include <limits>
#include <cmath>

namespace dyn
{
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

    integer::operator std::int64_t() const
    {
        return cast_to<std::int64_t>();
    }

    integer::operator std::int32_t() const
    {
        return cast_to<std::int32_t>();
    }

    integer::operator std::int16_t() const
    {
        return cast_to<std::int16_t>();
    }

    integer::operator std::int8_t() const
    {
        return cast_to<std::int8_t>();
    }

    integer::operator std::uint64_t() const
    {
        return cast_to<std::uint64_t>();
    }

    integer::operator std::uint32_t() const
    {
        return cast_to<std::uint32_t>();
    }

    integer::operator std::uint16_t() const
    {
        return cast_to<std::uint16_t>();
    }

    integer::operator std::uint8_t() const
    {
        return cast_to<std::uint8_t>();
    }

    integer::operator double() const
    {
        return cast_to<double>();
    }

    integer::operator float() const
    {
        return cast_to<float>();
    }

    integer::operator char() const
    {
        return cast_to<char>();
    }

    integer::data::data()
        : m_head(), m_tail()
    {
    }

    integer::data::data(std::int64_t value)
        : m_head(value), m_tail()
    {
    }

    integer::data::data(std::int64_t head, std::uint64_t tail)
        : m_head(head), m_tail({tail})
    {
        correct_tail();
    }

    integer::data::data(std::int64_t head, const integer::data::tail_type& tail)
        : m_head(head), m_tail(tail)
    {
        correct_tail();
    }

    integer::data::data(double value)
        : m_head(), m_tail()
    {
        // TODO: double -> integer
    }

    integer::data::data(float value)
        : m_head(), m_tail()
    {
        // TODO: float -> integer
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
        return m_head || tail_size();
    }

    void integer::data::output(std::ostream& stream) const
    {
        if (tail_size())
        {
            stream << m_head;
        }
        else
        {
            // TODO: integer -> ostream
        }
    }

    size_t integer::data::tail_size() const
    {
        size_t number = max_tail_size;
        for ( ; number && !m_tail[number - 1]; --number);
        return number;
    }

    void integer::data::correct_tail()
    {
        static const std::uint64_t tail_top_bit = 1uLL << 63;

        if (!m_head && tail_size() == 1 && !(m_tail[0] & tail_top_bit))
        {
            m_head = static_cast<std::int64_t>(m_tail[0]);
            m_tail[0] = 0;
        }
    }

    namespace
    {
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
