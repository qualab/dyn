// scalar storage with scalar data and overloaded operators

#pragma once

#include <dyn/object.h>

namespace dyn
{
    class DYN_PUBLIC integer : public object
    {
    public:
        typedef object base;

        integer();

        integer(const integer& another);
        integer& operator = (const integer& another);

        integer(integer&& temorary);
        integer& operator = (integer&& temorary);

        integer(const object& another);
        integer& operator = (const object& another);

        integer(object&& temporary);
        integer& operator = (object&& temporary);

        template <typename value_type>
        explicit integer(value_type value);

        template <typename value_type>
        explicit operator value_type() const;

        integer(std::int64_t value);
        integer(std::int32_t value);
        integer(std::int16_t value);
        integer(std::int8_t value);

        integer(std::uint64_t value);
        integer(std::uint32_t value);
        integer(std::uint16_t value);
        integer(std::uint8_t value);

        explicit integer(double value);
        explicit integer(float value);

        explicit integer(char value);

        explicit integer(bool value);

        template <typename value_type>
        bool is_of() const;

        template <typename value_type>
        value_type cast_to() const;

        operator std::int64_t() const;
        operator std::int32_t() const;
        operator std::int16_t() const;
        operator std::int8_t() const;

        operator std::uint64_t() const;
        operator std::uint32_t() const;
        operator std::uint16_t() const;
        operator std::uint8_t() const;

        explicit operator double() const;
        explicit operator float() const;

        explicit operator char() const;

        integer& operator = (std::int64_t value);
        integer& operator = (std::int32_t value);
        integer& operator = (std::int16_t value);
        integer& operator = (std::int8_t value);

        integer& operator = (std::uint64_t value);
        integer& operator = (std::uint32_t value);
        integer& operator = (std::uint16_t value);
        integer& operator = (std::uint8_t value);

        integer& operator = (double value);
        integer& operator = (float value);

        integer& operator = (char value);

        integer& operator = (bool value);

        bool operator == (const integer& another) const;
        bool operator != (const integer& another) const;

        bool operator <= (const integer& another) const;
        bool operator >= (const integer& another) const;

        bool operator < (const integer& another) const;
        bool operator > (const integer& another) const;

        integer operator + (const integer& another) const;
        integer operator - (const integer& another) const;
        integer operator * (const integer& another) const;
        integer operator / (const integer& another) const;
        integer operator % (const integer& another) const;

        integer& operator += (const integer& another);
        integer& operator -= (const integer& another);
        integer& operator *= (const integer& another);
        integer& operator /= (const integer& another);
        integer& operator %= (const integer& another);

        integer operator ~ () const;

        integer operator & (const integer& another) const;
        integer operator | (const integer& another) const;
        integer operator ^ (const integer& another) const;

        integer& operator &= (const integer& another);
        integer& operator |= (const integer& another);
        integer& operator ^= (const integer& another);

        class data;

        class exception;
        class out_of_range_exception;
        class type_cast_exception;
        class arithmetic_overflow_exception;

        template <typename value_type>
        class out_of_range_exception_of;

        template <typename value_type>
        class type_cast_exception_of;

    private:
        data* m_data;
    };

    class DYN_PUBLIC integer::data : public object::data
    {
    public:
        typedef object::data base;

        data();

        data(std::int64_t value);
        data(std::int32_t value);
        data(std::int16_t value);
        data(std::int8_t value);

        data(std::uint64_t value);
        data(std::uint32_t value);
        data(std::uint16_t value);
        data(std::uint8_t value);

        data(double value);
        data(float value);

        virtual object::data* move_to(void* buffer) override;
        virtual object::data* copy_to(void* buffer) override;

        virtual const char* name() const override;

        virtual bool equals_to(const data& another) const;
        virtual bool lesser_than(const data& another) const;
        virtual bool greater_than(const data& another) const;

        virtual void add(const data& another);
        virtual void sub(const data& another);
        virtual void mul(const data& another);
        virtual void div(const data& another);
        virtual void mod(const data& another);

