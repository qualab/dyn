// scalar storage with scalar data and overloaded operators

#pragma once

#include <dyn/object.h>

namespace dyn
{
    class integer : public object
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
        integer(value_type value);

        template <typename value_type>
        operator value_type() const;

        integer(std::int64_t value);
        integer(std::int32_t value);
        integer(std::int16_t value);
        integer(std::int8_t value);

        integer(std::uint64_t value);
        integer(std::uint32_t value);
        integer(std::uint16_t value);
        integer(std::uint8_t value);

        integer(double value);
        integer(float value);

        integer(char value);

        integer(bool value);

        template <typename value_type>
        bool is_of() const;

        template <typename value_type>
        value_type cast_to() const;

        explicit operator std::int64_t() const;
		explicit operator std::int32_t() const;
		explicit operator std::int16_t() const;
        explicit operator std::int8_t() const;

		explicit operator std::uint64_t() const;
		explicit operator std::uint32_t() const;
		explicit operator std::uint16_t() const;
		explicit operator std::uint8_t() const;

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

        bool operator == (std::int64_t another) const;
        bool operator == (std::int32_t another) const;
        bool operator == (std::int16_t another) const;
        bool operator == (std::int8_t another) const;

        bool operator == (std::uint64_t another) const;
        bool operator == (std::uint32_t another) const;
        bool operator == (std::uint16_t another) const;
        bool operator == (std::uint8_t another) const;

        bool operator == (double another) const;
        bool operator == (float another) const;

        bool operator == (char another) const;

        bool operator == (bool another) const;

        bool operator != (std::int64_t another) const;
        bool operator != (std::int32_t another) const;
        bool operator != (std::int16_t another) const;
        bool operator != (std::int8_t another) const;

        bool operator != (std::uint64_t another) const;
        bool operator != (std::uint32_t another) const;
        bool operator != (std::uint16_t another) const;
        bool operator != (std::uint8_t another) const;

        bool operator != (double another) const;
        bool operator != (float another) const;

        bool operator != (char another) const;

        bool operator != (bool another) const;

        bool operator <= (std::int64_t another) const;
        bool operator <= (std::int32_t another) const;
        bool operator <= (std::int16_t another) const;
        bool operator <= (std::int8_t another) const;

        bool operator <= (std::uint64_t another) const;
        bool operator <= (std::uint32_t another) const;
        bool operator <= (std::uint16_t another) const;
        bool operator <= (std::uint8_t another) const;

        bool operator <= (double another) const;
        bool operator <= (float another) const;

        bool operator <= (char another) const;

        bool operator <= (bool another) const;

        bool operator >= (std::int64_t another) const;
        bool operator >= (std::int32_t another) const;
        bool operator >= (std::int16_t another) const;
        bool operator >= (std::int8_t another) const;

        bool operator >= (std::uint64_t another) const;
        bool operator >= (std::uint32_t another) const;
        bool operator >= (std::uint16_t another) const;
        bool operator >= (std::uint8_t another) const;

        bool operator >= (double another) const;
        bool operator >= (float another) const;

        bool operator >= (char another) const;

        bool operator >= (bool another) const;

        integer operator + (const integer& another) const;
        integer operator - (const integer& another) const;
        integer operator * (const integer& another) const;
        integer operator / (const integer& another) const;

        integer& operator += (const integer& another);
        integer& operator -= (const integer& another);
        integer& operator *= (const integer& another);
        integer& operator /= (const integer& another);

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

        template <typename value_type>
        class out_of_range_exception_of;

        template <typename value_type>
        class type_cast_exception_of;

    private:
        data* m_data;
    };

    class integer::data : public object::data
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

        virtual bool as_bool() const override;
        virtual void output(std::ostream& stream) const override;

    private:
		std::int64_t m_signed;
		std::uint64_t m_unsigned;
    };

    class integer::exception : public object::exception
    {
    public:
        typedef object::exception base;

        exception(const std::string& message);
    };

    class integer::out_of_range_exception : public integer::exception
    {
    public:
        typedef integer::exception base;

        out_of_range_exception(double value);
        out_of_range_exception(float value);
    };

    class integer::type_cast_exception : public integer::exception
    {
    public:
        typedef integer::exception base;

        type_cast_exception(const integer& value);
    };

    template <typename value_type>
    class integer::out_of_range_exception_of : public integer::out_of_range_exception
    {
    public:
        typedef out_of_range_exception base;

        out_of_range_exception_of(value_type value);
    };

    template <typename value_type>
    class integer::type_cast_exception_of : public integer::type_cast_exception
    {
        typedef integer::type_cast_exception base;

        type_cast_exception_of(const integer& value);
    };

    template <typename value_type>
    integer::out_of_range_exception_of<value_type>::out_of_range_exception_of(value_type value)
        : base(value)
    {
    }

    template <typename value_type>
    integer::type_cast_exception_of<value_type>::type_cast_exception_of(const integer& value)
        : base(value)
    {
    }

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
}

// Unicode signature: Владимир Керимов
