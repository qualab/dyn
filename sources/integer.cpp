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

	integer& integer::operator = (std::int64_t value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	integer& integer::operator = (std::int32_t value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	integer& integer::operator = (std::int16_t value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	integer& integer::operator = (std::int8_t value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	integer& integer::operator = (std::uint64_t value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	integer& integer::operator = (std::uint32_t value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	integer& integer::operator = (std::uint16_t value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	integer& integer::operator = (std::uint8_t value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	integer& integer::operator = (double value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	integer& integer::operator = (float value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	integer& integer::operator = (char value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	integer& integer::operator = (bool value)
	{
		m_data = initialize<data>(value);
		return *this;
	}

	bool integer::operator == (const integer& another) const
	{
		return m_data->equals_to(*another.m_data);
	}

	bool integer::operator != (const integer& another) const
	{
		return !m_data->equals_to(*another.m_data);
	}

	bool integer::operator <= (const integer& another) const
	{
		return !m_data->greater_than(*another.m_data);
	}

	bool integer::operator >= (const integer& another) const
	{
		return !m_data->lesser_than(*another.m_data);
	}

	bool integer::operator < (const integer& another) const
	{
		return m_data->lesser_than(*another.m_data);
	}

	bool integer::operator > (const integer& another) const
	{
		return m_data->greater_than(*another.m_data);
	}

	template <> bool integer::is_of<std::int64_t>() const
	{
		return m_data->of_int64();
	}

	template <> bool integer::is_of<std::int32_t>() const
	{
		return m_data->of_int32();
	}

	template <> bool integer::is_of<std::int16_t>() const
	{
		return m_data->of_int16();
	}

	template <> bool integer::is_of<std::int8_t>() const
	{
		return m_data->of_int8();
	}

	template <> bool integer::is_of<std::uint64_t>() const
	{
		return m_data->of_uint64();
	}

	template <> bool integer::is_of<std::uint32_t>() const
	{
		return m_data->of_uint32();
	}

	template <> bool integer::is_of<std::uint16_t>() const
	{
		return m_data->of_uint16();
	}

	template <> bool integer::is_of<std::uint8_t>() const
	{
		return m_data->of_uint8();
	}

	template <> std::int64_t integer::cast_to() const
	{
		if (!is_of<std::int64_t>())
			throw type_cast_exception_of<std::int64_t>(*this);
		return m_data->as_int64();
	}

	template <> std::int32_t integer::cast_to() const
	{
		if (!is_of<std::int32_t>())
			throw type_cast_exception_of<std::int32_t>(*this);
		return m_data->as_int32();
	}

	template <> std::int16_t integer::cast_to() const
	{
		if (!is_of<std::int16_t>())
			throw type_cast_exception_of<std::int16_t>(*this);
		return m_data->as_int16();
	}

	template <> std::int8_t integer::cast_to() const
	{
		if (!is_of<std::int8_t>())
			throw type_cast_exception_of<std::int8_t>(*this);
		return m_data->as_int8();
	}

	template <> std::uint64_t integer::cast_to() const
	{
		if (!is_of<std::uint64_t>())
			throw type_cast_exception_of<std::uint64_t>(*this);
		return m_data->as_uint64();
	}

	template <> std::uint32_t integer::cast_to() const
	{
		if (!is_of<std::uint32_t>())
			throw type_cast_exception_of<std::uint32_t>(*this);
		return m_data->as_uint32();
	}

	template <> std::uint16_t integer::cast_to() const
	{
		if (!is_of<std::uint16_t>())
			throw type_cast_exception_of<std::uint16_t>(*this);
		return m_data->as_uint16();
	}

	template <> std::uint8_t integer::cast_to() const
	{
		if (!is_of<std::uint8_t>())
			throw type_cast_exception_of<std::uint8_t>(*this);
		return m_data->as_uint8();
	}

	template <> double integer::cast_to() const
	{
		return m_data->as_double();
	}

	template <> float integer::cast_to() const
	{
		return m_data->as_float();
	}

	template <> bool integer::cast_to() const
	{
		return m_data->as_bool();
	}

	template <> char integer::cast_to() const
	{
		return m_data->as_int8();
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
		if (value <= max_signed)
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

	bool integer::data::equals_to(const data& another) const
	{
		if (m_unsigned && another.m_unsigned)
			return m_unsigned == another.m_unsigned;
		else if (!m_unsigned && !another.m_unsigned)
			return m_signed == another.m_signed;
		else
			return false;
	}

	bool integer::data::lesser_than(const data& another) const
	{
		if (m_unsigned && another.m_unsigned)
			return m_unsigned < another.m_unsigned;
		else if (!m_unsigned && !another.m_unsigned)
			return m_signed < another.m_signed;
		else
			return another.m_unsigned;
	}

	bool integer::data::greater_than(const data& another) const
	{
		if (m_unsigned && another.m_unsigned)
			return m_unsigned > another.m_unsigned;
		else if (!m_unsigned && !another.m_unsigned)
			return m_signed > another.m_signed;
		else
			return m_unsigned;
	}

	void integer::data::add(const data& another)
	{
		static const char* const operation_name = "addition";
		if (m_unsigned && another.m_unsigned)
		{
			std::uint64_t result = m_unsigned + another.m_unsigned;
			if (result < m_unsigned)
				throw arithmetic_overflow_exception(operation_name, *this, another);
			m_unsigned = result;
		}
		else if (m_signed && m_signed)
		{
			if (m_signed >= 0 && another.m_signed >= 0)
			{
				std::int64_t result = m_signed + another.m_signed;
				if (result >= 0)
					m_signed = result;
				else
				{
					m_unsigned = static_cast<std::uint64_t>(result);
					m_signed = 0;
				}
			}
			else if (m_signed < 0 && another.m_signed < 0)
			{
				std::int64_t result = m_signed + another.m_signed;
				if (result >= 0)
					throw arithmetic_overflow_exception(operation_name, *this, another);
				m_signed = result;
			}
			else
			{
				m_signed += another.m_signed;
			}
		}
		else
		{
			std::uint64_t greater;
			std::int64_t lesser;
			if (m_unsigned)
			{
				greater = m_unsigned;
				lesser = another.m_signed;
			}
			else
			{
				greater = another.m_unsigned;
				lesser = m_signed;
			}
			if (lesser >= 0)
			{
				std::uint64_t result = greater + static_cast<std::uint64_t>(lesser);
				if (result < greater)
					throw arithmetic_overflow_exception(operation_name, *this, another);
				m_unsigned = result;
			}
			else
			{
				static const std::uint64_t max_signed = std::numeric_limits<std::int64_t>::max();
				m_unsigned = greater - static_cast<std::uint64_t>(-lesser);
				if (m_unsigned <= max_signed)
				{
					m_signed = static_cast<std::int64_t>(m_unsigned);
					m_unsigned = 0;
				}
			}
		}
	}

	void integer::data::sub(const data& another)
	{
	}

	void integer::data::mul(const data& another)
	{
	}

	void integer::data::div(const data& another)
	{
	}

	void integer::data::unary_minus()
	{
		m_signed = -m_signed;
	}

	void integer::data::binary_inverse()
	{
		if (m_unsigned)
		{
			m_signed = ~m_unsigned;
			m_unsigned = 0;
		}
		else
			m_signed = ~m_signed;
	}

	void integer::data::binary_and(const data& another)
	{
		std::uint64_t left = m_unsigned ? m_unsigned : static_cast<std::uint64_t>(m_signed);
		std::uint64_t right = another.m_unsigned ? another.m_unsigned : static_cast<std::uint64_t>(another.m_signed);
		left &= right;
		static const std::uint64_t max_signed = std::numeric_limits<std::int64_t>::max();
		if (left <= max_signed)
			m_signed = left;
		else if (m_unsigned || another.m_unsigned)
			m_unsigned = left;
		else
			m_signed = static_cast<std::int64_t>(left);
	}

	void integer::data::binary_or(const data& another)
	{
		std::uint64_t left = m_unsigned ? m_unsigned : static_cast<std::uint64_t>(m_signed);
		std::uint64_t right = another.m_unsigned ? another.m_unsigned : static_cast<std::uint64_t>(another.m_signed);
		left |= right;
		static const std::uint64_t max_signed = std::numeric_limits<std::int64_t>::max();
		if (left <= max_signed)
			m_signed = left;
		else if (m_unsigned || another.m_unsigned)
			m_unsigned = left;
		else
			m_signed = static_cast<std::int64_t>(left);
	}

	void integer::data::binary_xor(const data& another)
	{
		std::uint64_t left = m_unsigned ? m_unsigned : static_cast<std::uint64_t>(m_signed);
		std::uint64_t right = another.m_unsigned ? another.m_unsigned : static_cast<std::uint64_t>(another.m_signed);
		left ^= right;
		static const std::uint64_t max_signed = std::numeric_limits<std::int64_t>::max();
		if (left <= max_signed)
			m_signed = left;
		else if (m_unsigned || another.m_unsigned)
			m_unsigned = left;
		else
			m_signed = static_cast<std::int64_t>(left);
	}

	bool integer::data::as_bool() const
    {
        return m_signed || m_unsigned;
    }

	bool integer::data::of_int64() const
	{
		return !m_unsigned;
	}

	bool integer::data::of_int32() const
	{
		static const std::int64_t min_int32 = std::numeric_limits<std::int32_t>::min();
		static const std::int64_t max_int32 = std::numeric_limits<std::int32_t>::max();
		return !m_unsigned && m_signed >= min_int32 && m_signed <= max_int32;
	}

	bool integer::data::of_int16() const
	{
		static const std::int64_t min_int16 = std::numeric_limits<std::int16_t>::min();
		static const std::int64_t max_int16 = std::numeric_limits<std::int16_t>::max();
		return !m_unsigned && m_signed >= min_int16 && m_signed <= max_int16;
	}

	bool integer::data::of_int8() const
	{
		static const std::int64_t min_int8 = std::numeric_limits<std::int8_t>::min();
		static const std::int64_t max_int8 = std::numeric_limits<std::int8_t>::max();
		return !m_unsigned && m_signed >= min_int8 && m_signed <= max_int8;
	}

	bool integer::data::of_uint64() const
	{
		return m_unsigned || m_signed >= 0;
	}

	bool integer::data::of_uint32() const
	{
		static const std::int64_t max_uint32 = std::numeric_limits<std::uint32_t>::max();
		return !m_unsigned && m_signed >= 0 && m_signed <= max_uint32;
	}

	bool integer::data::of_uint16() const
	{
		static const std::int64_t max_uint16 = std::numeric_limits<std::uint16_t>::max();
		return !m_unsigned && m_signed >= 0 && m_signed <= max_uint16;
	}

	bool integer::data::of_uint8() const
	{
		static const std::int64_t max_uint8 = std::numeric_limits<std::uint8_t>::max();
		return !m_unsigned && m_signed >= 0 && m_signed <= max_uint8;
	}

	std::int64_t integer::data::as_int64() const
	{
		return m_signed;
	}

	std::int32_t integer::data::as_int32() const
	{
		return static_cast<std::int32_t>(m_signed);
	}

	std::int16_t integer::data::as_int16() const
	{
		return static_cast<std::int16_t>(m_signed);
	}

	std::int8_t integer::data::as_int8() const
	{
		return static_cast<std::int8_t>(m_signed);
	}

	std::uint64_t integer::data::as_uint64() const
	{
		return m_unsigned ? m_unsigned : static_cast<std::uint64_t>(m_signed);
	}

	std::uint32_t integer::data::as_uint32() const
	{
		return static_cast<std::uint32_t>(m_signed);
	}

	std::uint16_t integer::data::as_uint16() const
	{
		return static_cast<std::uint16_t>(m_signed);
	}

	std::uint8_t integer::data::as_uint8() const
	{
		return static_cast<std::uint8_t>(m_signed);
	}

	double integer::data::as_double() const
	{
		return m_unsigned ? static_cast<double>(m_unsigned) : static_cast<double>(m_signed);
	}

	float integer::data::as_float() const
	{
		return m_unsigned ? static_cast<float>(m_unsigned) : static_cast<float>(m_signed);
	}

	std::string integer::data::as_string() const
	{
		std::stringstream stream;
		output(stream);
		return stream.str();
	}

	void integer::data::output(std::ostream& stream) const
    {
		if (m_unsigned)
			stream << m_unsigned;
		else
			stream << m_signed;
    }

	integer::exception::exception(const std::string& message)
		: base(message)
	{
	}

	integer::out_of_range_exception::out_of_range_exception(const std::string& message)
		: base(message)
	{
	}

	integer::type_cast_exception::type_cast_exception(const std::string& message)
		: base(message)
	{
	}

	namespace
	{
		inline std::string arithmetic_overflow_message(const std::string& operation, const integer::data& left, const integer::data& right)
		{
			std::stringstream output;
			output << "Arithmetic overflow on binary operation '" << operation 
				<< "' between integers '" << left.as_string() << "' and '" << right.as_string() << "'.";
			return output.str();
		}

		inline std::string arithmetic_overflow_message(const std::string& operation, const integer::data& single)
		{
			std::stringstream output;
			output << "Arithmetic overflow on unary operation '" << operation
				<< "' on integer '" << single.as_string() << "'.";
			return output.str();
		}
	}

	integer::arithmetic_overflow_exception::arithmetic_overflow_exception(const std::string& operation, const integer::data& single)
		: base(arithmetic_overflow_message(operation, single))
	{
	}

	integer::arithmetic_overflow_exception::arithmetic_overflow_exception(const std::string& operation, const integer::data& left, const integer::data& right)
		: base(arithmetic_overflow_message(operation, left, right))
	{
	}

	namespace
	{
		template <typename value_type>
		inline std::string out_of_range_message(value_type value)
		{
			std::stringstream output;
			output << "Value '" << value << "' is out of range to be represented as integer.";
			return output.str();
		}
	}

	template<> std::string integer::out_of_range_exception_of<double>::gen_message(double value)
    {
		return out_of_range_message(value);
    }

	template<> std::string integer::out_of_range_exception_of<float>::gen_message(float value)
	{
		return out_of_range_message(value);
	}

	namespace
	{
		template <typename value_type>
		inline std::string type_cast_message(const integer& value)
		{
			std::stringstream output;
			output << "Integer '" << value << "' cannot be represented as type " << typeid(value_type).name();
			return output.str();
		}
	}

	template<> std::string integer::type_cast_exception_of<int64_t>::gen_message(const integer& value)
	{
		return type_cast_message<int64_t>(value);
	}

	template<> std::string integer::type_cast_exception_of<int32_t>::gen_message(const integer& value)
	{
		return type_cast_message<int32_t>(value);
	}

	template<> std::string integer::type_cast_exception_of<int16_t>::gen_message(const integer& value)
	{
		return type_cast_message<int16_t>(value);
	}

	template<> std::string integer::type_cast_exception_of<int8_t>::gen_message(const integer& value)
	{
		return type_cast_message<int8_t>(value);
	}

	template<> std::string integer::type_cast_exception_of<uint64_t>::gen_message(const integer& value)
	{
		return type_cast_message<uint64_t>(value);
	}

	template<> std::string integer::type_cast_exception_of<uint32_t>::gen_message(const integer& value)
	{
		return type_cast_message<uint32_t>(value);
	}

	template<> std::string integer::type_cast_exception_of<uint16_t>::gen_message(const integer& value)
	{
		return type_cast_message<uint16_t>(value);
	}

	template<> std::string integer::type_cast_exception_of<uint8_t>::gen_message(const integer& value)
	{
		return type_cast_message<uint8_t>(value);
	}

	template<> std::string integer::type_cast_exception_of<double>::gen_message(const integer& value)
	{
		return type_cast_message<double>(value);
	}

	template<> std::string integer::type_cast_exception_of<float>::gen_message(const integer& value)
	{
		return type_cast_message<float>(value);
	}
}

// Unicode signature: Владимир Керимов