        virtual void unary_minus();

        virtual void binary_inverse();

        virtual void binary_and(const data& another);
        virtual void binary_or(const data& another);
        virtual void binary_xor(const data& another);

        virtual bool as_bool() const override;
        virtual void output(std::ostream& stream) const override;

        virtual bool of_int64() const;
        virtual bool of_int32() const;
        virtual bool of_int16() const;
        virtual bool of_int8()  const;

        virtual bool of_uint64() const;
        virtual bool of_uint32() const;
        virtual bool of_uint16() const;
        virtual bool of_uint8()  const;

        virtual std::int64_t as_int64() const;
        virtual std::int32_t as_int32() const;
        virtual std::int16_t as_int16() const;
        virtual std::int8_t  as_int8() const;

        virtual std::uint64_t as_uint64() const;
        virtual std::uint32_t as_uint32() const;
        virtual std::uint16_t as_uint16() const;
        virtual std::uint8_t  as_uint8() const;

        virtual double as_double() const;
        virtual float as_float() const;

        virtual std::string as_string() const;

    private:
        std::int64_t m_signed;
        std::uint64_t m_unsigned;
    };

    class DYN_PUBLIC integer::exception : public object::exception
    {
    public:
        typedef object::exception base;

        exception(const std::string& message);
    };

    class DYN_PUBLIC integer::out_of_range_exception : public integer::exception
    {
    public:
        typedef integer::exception base;

        out_of_range_exception(const std::string& message);
    };

    class DYN_PUBLIC integer::type_cast_exception : public integer::exception
    {
    public:
        typedef integer::exception base;

        type_cast_exception(const std::string& message);
    };

    class DYN_PUBLIC integer::arithmetic_overflow_exception : public integer::exception
    {
    public:
        typedef integer::exception base;

        arithmetic_overflow_exception(const std::string& operation, const integer::data& single);
        arithmetic_overflow_exception(const std::string& operation, const integer::data& left, const integer::data& right);
    };

    template <typename value_type>
    class integer::out_of_range_exception_of : public integer::out_of_range_exception
    {
    public:
        typedef out_of_range_exception base;

        out_of_range_exception_of(value_type value);

    private:
        static std::string gen_message(value_type value);
    };

    template <typename value_type>
    class integer::type_cast_exception_of : public integer::type_cast_exception
    {
    public:
        typedef integer::type_cast_exception base;

        type_cast_exception_of(const integer& value);

    private:
        static std::string gen_message(const integer& value);
    };

    template <typename value_type>
    integer::integer(value_type value)
        : m_data(initialize<data>())
    {
        *this = value;
    }

    template <typename value_type>
    integer::operator value_type() const
    {
        return cast_to<value_type>();
    }

    template <typename value_type>
    integer::out_of_range_exception_of<value_type>::out_of_range_exception_of(value_type value)
        : base(gen_message(value))
    {
    }

    template <typename value_type>
    integer::type_cast_exception_of<value_type>::type_cast_exception_of(const integer& value)
        : base(gen_message(value))
    {
    }

    template <> DYN_PUBLIC bool integer::is_of<std::int64_t>() const;
    template <> DYN_PUBLIC bool integer::is_of<std::int32_t>() const;
    template <> DYN_PUBLIC bool integer::is_of<std::int16_t>() const;
    template <> DYN_PUBLIC bool integer::is_of<std::int8_t>() const;

    template <> DYN_PUBLIC bool integer::is_of<std::uint64_t>() const;
    template <> DYN_PUBLIC bool integer::is_of<std::uint32_t>() const;
    template <> DYN_PUBLIC bool integer::is_of<std::uint16_t>() const;
    template <> DYN_PUBLIC bool integer::is_of<std::uint8_t>() const;

    template <> DYN_PUBLIC std::int64_t integer::cast_to() const;
    template <> DYN_PUBLIC std::int32_t integer::cast_to() const;
    template <> DYN_PUBLIC std::int16_t integer::cast_to() const;
    template <> DYN_PUBLIC std::int8_t  integer::cast_to() const;

