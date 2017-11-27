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
        scalar();

        scalar(const scalar& another);
        scalar& operator = (const scalar& another);

        scalar(const object& another);
        scalar& operator = (const object& another);

        scalar(value_type value);

        scalar& operator = (value_type value);
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

    protected:
        virtual void reset() override;

    private:
        data* m_data;
    };

    template <typename value_type>
    class scalar<value_type>::data : public object::data
    {
    public:
        data();
        data(value_type value);

        virtual object::data* move_to(void*) override;
        virtual object::data* copy_to(void*) override;

        virtual bool as_bool() const override;

        virtual void output(std::ostream& stream) const override;

        void set(value_type value);
        const value_type& get() const;
        value_type& get();

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
        set(another.data_as<data>().get());
        return *this;
    }

    template <typename value_type>
    scalar<value_type>::scalar(value_type value)
        : m_data(nullptr)
    {
        m_data = initialize<data>(value);
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator = (value_type value)
    {
        m_data->set(value);
        return *this;
    }

    template <typename value_type>
    scalar<value_type>::operator value_type () const
    {
        return value();
    }

    template <typename value_type>
    const value_type& scalar<value_type>::value() const
    {
        return m_data->get();
    }

    template <typename value_type>
    value_type& scalar<value_type>::value()
    {
        return m_data->ref();
    }

    template <typename value_type>
    void scalar<value_type>::reset()
    {
        m_data = nullptr;
        object::reset();
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
        set(value() + another.value());
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator -= (const scalar<value_type>& another)
    {
        set(value() - another.value());
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator *= (const scalar<value_type>& another)
    {
        set(value() * another.value());
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator /= (const scalar<value_type>& another)
    {
        set(value() / another.value());
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
        set(value() + another_value);
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator -= (value_type another_value)
    {
        set(value() - another_value);
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator *= (value_type another_value)
    {
        set(value() * another_value);
        return *this;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator /= (value_type another_value)
    {
        set(value() / another_value);
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
        return static_cast<bool>(m_value);
    }

    template <typename value_type>
    void scalar<value_type>::data::output(std::ostream& stream) const
    {
        stream << "scalar: " << m_value;
    }

    template <typename value_type>
    void scalar<value_type>::data::set(value_type value)
    {
        m_value = value;
    }

    template <typename value_type>
    const value_type& scalar<value_type>::data::get() const
    {
        return m_value;
    }

    template <typename value_type>
    value_type& scalar<value_type>::data::get()
    {
        return m_value;
    }
}

// Unicode signature: Владимир Керимов
