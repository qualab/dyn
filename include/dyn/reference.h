// copy-on-write reference to shared instance

#pragma once

#include <dyn/object.h>
#include <memory>
#include <mutex>

namespace dyn
{
    template <typename instance_type>
    class reference : public object
    {
    public:
        template <typename... argument_types>
        reference(const argument_types&... arguments);

        reference(const reference& another);

        const instance_type* operator -> () const;
        instance_type* operator -> ();

        const instance_type& operator * () const;
        instance_type& operator * ();

        const instance_type& const_instance() const;
        const instance_type& instance() const;
        instance_type& instance();

        bool is_unique() const;
        int shared_count() const;

        bool operator == (const reference& another) const;
        bool operator != (const reference& another) const;

        class data;

        class null_reference_exception;

    private:
        data* m_data;
    };

    template <typename instance_type>
    class reference<instance_type>::data : public object::data
    {
    public:
        template <typename... argument_types>
        data(const argument_types&... arguments);

        data(const data& another);

        const instance_type* get_shared() const;
        instance_type* get_unique();

        bool is_unique() const;
        int shared_count() const;
        bool equals(const data& another) const;

        virtual object::data* move_to(void* buffer) override;
        virtual object::data* copy_to(void* buffer) override;

    private:
        std::shared_ptr<instance_type> m_instance;
    };

    template <typename instance_type>
    class reference<instance_type>::null_reference_exception : public std::exception
    {
    public:
        const char* what() const override;
    };

    template <typename instance_type>
    template <typename... argument_types>
    reference<instance_type>::reference(const argument_types&... arguments)
        : m_data(initialize<data>(arguments...))
    {
        if (!m_data)
            throw null_reference_exception();
    }

    template <typename instance_type>
    reference<instance_type>::reference(const reference<instance_type>& another)
        : m_data(initialize<data>(*another.m_data))
    {
        if (!m_data)
            throw null_reference_exception();
    }

    template <typename instance_type>
    const instance_type* reference<instance_type>::operator -> () const
    {
        return m_data->get_shared();
    }

    template <typename instance_type>
    instance_type* reference<instance_type>::operator -> ()
    {
        return m_data->get_unique();
    }

    template <typename instance_type>
    const instance_type& reference<instance_type>::operator * () const
    {
        return *m_data->get_shared();
    }

    template <typename instance_type>
    instance_type& reference<instance_type>::operator * ()
    {
        return *m_data->get_unique();
    }

    template <typename instance_type>
    const instance_type& reference<instance_type>::const_instance() const
    {
        return **this;
    }

    template <typename instance_type>
    const instance_type& reference<instance_type>::instance() const
    {
        return **this;
    }

    template <typename instance_type>
    instance_type& reference<instance_type>::instance()
    {
        return **this;
    }

    template <typename instance_type>
    bool reference<instance_type>::is_unique() const
    {
        return m_data->is_unique();
    }

    template <typename instance_type>
    int reference<instance_type>::shared_count() const
    {
        return m_data->shared_count();
    }

    template <typename instance_type>
    bool reference<instance_type>::operator == (const reference<instance_type>& another) const
    {
        return m_data->equals(*another.m_data);
    }

    template <typename instance_type>
    bool reference<instance_type>::operator != (const reference<instance_type>& another) const
    {
        return !m_data->equals(*another.m_data);
    }

    template <typename instance_type>
    template <typename... argument_types>
    reference<instance_type>::data::data(const argument_types&... arguments)
        : m_instance(std::make_shared<instance_type>(arguments...))
    {
    }

    template <typename instance_type>
    reference<instance_type>::data::data(const data& another)
        : m_instance(another.m_instance)
    {
    }

    template <typename instance_type>
    const instance_type* reference<instance_type>::data::get_shared() const
    {
        return m_instance.get();
    }

    template <typename instance_type>
    instance_type* reference<instance_type>::data::get_unique()
    {
        if (!m_instance.unique())
        {
            // clone instance to get unique shared reference
            m_instance = std::make_shared<instance_type>(*m_instance);
        }
        return m_instance.get();
    }

    template <typename instance_type>
    bool reference<instance_type>::data::is_unique() const
    {
        return m_instance.unique();
    }

    template <typename instance_type>
    int reference<instance_type>::data::shared_count() const
    {
        return m_instance.use_count();
    }

    template <typename instance_type>
    bool reference<instance_type>::data::equals(const data& another) const
    {
        return m_instance == another.m_instance;
    }

    template <typename instance_type>
    object::data* reference<instance_type>::data::move_to(void* buffer)
    {
        return new(buffer) data(std::move(*this));
    }

    template <typename instance_type>
    object::data* reference<instance_type>::data::copy_to(void* buffer)
    {
        return new(buffer) data(*this);
    }

    template <typename instance_type>
    const char* reference<instance_type>::null_reference_exception::what() const
    {
        return "Null reference is not allowed to call any method or request any data.";
    }
}

// Unicode signature: Владимир Керимов