    template <> DYN_PUBLIC std::uint64_t integer::cast_to() const;
    template <> DYN_PUBLIC std::uint32_t integer::cast_to() const;
    template <> DYN_PUBLIC std::uint16_t integer::cast_to() const;
    template <> DYN_PUBLIC std::uint8_t  integer::cast_to() const;

    template <> DYN_PUBLIC double integer::cast_to() const;
    template <> DYN_PUBLIC float  integer::cast_to() const;

    template <> DYN_PUBLIC bool integer::cast_to() const;

    template <> DYN_PUBLIC std::string    integer::cast_to() const;
    template <> DYN_PUBLIC std::wstring   integer::cast_to() const;
    template <> DYN_PUBLIC std::u32string integer::cast_to() const;

    template <> DYN_PUBLIC char integer::cast_to() const;

    template <> DYN_PUBLIC std::string integer::out_of_range_exception_of<double>::gen_message(double value);
    template <> DYN_PUBLIC std::string integer::out_of_range_exception_of<float>::gen_message(float value);

    template <> DYN_PUBLIC std::string integer::type_cast_exception_of<std::int64_t>::gen_message(const integer& value);
    template <> DYN_PUBLIC std::string integer::type_cast_exception_of<std::int32_t>::gen_message(const integer& value);
    template <> DYN_PUBLIC std::string integer::type_cast_exception_of<std::int16_t>::gen_message(const integer& value);
    template <> DYN_PUBLIC std::string integer::type_cast_exception_of<std::int8_t>::gen_message(const integer& value);

    template <> DYN_PUBLIC std::string integer::type_cast_exception_of<std::uint64_t>::gen_message(const integer& value);
    template <> DYN_PUBLIC std::string integer::type_cast_exception_of<std::uint32_t>::gen_message(const integer& value);
    template <> DYN_PUBLIC std::string integer::type_cast_exception_of<std::uint16_t>::gen_message(const integer& value);
    template <> DYN_PUBLIC std::string integer::type_cast_exception_of<std::uint8_t>::gen_message(const integer& value);

    template <> DYN_PUBLIC std::string integer::type_cast_exception_of<double>::gen_message(const integer& value);
    template <> DYN_PUBLIC std::string integer::type_cast_exception_of<float>::gen_message(const integer& value);

    inline bool operator == (const integer& left, std::int64_t right) { return left == integer(right); }
    inline bool operator == (const integer& left, std::int32_t right) { return left == integer(right); }
    inline bool operator == (const integer& left, std::int16_t right) { return left == integer(right); }
    inline bool operator == (const integer& left, std::int8_t  right) { return left == integer(right); }

    inline bool operator == (const integer& left, std::uint64_t right) { return left == integer(right); }
    inline bool operator == (const integer& left, std::uint32_t right) { return left == integer(right); }
    inline bool operator == (const integer& left, std::uint16_t right) { return left == integer(right); }
    inline bool operator == (const integer& left, std::uint8_t  right) { return left == integer(right); }

    inline bool operator == (std::int64_t left, const integer& right) { return integer(left) == right; }
    inline bool operator == (std::int32_t left, const integer& right) { return integer(left) == right; }
    inline bool operator == (std::int16_t left, const integer& right) { return integer(left) == right; }
    inline bool operator == (std::int8_t  left, const integer& right) { return integer(left) == right; }

    inline bool operator == (std::uint64_t left, const integer& right) { return integer(left) == right; }
    inline bool operator == (std::uint32_t left, const integer& right) { return integer(left) == right; }
    inline bool operator == (std::uint16_t left, const integer& right) { return integer(left) == right; }
    inline bool operator == (std::uint8_t  left, const integer& right) { return integer(left) == right; }

