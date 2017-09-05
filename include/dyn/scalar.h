// dynamically typified object

#pragma once

#include <dyn/object.h>
#include <cstdint>
#include <cstddef>

namespace dyn
{
    template <typename value_type>
    class scalar : public object
    {
    public:
        scalar();

        scalar(value_type value);
        scalar& operator = (value_type value);

        operator value_type () const;

        bool operator ! () const;

        scalar(const object& another);
        scalar& operator = (const object& another);

        class data;

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

        value_type get() const;
        void set(value_type value);

    private:
        value_type m_value;
    };

    template <typename value_type>
    scalar<value_type>::scalar()
        : m_data(nullptr)
    {
        m_data = initialize(new(buffer()) data());
    }

    template <typename value_type>
    scalar<value_type>::scalar(value_type value)
        : m_data(nullptr)
    {
        m_data = initialize(new(buffer()) data(value));
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
        return m_data->get();
    }

    template <typename value_type>
    bool scalar<value_type>::operator ! () const
    {
        return !m_data->get();
    }

    template <typename value_type>
    scalar<value_type>::scalar(const object& another)
        : m_data(nullptr)
    {
        m_data = initialize(new(buffer()) data());
        *this = another;
    }

    template <typename value_type>
    scalar<value_type>& scalar<value_type>::operator = (const object& another)
    {
        const data* another_data = dynamic_cast<const data*>(another.get_data());
        if (!another_data)
            std::runtime_error("Wrong type of object to initialize as such type of scalar.");
        m_data->set(another_data->get());
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
    object::data* scalar<value_type>::data::copy_to(void* buffer)
    {
        return new(buffer) data(*this);
    }

    template <typename value_type>
    object::data* scalar<value_type>::data::move_to(void* buffer)
    {
        return new(buffer) data(std::move(*this));
    }

    template <typename value_type>
    value_type scalar<value_type>::data::get() const
    {
        return m_value;
    }

    template <typename value_type>
    void scalar<value_type>::data::set(value_type value)
    {
        m_value = value;
    }

    template<> DYN_PUBLIC object& object::operator = (std::int64_t);
    template<> DYN_PUBLIC object& object::operator = (std::int32_t);
    template<> DYN_PUBLIC object& object::operator = (std::int16_t);
    template<> DYN_PUBLIC object& object::operator = (std::int8_t);

    template<> DYN_PUBLIC object& object::operator = (std::uint64_t);
    template<> DYN_PUBLIC object& object::operator = (std::uint32_t);
    template<> DYN_PUBLIC object& object::operator = (std::uint16_t);
    template<> DYN_PUBLIC object& object::operator = (std::uint8_t);

    template<> DYN_PUBLIC object& object::operator = (double);
    template<> DYN_PUBLIC object& object::operator = (float);

    template<> DYN_PUBLIC object& object::operator = (bool);

    template<> DYN_PUBLIC object& object::operator = (char);
    template<> DYN_PUBLIC object& object::operator = (wchar_t);

    template<> DYN_PUBLIC object& object::operator = (std::nullptr_t);
}

// Unicode signature: Владимир Керимов
