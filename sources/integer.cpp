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

    integer integer::operator + (const integer& another) const
    {
        integer result = *this;
        return result += another;
    }

    integer integer::operator - (const integer& another) const
    {
        integer result = *this;
        return result -= another;
    }

    integer integer::operator * (const integer& another) const
    {
        integer result = *this;
        return result *= another;
    }

    integer integer::operator / (const integer& another) const
    {
        integer result = *this;
        return result /= another;
    }

    integer integer::operator % (const integer& another) const
    {
        integer result = *this;
        return result %= another;
    }

    integer& integer::operator += (const integer& another)
    {
        m_data->add(*another.m_data);
        return *this;
    }

    integer& integer::operator -= (const integer& another)
    {
        m_data->sub(*another.m_data);
        return *this;
    }

    integer& integer::operator *= (const integer& another)
    {
        m_data->mul(*another.m_data);
        return *this;
    }

    integer& integer::operator /= (const integer& another)
    {
        m_data->div(*another.m_data);
        return *this;
    }

    integer& integer::operator %= (const integer& another)
    {
        m_data->mod(*another.m_data);
        return *this;
    }

    integer integer::operator - () const
    {
        integer result = *this;
        result.m_data->unary_minus();
        return result;
    }

    integer integer::operator ~ () const
    {
        integer result = *this;
        result.m_data->binary_inverse();
        return result;
    }

    integer integer::operator & (const integer& another) const
    {
        integer result;
        return result &= another;
    }

    integer integer::operator | (const integer& another) const
    {
        integer result;
        return result |= another;
    }

    integer integer::operator ^ (const integer& another) const
    {
        integer result;
        return result ^= another;
    }

    integer& integer::operator &= (const integer& another)
    {
        m_data->binary_and(*another.m_data);
        return *this;
    }

    integer& integer::operator |= (const integer& another)
    {
        m_data->binary_or(*another.m_data);
        return *this;
    }

    integer& integer::operator ^= (const integer& another)
    {
        m_data->binary_xor(*another.m_data);
        return *this;
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
        constexpr std::uint64_t pow10[] = {
            1uLL,
            10uLL,
            100uLL,
            1000uLL,
            10000uLL,
            100000uLL,
            1000000uLL,
            10000000uLL,
            100000000uLL,
            1000000000uLL,
            10000000000uLL,
            100000000000uLL,
            1000000000000uLL,
            10000000000000uLL,
            100000000000000uLL,
            1000000000000000uLL,
            10000000000000000uLL,
            100000000000000000uLL,
            1000000000000000000uLL,
            10000000000000000000uLL,
        };

        int int64_digits(std::int64_t value)
        {
            std::uint64_t number(std::abs(value));
            static constexpr int int64_min_digits = 1;
            static constexpr int int64_max_digits = 19;
            int result = int64_min_digits;
            for (; result < int64_max_digits; ++result)
            {
                if (number < pow10[result])
                    break;
            }
            return result;
        }

        template <typename float_type, typename result_type>
        result_type round_lossless(float_type value, result_type lossy)
        {
            // value must be non-negative
            result_type result = static_cast<result_type>(value);
            result_type mod = result % lossy;
            if (mod)
            {
                if (mod <= lossy / 2)
                    result -= mod;
                else
                    result += lossy - mod;
            }
            return result;
        }

        template <typename float_type>
        void range_check_convert(float_type value, std::int64_t& signed_value, std::uint64_t& unsigned_value)
        {
            static constexpr float_type min_signed = static_cast<float_type>(std::numeric_limits<std::int64_t>::min());
            static constexpr float_type max_signed = static_cast<float_type>(std::numeric_limits<std::int64_t>::max());
            static constexpr float_type max_unsigned = static_cast<float_type>(std::numeric_limits<std::uint64_t>::max());

            // common case: convert floating point value to signed 64-bit integer
            // floating point is lossy format, integer must be rounded
            // lossless round depends of how many decimal digits may contain in mantissa
            if (value >= min_signed && value <= max_signed)
            {
                signed_value = static_cast<std::int64_t>(value);
                unsigned_value = 0;

                int digits = int64_digits(signed_value);
                int lost = digits - std::numeric_limits<float_type>::digits10;
                if (lost > 0)
                {
                    std::int64_t lossy(pow10[lost]);
                    signed_value = value >= 0 ?  round_lossless( value, lossy)
                                              : -round_lossless(-value, lossy);
                }
            }
            // case when floating point value can be represented as unsigned 64-bit integer
            // but it is too big for signed 64-bit integer
            else if (value >= 0 && value <= max_unsigned)
            {
                // 19 digits because of 20th higher (if present) is always 1 for biggest unsigned
                // 1 is default for floating-point format and not found in mantissa
                static constexpr std::uint64_t lossy = pow10[19 - std::numeric_limits<float_type>::digits10];
                signed_value = 0;
                unsigned_value = round_lossless(value, lossy);
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

    bool integer::data::is_zero() const
    {
        return !m_unsigned && !m_signed;
    }

    bool integer::data::is_unit() const
    {
        return !m_unsigned && m_signed == 1;
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

    namespace
    {
        constexpr std::uint64_t max_signed_uint64(std::numeric_limits<std::int64_t>::max());
        constexpr std::uint64_t min_signed_uint64(std::numeric_limits<std::int64_t>::min());

        std::uint64_t safe_abs(std::int64_t value)
        {
            if (value >= 0 || value == std::numeric_limits<std::int64_t>::min())
                return static_cast<std::uint64_t>(value);
            else
                return static_cast<std::uint64_t>(-value);
        }

        // if possible convert integer with the sign specified
        // returns false when arithmetic overflow must be thrown
        bool safe_sign(bool negative, std::uint64_t& unsigned_value, std::int64_t& signed_value)
        {
            if (unsigned_value)
            {
                if (unsigned_value <= max_signed_uint64)
                {
                    signed_value = negative ? -static_cast<std::int64_t>(unsigned_value)
                        : static_cast<std::int64_t>(unsigned_value);
                    unsigned_value = 0;
                }
                else if (negative && unsigned_value == min_signed_uint64)
                {
                    signed_value = static_cast<std::int64_t>(unsigned_value);
                    unsigned_value = 0;
                }
                else
                {
                    signed_value = 0;
                    return !negative;
                }
            }
            else
            {
                if (!negative && signed_value == std::numeric_limits<std::int64_t>::min())
                {
                    unsigned_value = min_signed_uint64;
                    signed_value = 0;
                }
                else
                {
                    signed_value = -signed_value;
                }
            }
            return true;
        }

        bool is_negative(std::uint64_t unsigned_value, std::int64_t signed_value)
        {
            return !unsigned_value && signed_value < 0;
        }

        bool sign_and_sides(std::uint64_t& left,          std::uint64_t& right,
                            std::uint64_t  left_unsigned, std::uint64_t  right_unsigned,
                            std::int64_t   left_signed,   std::int64_t   right_signed)
        {
            bool left_negative = is_negative(left_unsigned, left_signed);
            bool right_negative = is_negative(right_unsigned, right_signed);

            left = left_unsigned ? left_unsigned : safe_abs(left_signed);
            right = right_unsigned ? right_unsigned : safe_abs(right_signed);

            return left_negative ^ right_negative;
        }

        int top_bit(std::uint64_t value)
        {
            int bit = 63;
            for (std::uint64_t mask = 1uLL << 63; bit && !(value & mask); --bit, mask >>= 1);
            return bit;
        }
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
        else if (!m_unsigned && !another.m_unsigned)
        {
            if (m_signed >= 0 && another.m_signed >= 0)
            {
                std::uint64_t result = static_cast<std::uint64_t>(m_signed) + static_cast<std::uint64_t>(another.m_signed);
                if (result <= max_signed_uint64)
                {
                    m_signed = static_cast<std::int64_t>(result);
                    m_unsigned = 0;
                }
                else
                {
                    m_unsigned = result;
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
                m_unsigned = greater - safe_abs(lesser);
                safe_sign(false, m_unsigned, m_signed);
            }
        }
    }

    void integer::data::sub(const data& another)
    {
        if (m_unsigned && another.m_unsigned)
        {
            if (m_unsigned >= another.m_unsigned)
            {
                m_signed = static_cast<std::int64_t>(m_unsigned - another.m_unsigned);
            }
            else
            {
                m_signed = -static_cast<std::int64_t>(another.m_unsigned - m_unsigned);
            }
            m_unsigned = 0;
        }
        else if (!another.m_unsigned)
        {
            integer::data negated = another;
            negated.unary_minus();
            add(negated);
        }
        else
        {
            integer::data negated = another;
            negated.sub(*this);
            negated.unary_minus();
            *this = negated;
        }
    }

    void integer::data::mul(const data& another)
    {
        static const char* const operation_name = "multiplication";

        if (is_zero() || another.is_unit())
            return;

        if (another.is_zero() || is_unit())
        {
            *this = another;
            return;
        }

        std::uint64_t left, right;
        bool negative = sign_and_sides(left,       right,
                                       m_unsigned, another.m_unsigned,
                                       m_signed,   another.m_signed);

        int left_bit  = top_bit(left);
        int right_bit = top_bit(right);
        if (left_bit + right_bit > 63)
            throw arithmetic_overflow_exception(operation_name, *this, another);

        m_unsigned = left * right;
        m_signed = 0;

        if (m_unsigned < left || m_unsigned < right
                || !safe_sign(negative, m_unsigned, m_signed))
        {
            throw arithmetic_overflow_exception(operation_name, *this, another);
        }
    }

    void integer::data::div(const data& another)
    {
        static const char* const operation_name = "division";

        if (!another.as_bool())
            throw arithmetic_overflow_exception(operation_name, *this, another);

        std::uint64_t left, right;
        bool negative = sign_and_sides(left,       right,
                                       m_unsigned, another.m_unsigned,
                                       m_signed,   another.m_signed);
        m_unsigned = left / right;
        m_signed = 0;

        if (!safe_sign(negative, m_unsigned, m_signed))
            throw arithmetic_overflow_exception(operation_name, *this, another);
    }

    void integer::data::mod(const data& another)
    {
        static const char* const operation_name = "module";

        if (!another.as_bool())
            throw arithmetic_overflow_exception(operation_name, *this, another);

        std::uint64_t left, right;
        bool negative = sign_and_sides(left,       right,
                                       m_unsigned, another.m_unsigned,
                                       m_signed,   another.m_signed);
        m_unsigned = left % right;
        m_signed = 0;

        if (!safe_sign(negative, m_unsigned, m_signed))
            throw arithmetic_overflow_exception(operation_name, *this, another);
    }

    void integer::data::unary_minus()
    {
        static const char* const operation_name = "negation";

        bool negative = !is_negative(m_unsigned, m_signed);

        if (!safe_sign(negative, m_unsigned, m_signed))
            throw arithmetic_overflow_exception(operation_name, *this);
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
        return !is_zero();
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