    inline bool operator != (const integer& left, std::int64_t right) { return left != integer(right); }
    inline bool operator != (const integer& left, std::int32_t right) { return left != integer(right); }
    inline bool operator != (const integer& left, std::int16_t right) { return left != integer(right); }
    inline bool operator != (const integer& left, std::int8_t  right) { return left != integer(right); }

    inline bool operator != (const integer& left, std::uint64_t right) { return left != integer(right); }
    inline bool operator != (const integer& left, std::uint32_t right) { return left != integer(right); }
    inline bool operator != (const integer& left, std::uint16_t right) { return left != integer(right); }
    inline bool operator != (const integer& left, std::uint8_t  right) { return left != integer(right); }

    inline bool operator != (std::int64_t left, const integer& right) { return integer(left) != right; }
    inline bool operator != (std::int32_t left, const integer& right) { return integer(left) != right; }
    inline bool operator != (std::int16_t left, const integer& right) { return integer(left) != right; }
    inline bool operator != (std::int8_t  left, const integer& right) { return integer(left) != right; }

    inline bool operator != (std::uint64_t left, const integer& right) { return integer(left) != right; }
    inline bool operator != (std::uint32_t left, const integer& right) { return integer(left) != right; }
    inline bool operator != (std::uint16_t left, const integer& right) { return integer(left) != right; }
    inline bool operator != (std::uint8_t  left, const integer& right) { return integer(left) != right; }

    inline bool operator >= (const integer& left, std::int64_t right) { return left >= integer(right); }
    inline bool operator >= (const integer& left, std::int32_t right) { return left >= integer(right); }
    inline bool operator >= (const integer& left, std::int16_t right) { return left >= integer(right); }
    inline bool operator >= (const integer& left, std::int8_t  right) { return left >= integer(right); }

    inline bool operator >= (const integer& left, std::uint64_t right) { return left >= integer(right); }
    inline bool operator >= (const integer& left, std::uint32_t right) { return left >= integer(right); }
    inline bool operator >= (const integer& left, std::uint16_t right) { return left >= integer(right); }
    inline bool operator >= (const integer& left, std::uint8_t  right) { return left >= integer(right); }

    inline bool operator >= (std::int64_t left, const integer& right) { return integer(left) >= right; }
    inline bool operator >= (std::int32_t left, const integer& right) { return integer(left) >= right; }
    inline bool operator >= (std::int16_t left, const integer& right) { return integer(left) >= right; }
    inline bool operator >= (std::int8_t  left, const integer& right) { return integer(left) >= right; }

    inline bool operator >= (std::uint64_t left, const integer& right) { return integer(left) >= right; }
    inline bool operator >= (std::uint32_t left, const integer& right) { return integer(left) >= right; }
    inline bool operator >= (std::uint16_t left, const integer& right) { return integer(left) >= right; }
    inline bool operator >= (std::uint8_t  left, const integer& right) { return integer(left) >= right; }

    inline bool operator <= (const integer& left, std::int64_t right) { return left <= integer(right); }
    inline bool operator <= (const integer& left, std::int32_t right) { return left <= integer(right); }
    inline bool operator <= (const integer& left, std::int16_t right) { return left <= integer(right); }
    inline bool operator <= (const integer& left, std::int8_t  right) { return left <= integer(right); }

    inline bool operator <= (const integer& left, std::uint64_t right) { return left <= integer(right); }
    inline bool operator <= (const integer& left, std::uint32_t right) { return left <= integer(right); }
    inline bool operator <= (const integer& left, std::uint16_t right) { return left <= integer(right); }
    inline bool operator <= (const integer& left, std::uint8_t  right) { return left <= integer(right); }

    inline bool operator <= (std::int64_t left, const integer& right) { return integer(left) <= right; }
    inline bool operator <= (std::int32_t left, const integer& right) { return integer(left) <= right; }
    inline bool operator <= (std::int16_t left, const integer& right) { return integer(left) <= right; }
    inline bool operator <= (std::int8_t  left, const integer& right) { return integer(left) <= right; }

