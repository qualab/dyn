// scalar storage with scalar data and overloaded operators

#pragma once

#include <dyn/object.h>
#include <iostream>

namespace dyn
{
    template <typename value_type>
    class scalar : public object
    {
    public:
        typedef object base;

        scalar();

        scalar(const scalar& another);
        scalar& operator = (const scalar& another);

        scalar(const object& another);
        scalar& operator = (const object& another);

        scalar(value_type scalar_value);
        scalar& operator = (value_type scalar_value);

        operator value_type () const;

        const value_type& value() const;
        value_type& value();

        bool operator ! () const;

        bool operator == (const scalar& another) const;
        bool operator != (const scalar& another) const;

        bool operator <= (const scalar& another) const;
        bool operator >= (const scalar& another) const;

        bool operator < (const scalar& another) const;
        bool operator > (const scalar& another) const;

        scalar operator + (const scalar& another) const;
        scalar operator - (const scalar& another) const;
        scalar operator * (const scalar& another) const;
        scalar operator / (const scalar& another) const;

        scalar operator + () const;
        scalar operator - () const;

        scalar& operator += (const scalar& another);
        scalar& operator -= (const scalar& another);
        scalar& operator *= (const scalar& another);
        scalar& operator /= (const scalar& another);

        scalar& operator ++ ();
        scalar& operator -- ();

        scalar operator ++ (int);
        scalar operator -- (int);

        bool operator == (value_type another_value) const;
        bool operator != (value_type another_value) const;

        bool operator <= (value_type another_value) const;
        bool operator >= (value_type another_value) const;

        bool operator < (value_type another_value) const;
        bool operator > (value_type another_value) const;

        scalar operator + (value_type another_value) const;
        scalar operator - (value_type another_value) const;
        scalar operator * (value_type another_value) const;
        scalar operator / (value_type another_value) const;

        scalar& operator += (value_type another_value);
        scalar& operator -= (value_type another_value);
        scalar& operator *= (value_type another_value);
        scalar& operator /= (value_type another_value);

        class data;

        static const char* const class_name;
        virtual const char* const get_class_name() const override;

    private:
        data* m_data;
    };

    template <typename value_type>
    class scalar<value_type>::data : public object::data
    {
    public:
        typedef object::data base;

        data();
        data(value_type value);

        virtual object::data* move_to(void*) override;
        virtual object::data* copy_to(void*) override;

        virtual bool as_bool() const override;

        virtual void output(std::ostream& stream) const override;

        const value_type& value() const;
        value_type& value();

        static const char* const class_name;
        virtual const char* const get_class_name() const override;

    private:
        value_type m_value;
    };

    template <typename value_type>
    scalar<value_type>::scalar()
        : m_data(nullptr)
    {
        m_data = initialize<data>();
    }

