// dynamically typified object

#include <dyn/integer.h>
#include <sstream>
#include <limits>
#include <cmath>

namespace dyn
{
	namespace
	{
		template <typename float_type>
		void range_check_convert(float_type value, std::int64_t& signed_value, std::uint64_t& unsigned_value)
		{
			static const float_type min_signed = static_cast<float_type>(std::numeric_limits<std::int64_t>::min());
			static const float_type max_signed = static_cast<float_type>(std::numeric_limits<std::int64_t>::max());
			static const float_type max_unsigned = static_cast<float_type>(std::numeric_limits<std::uint64_t>::max());

			if (value >= min_signed && value <= max_signed)
			{
				signed_value = static_cast<std::int64_t>(value);
				unsigned_value = 0;
			}
			else if (value <= max_unsigned)
			{
				signed_value = 0;
				unsigned_value = static_cast<std::uint64_t>(value);
			}
			else
			{
				signed_value = 0;
				unsigned_value = 0;
				throw integer::out_of_range_exception_of<float_type>(value);
			}
		}
	}

    integer::integer()
        : m_data(initialize<data>())
    {
    }

	integer::integer(const integer& another)
		: m_data(initialize<data>(*another.m_data))
	{
	}

	integer& integer::operator = (const integer& another)
	{
		m_data = initialize<data>(*another.m_data);
		return *this;
	}

	integer::integer(integer&& temporary)
		: m_data(initialize<data>(std::move(*temporary.m_data)))
	{
	}

	integer& integer::operator = (integer&& temporary)
	{
		m_data = initialize<data>(std::move(*temporary.m_data));
		return *this;
	}

	integer::integer(const object& another)
		: m_data(initialize<data>(another.data_as<data>()))
	{
	}

	integer& integer::operator = (const object& another)
	{
		m_data = initialize<data>(another.data_as<data>());
		return *this;
	}

	integer::integer(object&& temporary)
		: m_data(initialize<data>(std::move(temporary.data_as<data>())))
	{
	}

	integer& integer::operator = (object&& temporary)
	{
		m_data = initialize<data>(std::move(temporary.data_as<data>()));
		return *this;
	}

	integer::integer(std::int64_t value)
        : m_data(initialize<data>(value))
    {
    }

    integer::integer(std::int32_t value)
        : m_data(initialize<data>(value))
    {
    }

    integer::integer(std::int16_t value)
        : m_data(initialize<data>(value))
    {
    }

    integer::integer(std::int8_t value)
        : m_data(initialize<data>(value))
    {
    }

    integer::integer(std::uint64_t value)
        : m_data(initialize<data>(value))
    {
    }

    integer::integer(std::uint32_t value)
        : m_data(initialize<data>(value))
    {
    }

    integer::integer(std::uint16_t value)
        : m_data(initialize<data>(value))
    {
    }

    integer::integer(std::uint8_t value)
        : m_data(initialize<data>(value))
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
        : m_signed(), m_unsigned()
    {
    }

    integer::data::data(std::int64_t value)
        : m_signed(value), m_unsigned()
    {
    }

	integer::data::data(std::int32_t value)
		: m_signed(value), m_unsigned()
	{
	}

	integer::data::data(std::int16_t value)
		: m_signed(value), m_unsigned()
	{
	}

	integer::data::data(std::int8_t value)
		: m_signed(value), m_unsigned()
	{
	}

	integer::data::data(std::uint64_t value)
        : m_signed(), m_unsigned(value)
    {
		static const std::uint64_t max_signed = std::numeric_limits<std::int64_t>::max();
		if (m_unsigned <= max_signed)
		{
			m_signed = value;
			m_unsigned = 0;
		}
    }

	integer::data::data(std::uint32_t value)
		: m_signed(value), m_unsigned()
	{
	}

	integer::data::data(std::uint16_t value)
		: m_signed(value), m_unsigned()
	{
	}

	integer::data::data(std::uint8_t value)
		: m_signed(value), m_unsigned()
	{
	}

	integer::data::data(double value)
		: m_signed(), m_unsigned()
	{
		range_check_convert(value, m_signed, m_unsigned);
    }

    integer::data::data(float value)
		: m_signed(), m_unsigned()
    {
		range_check_convert(value, m_signed, m_unsigned);
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
        return m_signed || m_unsigned;
    }

    void integer::data::output(std::ostream& stream) const
    {
		if (m_unsigned)
			stream << m_unsigned;
		else
			stream << m_signed;
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