    inline bool operator <= (std::uint64_t left, const integer& right) { return integer(left) <= right; }
    inline bool operator <= (std::uint32_t left, const integer& right) { return integer(left) <= right; }
    inline bool operator <= (std::uint16_t left, const integer& right) { return integer(left) <= right; }
    inline bool operator <= (std::uint8_t  left, const integer& right) { return integer(left) <= right; }

    inline bool operator > (const integer& left, std::int64_t right) { return left > integer(right); }
    inline bool operator > (const integer& left, std::int32_t right) { return left > integer(right); }
    inline bool operator > (const integer& left, std::int16_t right) { return left > integer(right); }
    inline bool operator > (const integer& left, std::int8_t  right) { return left > integer(right); }

    inline bool operator > (const integer& left, std::uint64_t right) { return left > integer(right); }
    inline bool operator > (const integer& left, std::uint32_t right) { return left > integer(right); }
    inline bool operator > (const integer& left, std::uint16_t right) { return left > integer(right); }
    inline bool operator > (const integer& left, std::uint8_t  right) { return left > integer(right); }

    inline bool operator > (std::int64_t left, const integer& right) { return integer(left) > right; }
    inline bool operator > (std::int32_t left, const integer& right) { return integer(left) > right; }
    inline bool operator > (std::int16_t left, const integer& right) { return integer(left) > right; }
    inline bool operator > (std::int8_t  left, const integer& right) { return integer(left) > right; }

    inline bool operator > (std::uint64_t left, const integer& right) { return integer(left) > right; }
    inline bool operator > (std::uint32_t left, const integer& right) { return integer(left) > right; }
    inline bool operator > (std::uint16_t left, const integer& right) { return integer(left) > right; }
    inline bool operator > (std::uint8_t  left, const integer& right) { return integer(left) > right; }

    inline bool operator < (const integer& left, std::int64_t right) { return left < integer(right); }
    inline bool operator < (const integer& left, std::int32_t right) { return left < integer(right); }
    inline bool operator < (const integer& left, std::int16_t right) { return left < integer(right); }
    inline bool operator < (const integer& left, std::int8_t  right) { return left < integer(right); }

    inline bool operator < (const integer& left, std::uint64_t right) { return left < integer(right); }
    inline bool operator < (const integer& left, std::uint32_t right) { return left < integer(right); }
    inline bool operator < (const integer& left, std::uint16_t right) { return left < integer(right); }
    inline bool operator < (const integer& left, std::uint8_t  right) { return left < integer(right); }

    inline bool operator < (std::int64_t left, const integer& right) { return integer(left) < right; }
    inline bool operator < (std::int32_t left, const integer& right) { return integer(left) < right; }
    inline bool operator < (std::int16_t left, const integer& right) { return integer(left) < right; }
    inline bool operator < (std::int8_t  left, const integer& right) { return integer(left) < right; }

    inline bool operator < (std::uint64_t left, const integer& right) { return integer(left) < right; }
    inline bool operator < (std::uint32_t left, const integer& right) { return integer(left) < right; }
    inline bool operator < (std::uint16_t left, const integer& right) { return integer(left) < right; }
    inline bool operator < (std::uint8_t  left, const integer& right) { return integer(left) < right; }

    inline integer operator + (const integer& left, std::int64_t right) { return left + integer(right); }
    inline integer operator + (const integer& left, std::int32_t right) { return left + integer(right); }
    inline integer operator + (const integer& left, std::int16_t right) { return left + integer(right); }
    inline integer operator + (const integer& left, std::int8_t  right) { return left + integer(right); }

    inline integer operator + (const integer& left, std::uint64_t right) { return left + integer(right); }
    inline integer operator + (const integer& left, std::uint32_t right) { return left + integer(right); }
    inline integer operator + (const integer& left, std::uint16_t right) { return left + integer(right); }
    inline integer operator + (const integer& left, std::uint8_t  right) { return left + integer(right); }