    template <typename value_type>
    scalar<value_type>::scalar(const scalar<value_type>& another)
        : m_data(nullptr)
    {
        m_data = initialize<data>(another.value());
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator = (const scalar<value_type>& another)
    {
        m_data = initialize<data>(another.value());
        return *this;
    }

    template <typename value_type>
    scalar<value_type>::scalar(const object& another)
        : m_data(nullptr)
    {
        *this = another;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator = (const object& another)
    {
        value() = another.data_as<data>().value();
        return *this;
    }

    template <typename value_type>
    scalar<value_type>::scalar(value_type scalar_value)
        : m_data(nullptr)
    {
        m_data = initialize<data>(scalar_value);
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator = (value_type scalar_value)
    {
        value() = scalar_value;
        return *this;
    }

    template <typename value_type>
    scalar<value_type>::operator value_type() const
    {
        return value();
    }

    template <typename value_type>
    const value_type& scalar<value_type>::value() const
    {
        return m_data->value();
    }

    template <typename value_type>
    value_type& scalar<value_type>::value()
    {
        return m_data->value();
    }

    template <typename value_type>
    const char* const scalar<value_type>::get_class_name() const
    {
        return class_name;
    }

    template <typename value_type>
    bool scalar<value_type>::operator ! () const
    {
        return !value();
    }

    template <typename value_type>
    bool scalar<value_type>::operator == (const scalar<value_type>& another) const
    {
        return value() == another.value();
    }

    template <typename value_type>
    bool scalar<value_type>::operator != (const scalar<value_type>& another) const
    {
        return value() != another.value();
    }

    template <typename value_type>
    bool scalar<value_type>::operator <= (const scalar<value_type>& another) const
    {
        return value() <= another.value();
    }

    template <typename value_type>
    bool scalar<value_type>::operator >= (const scalar<value_type>& another) const
    {
        return value() >= another.value();
    }

    template <typename value_type>
    bool scalar<value_type>::operator < (const scalar<value_type>& another) const
    {
        return value() < another.value();
    }

    template <typename value_type>
    bool scalar<value_type>::operator > (const scalar<value_type>& another) const
    {
        return value() > another.value();
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator + (const scalar<value_type>& another) const
    {
        return scalar<value_type>(value() + another.value());
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator - (const scalar<value_type>& another) const
    {
        return scalar<value_type>(value() - another.value());
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator * (const scalar<value_type>& another) const
    {
        return scalar<value_type>(value() * another.value());
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator / (const scalar<value_type>& another) const
    {
        return scalar<value_type>(value() / another.value());
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator + () const
    {
        return scalar<value_type>(+value());
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator - () const
    {
        return scalar<value_type>(-value());
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator += (const scalar<value_type>& another)
    {
        value() += another.value();
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator -= (const scalar<value_type>& another)
    {
        value() -= another.value();
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator *= (const scalar<value_type>& another)
    {
        value() *= another.value();
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator /= (const scalar<value_type>& another)
    {
        value() /= another.value();
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator ++ ()
    {
        ++value();
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator -- ()
    {
        --value();
        return *this;
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator ++ (int)
    {
        scalar<value_type> result(value());
        ++value();
        return *this;
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator -- (int)
    {
        scalar<value_type> result(value());
        --value();
        return *this;
    }

    template <typename value_type>
    bool scalar<value_type>::operator == (value_type another_value) const
    {
        return value() == another_value;
    }

    template <typename value_type>
    bool scalar<value_type>::operator != (value_type another_value) const
    {
        return value() != another_value;
    }

    template <typename value_type>
    bool scalar<value_type>::operator <= (value_type another_value) const
    {
        return value() <= another_value;
    }

    template <typename value_type>
    bool scalar<value_type>::operator >= (value_type another_value) const
    {
        return value() >= another_value;
    }

    template <typename value_type>
    bool scalar<value_type>::operator < (value_type another_value) const
    {
        return value() < another_value;
    }

    template <typename value_type>
    bool scalar<value_type>::operator > (value_type another_value) const
    {
        return value() > another_value;
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator + (value_type another_value) const
    {
        return scalar<value_type>(value() + another_value);
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator - (value_type another_value) const
    {
        return scalar<value_type>(value() - another_value);
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator * (value_type another_value) const
    {
        return scalar<value_type>(value() * another_value);
    }

    template <typename value_type>
    scalar<value_type> scalar<value_type>::operator / (value_type another_value) const
    {
        return scalar<value_type>(value() / another_value);
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator += (value_type another_value)
    {
        value() += another_value;
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator -= (value_type another_value)
    {
        value() -= another_value;
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator *= (value_type another_value)
    {
        value() *= another_value;
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator /= (value_type another_value)
    {
        value() /= another_value;
        return *this;
    }

    template <typename value_type>
    scalar<value_type>::data::data()
        : m_value()
    {
    }

    template <typename value_type>
    scalar<value_type>::data::data(value_type value)
        : m_value(value)
    {
    }

    template <typename value_type>
    object::data* scalar<value_type>::data::move_to(void* buffer)
    {
        return new(buffer) data(std::move(*this));
    }

    template <typename value_type>
    object::data* scalar<value_type>::data::copy_to(void* buffer)
    {
        return new(buffer) data(*this);
    }

    template <typename value_type>
    bool scalar<value_type>::data::as_bool() const
    {
        return m_value != 0;
    }

    template <typename value_type>
    void scalar<value_type>::data::output(std::ostream& stream) const
    {
        stream << m_value;
    }

    template <typename value_type>
    const value_type& scalar<value_type>::data::value() const
    {
        return m_value;
    }

    template <typename value_type>
    value_type& scalar<value_type>::data::value()
    {
        return m_value;
    }

    template <typename value_type>
    const char* const scalar<value_type>::data::get_class_name() const
    {
        return class_name;
    }

    template<> const char* const scalar<int64>::class_name = "scalar<int64>";
    template<> const char* const scalar<int32>::class_name = "scalar<int32>";
    template<> const char* const scalar<int16>::class_name = "scalar<int16>";
    template<> const char* const scalar<int8>::class_name = "scalar<int8>";

    template<> const char* const scalar<uint64>::class_name = "scalar<uint64>";
    template<> const char* const scalar<uint32>::class_name = "scalar<uint32>";
    template<> const char* const scalar<uint16>::class_name = "scalar<uint16>";
    template<> const char* const scalar<uint8>::class_name = "scalar<uint8>";

    template<> const char* const scalar<double>::class_name = "scalar<double>";
    template<> const char* const scalar<float>::class_name = "scalar<float>";

    template<> const char* const scalar<bool>::class_name = "scalar<bool>";
    template<> const char* const scalar<char>::class_name = "scalar<char>";

    template<> const char* const scalar<int64>::data::class_name = "scalar<int64>::data";
    template<> const char* const scalar<int32>::data::class_name = "scalar<int32>::data";
    template<> const char* const scalar<int16>::data::class_name = "scalar<int16>::data";
    template<> const char* const scalar<int8>::data::class_name = "scalar<int8>::data";

    template<> const char* const scalar<uint64>::data::class_name = "scalar<uint64>::data";
    template<> const char* const scalar<uint32>::data::class_name = "scalar<uint32>::data";
    template<> const char* const scalar<uint16>::data::class_name = "scalar<uint16>::data";
    template<> const char* const scalar<uint8>::data::class_name = "scalar<uint8>::data";

    template<> const char* const scalar<double>::data::class_name = "scalar<double>::data";
    template<> const char* const scalar<float>::data::class_name = "scalar<float>::data";

    template<> const char* const scalar<bool>::data::class_name = "scalar<bool>::data";
    template<> const char* const scalar<char>::data::class_name = "scalar<char>::data";
}

// Unicode signature: Владимир Керимов