    inline integer operator + (std::int64_t left, const integer& right) { return integer(left) + right; }
    inline integer operator + (std::int32_t left, const integer& right) { return integer(left) + right; }
    inline integer operator + (std::int16_t left, const integer& right) { return integer(left) + right; }
    inline integer operator + (std::int8_t  left, const integer& right) { return integer(left) + right; }

    inline integer operator + (std::uint64_t left, const integer& right) { return integer(left) + right; }
    inline integer operator + (std::uint32_t left, const integer& right) { return integer(left) + right; }
    inline integer operator + (std::uint16_t left, const integer& right) { return integer(left) + right; }
    inline integer operator + (std::uint8_t  left, const integer& right) { return integer(left) + right; }

    inline integer operator - (const integer& left, std::int64_t right) { return left - integer(right); }
    inline integer operator - (const integer& left, std::int32_t right) { return left - integer(right); }
    inline integer operator - (const integer& left, std::int16_t right) { return left - integer(right); }
    inline integer operator - (const integer& left, std::int8_t  right) { return left - integer(right); }

    inline integer operator - (const integer& left, std::uint64_t right) { return left - integer(right); }
    inline integer operator - (const integer& left, std::uint32_t right) { return left - integer(right); }
    inline integer operator - (const integer& left, std::uint16_t right) { return left - integer(right); }
    inline integer operator - (const integer& left, std::uint8_t  right) { return left - integer(right); }

    inline integer operator - (std::int64_t left, const integer& right) { return integer(left) - right; }
    inline integer operator - (std::int32_t left, const integer& right) { return integer(left) - right; }
    inline integer operator - (std::int16_t left, const integer& right) { return integer(left) - right; }
    inline integer operator - (std::int8_t  left, const integer& right) { return integer(left) - right; }

    inline integer operator - (std::uint64_t left, const integer& right) { return integer(left) - right; }
    inline integer operator - (std::uint32_t left, const integer& right) { return integer(left) - right; }
    inline integer operator - (std::uint16_t left, const integer& right) { return integer(left) - right; }
    inline integer operator - (std::uint8_t  left, const integer& right) { return integer(left) - right; }

    inline integer operator * (const integer& left, std::int64_t right) { return left * integer(right); }
    inline integer operator * (const integer& left, std::int32_t right) { return left * integer(right); }
    inline integer operator * (const integer& left, std::int16_t right) { return left * integer(right); }
    inline integer operator * (const integer& left, std::int8_t  right) { return left * integer(right); }

    inline integer operator * (const integer& left, std::uint64_t right) { return left * integer(right); }
    inline integer operator * (const integer& left, std::uint32_t right) { return left * integer(right); }
    inline integer operator * (const integer& left, std::uint16_t right) { return left * integer(right); }
    inline integer operator * (const integer& left, std::uint8_t  right) { return left * integer(right); }

    inline integer operator * (std::int64_t left, const integer& right) { return integer(left) * right; }
    inline integer operator * (std::int32_t left, const integer& right) { return integer(left) * right; }
    inline integer operator * (std::int16_t left, const integer& right) { return integer(left) * right; }
    inline integer operator * (std::int8_t  left, const integer& right) { return integer(left) * right; }

    inline integer operator * (std::uint64_t left, const integer& right) { return integer(left) * right; }
    inline integer operator * (std::uint32_t left, const integer& right) { return integer(left) * right; }
    inline integer operator * (std::uint16_t left, const integer& right) { return integer(left) * right; }
    inline integer operator * (std::uint8_t  left, const integer& right) { return integer(left) * right; }

    inline integer operator / (const integer& left, std::int64_t right) { return left / integer(right); }
    inline integer operator / (const integer& left, std::int32_t right) { return left / integer(right); }
    inline integer operator / (const integer& left, std::int16_t right) { return left / integer(right); }
    inline integer operator / (const integer& left, std::int8_t  right) { return left / integer(right); }

    inline integer operator / (const integer& left, std::uint64_t right) { return left / integer(right); }
    inline integer operator / (const integer& left, std::uint32_t right) { return left / integer(right); }
    inline integer operator / (const integer& left, std::uint16_t right) { return left / integer(right); }
    inline integer operator / (const integer& left, std::uint8_t  right) { return left / integer(right); }

    inline integer operator / (std::int64_t left, const integer& right) { return integer(left) / right; }
    inline integer operator / (std::int32_t left, const integer& right) { return integer(left) / right; }
    inline integer operator / (std::int16_t left, const integer& right) { return integer(left) / right; }
    inline integer operator / (std::int8_t  left, const integer& right) { return integer(left) / right; }

    inline integer operator / (std::uint64_t left, const integer& right) { return integer(left) / right; }
    inline integer operator / (std::uint32_t left, const integer& right) { return integer(left) / right; }
    inline integer operator / (std::uint16_t left, const integer& right) { return integer(left) / right; }
    inline integer operator / (std::uint8_t  left, const integer& right) { return integer(left) / right; }

    inline integer operator & (const integer& left, std::int64_t right) { return left & integer(right); }
    inline integer operator & (const integer& left, std::int32_t right) { return left & integer(right); }
    inline integer operator & (const integer& left, std::int16_t right) { return left & integer(right); }
    inline integer operator & (const integer& left, std::int8_t  right) { return left & integer(right); }

    inline integer operator & (const integer& left, std::uint64_t right) { return left & integer(right); }
    inline integer operator & (const integer& left, std::uint32_t right) { return left & integer(right); }
    inline integer operator & (const integer& left, std::uint16_t right) { return left & integer(right); }
    inline integer operator & (const integer& left, std::uint8_t  right) { return left & integer(right); }

    inline integer operator & (std::int64_t left, const integer& right) { return integer(left) & right; }
    inline integer operator & (std::int32_t left, const integer& right) { return integer(left) & right; }
    inline integer operator & (std::int16_t left, const integer& right) { return integer(left) & right; }
    inline integer operator & (std::int8_t  left, const integer& right) { return integer(left) & right; }

    inline integer operator & (std::uint64_t left, const integer& right) { return integer(left) & right; }
    inline integer operator & (std::uint32_t left, const integer& right) { return integer(left) & right; }
    inline integer operator & (std::uint16_t left, const integer& right) { return integer(left) & right; }
    inline integer operator & (std::uint8_t  left, const integer& right) { return integer(left) & right; }

    inline integer operator | (const integer& left, std::int64_t right) { return left | integer(right); }
    inline integer operator | (const integer& left, std::int32_t right) { return left | integer(right); }
    inline integer operator | (const integer& left, std::int16_t right) { return left | integer(right); }
    inline integer operator | (const integer& left, std::int8_t  right) { return left | integer(right); }

    inline integer operator | (const integer& left, std::uint64_t right) { return left | integer(right); }
    inline integer operator | (const integer& left, std::uint32_t right) { return left | integer(right); }
    inline integer operator | (const integer& left, std::uint16_t right) { return left | integer(right); }
    inline integer operator | (const integer& left, std::uint8_t  right) { return left | integer(right); }

    inline integer operator | (std::int64_t left, const integer& right) { return integer(left) | right; }
    inline integer operator | (std::int32_t left, const integer& right) { return integer(left) | right; }
    inline integer operator | (std::int16_t left, const integer& right) { return integer(left) | right; }
    inline integer operator | (std::int8_t  left, const integer& right) { return integer(left) | right; }

    inline integer operator | (std::uint64_t left, const integer& right) { return integer(left) | right; }
    inline integer operator | (std::uint32_t left, const integer& right) { return integer(left) | right; }
    inline integer operator | (std::uint16_t left, const integer& right) { return integer(left) | right; }
    inline integer operator | (std::uint8_t  left, const integer& right) { return integer(left) | right; }

    inline integer operator ^ (const integer& left, std::int64_t right) { return left ^ integer(right); }
    inline integer operator ^ (const integer& left, std::int32_t right) { return left ^ integer(right); }
    inline integer operator ^ (const integer& left, std::int16_t right) { return left ^ integer(right); }
    inline integer operator ^ (const integer& left, std::int8_t  right) { return left ^ integer(right); }

    inline integer operator ^ (const integer& left, std::uint64_t right) { return left ^ integer(right); }
    inline integer operator ^ (const integer& left, std::uint32_t right) { return left ^ integer(right); }
    inline integer operator ^ (const integer& left, std::uint16_t right) { return left ^ integer(right); }
    inline integer operator ^ (const integer& left, std::uint8_t  right) { return left ^ integer(right); }

    inline integer operator ^ (std::int64_t left, const integer& right) { return integer(left) ^ right; }
    inline integer operator ^ (std::int32_t left, const integer& right) { return integer(left) ^ right; }
    inline integer operator ^ (std::int16_t left, const integer& right) { return integer(left) ^ right; }
    inline integer operator ^ (std::int8_t  left, const integer& right) { return integer(left) ^ right; }

    inline integer operator ^ (std::uint64_t left, const integer& right) { return integer(left) ^ right; }
    inline integer operator ^ (std::uint32_t left, const integer& right) { return integer(left) ^ right; }
    inline integer operator ^ (std::uint16_t left, const integer& right) { return integer(left) ^ right; }
    inline integer operator ^ (std::uint8_t  left, const integer& right) { return integer(left) ^ right; }

    inline integer& operator += (integer& left, std::int64_t right) { return left += integer(right); }
    inline integer& operator += (integer& left, std::int32_t right) { return left += integer(right); }
    inline integer& operator += (integer& left, std::int16_t right) { return left += integer(right); }
    inline integer& operator += (integer& left, std::int8_t  right) { return left += integer(right); }

    inline integer& operator -= (integer& left, std::int64_t right) { return left -= integer(right); }
    inline integer& operator -= (integer& left, std::int32_t right) { return left -= integer(right); }
    inline integer& operator -= (integer& left, std::int16_t right) { return left -= integer(right); }
    inline integer& operator -= (integer& left, std::int8_t  right) { return left -= integer(right); }

    inline integer& operator *= (integer& left, std::int64_t right) { return left *= integer(right); }
    inline integer& operator *= (integer& left, std::int32_t right) { return left *= integer(right); }
    inline integer& operator *= (integer& left, std::int16_t right) { return left *= integer(right); }
    inline integer& operator *= (integer& left, std::int8_t  right) { return left *= integer(right); }

    inline integer& operator /= (integer& left, std::int64_t right) { return left /= integer(right); }
    inline integer& operator /= (integer& left, std::int32_t right) { return left /= integer(right); }
    inline integer& operator /= (integer& left, std::int16_t right) { return left /= integer(right); }
    inline integer& operator /= (integer& left, std::int8_t  right) { return left /= integer(right); }

    inline integer& operator &= (integer& left, std::int64_t right) { return left &= integer(right); }
    inline integer& operator &= (integer& left, std::int32_t right) { return left &= integer(right); }
    inline integer& operator &= (integer& left, std::int16_t right) { return left &= integer(right); }
    inline integer& operator &= (integer& left, std::int8_t  right) { return left &= integer(right); }

    inline integer& operator |= (integer& left, std::int64_t right) { return left |= integer(right); }
    inline integer& operator |= (integer& left, std::int32_t right) { return left |= integer(right); }
    inline integer& operator |= (integer& left, std::int16_t right) { return left |= integer(right); }
    inline integer& operator |= (integer& left, std::int8_t  right) { return left |= integer(right); }

    inline integer& operator ^= (integer& left, std::int64_t right) { return left ^= integer(right); }
    inline integer& operator ^= (integer& left, std::int32_t right) { return left ^= integer(right); }
    inline integer& operator ^= (integer& left, std::int16_t right) { return left ^= integer(right); }
    inline integer& operator ^= (integer& left, std::int8_t  right) { return left ^= integer(right); }
}

// Unicode signature: Владимир Керимов
