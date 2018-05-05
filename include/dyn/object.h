// dynamically typified object

#pragma once

#include <dyn/public.h>
#include <dyn/exception.h>
#include <cstddef>
#include <cstdint>

#ifndef DYN_OBJECT_MAX_DATA_SIZE
// Class object uses internal memory block for its data
// Memory for virtual table x64 pointer and 4 x64 fields
// It is enough for decimal, vectors and quaternions
// For matrices use reference type with shared instance
#define DYN_OBJECT_MAX_DATA_SIZE 40
#endif

namespace dyn
{
    class DYN_PUBLIC object
    {
    public:
        object();
        virtual ~object();

        object(const object& another);
        object(object&& temporary);

        object& operator = (const object& another);
        object& operator = (object&& temporary);

        bool is_null() const;
        bool is_not_null() const;

        template <typename value_type>
        object(const value_type& value);

        template <typename value_type>
        object& operator = (const value_type& value);
 
        class data;

		const data* get_data() const;
		data* get_data();

		template <typename derived_data_type>
		const derived_data_type& data_as() const;

		template <typename derived_data_type>
		derived_data_type& data_as();

		virtual void output_data(std::ostream& stream) const;

        bool operator ! () const;
        operator bool() const;

        template <typename value_type>
        const value_type& get() const;

        template <typename value_type>
        value_type& get();

        static const size_t max_data_size = DYN_OBJECT_MAX_DATA_SIZE;

        class exception;
        class data_size_exception;
        class representation_exception;

        template <typename derived_data_type>
        class data_size_exception_of;

        template <typename derived_data_type>
        class representation_exception_of;

    protected:
        template <typename derived_data_type, typename... arg_list>
        derived_data_type* initialize(arg_list... arg);

        virtual void reset();
        virtual bool as_bool() const;

    private:
        char m_buffer[max_data_size];
        data* m_data;
    };

    DYN_PUBLIC std::ostream& operator << (std::ostream& stream, const object& argument);

    class DYN_PUBLIC object::data
    {
    public:
        data() { }
        virtual ~data() { }

        virtual data* move_to(void*) = 0;
        virtual data* copy_to(void*) = 0;

        virtual const char* name() const;

        virtual bool as_bool() const;
        virtual void output(std::ostream& stream) const;

        static const size_t max_fields_size = max_data_size - sizeof(void*);
    };

    class DYN_PUBLIC object::exception : public dyn::exception
    {
    public:
        typedef dyn::exception base;
        exception(const std::string& message);
    };

    class DYN_PUBLIC object::data_size_exception : public object::exception
    {
    public:
        typedef object::exception base;
        data_size_exception();
    };
 
    class DYN_PUBLIC object::representation_exception : public object::exception
    {
    public:
        typedef object::exception base;
        representation_exception();
    };

    template <typename derived_data>
    class object::data_size_exception_of : public object::data_size_exception
    {
    public:
        typedef object::data_size_exception base;
    };

    template <typename value_type>
    class object::representation_exception_of : public object::representation_exception
    {
    public:
        typedef object::representation_exception base;
    };

    template <typename value_type>
    object::object(const value_type& value)
        : m_data(nullptr)
    {
        *this = value;
    }

    template <typename value_type>
    object& object::operator = (const value_type& value)
    {
        static_assert(false, "Cannot assign value of this type to object. Implement template specialization to accept such assignment.");
    }

    template <typename value_type>
    const value_type& object::get() const
    {
        static_assert(false, "Cannot represent object as specified type. Implement template specialization to accept such representation.");
    }

    template <typename value_type>
    value_type& object::get()
    {
        return const_cast<value_type&>(static_cast<const object*>(this)->get<value_type>());
    }

    template <typename derived_data_type, typename... arg_list>
    derived_data_type* object::initialize(arg_list... arg)
    {
        derived_data_type* result = nullptr;
        reset();
        if (sizeof(derived_data_type) > max_data_size)
            throw data_size_exception_of<derived_data_type>();
        m_data = result = new(m_buffer) derived_data_type(arg...);
        return result;
    }

    template <typename derived_data_type>
    const derived_data_type& object::data_as() const
    {
        const derived_data_type* derived_data = dynamic_cast<const derived_data_type*>(m_data);
        if (!derived_data)
            throw representation_exception_of<derived_data_type>();
        return *derived_data;
    }

    template <typename derived_data_type>
    derived_data_type& object::data_as()
    {
        return const_cast<derived_data_type&>(static_cast<const object*>(this)->data_as<derived_data_type>());
    }

    template<> DYN_PUBLIC object& object::operator = (const bool& value);

    template<> DYN_PUBLIC object& object::operator = (const std::int64_t& value);
    template<> DYN_PUBLIC object& object::operator = (const std::int32_t& value);
    template<> DYN_PUBLIC object& object::operator = (const std::int16_t& value);
    template<> DYN_PUBLIC object& object::operator = (const std::int8_t& value);

    template<> DYN_PUBLIC object& object::operator = (const std::uint64_t& value);
    template<> DYN_PUBLIC object& object::operator = (const std::uint32_t& value);
    template<> DYN_PUBLIC object& object::operator = (const std::uint16_t& value);
    template<> DYN_PUBLIC object& object::operator = (const std::uint8_t& value);

    template<> DYN_PUBLIC object& object::operator = (const double& value);
    template<> DYN_PUBLIC object& object::operator = (const float& value);

    template<> DYN_PUBLIC object& object::operator = (const char& value);

    template<> DYN_PUBLIC object& object::operator = (const char* const& value);
    template<> DYN_PUBLIC object& object::operator = (const std::string& value);

    template<> DYN_PUBLIC object& object::operator = (const wchar_t* const& value);
    template<> DYN_PUBLIC object& object::operator = (const std::wstring& value);

    template<> DYN_PUBLIC object& object::operator = (const char16_t* const& value);
    template<> DYN_PUBLIC object& object::operator = (const std::u16string& value);

    template<> DYN_PUBLIC object& object::operator = (const char32_t* const& value);
    template<> DYN_PUBLIC object& object::operator = (const std::u32string& value);

    template<> DYN_PUBLIC object& object::operator = (const std::nullptr_t&);

    template<> DYN_PUBLIC const bool& object::get<bool>() const;

    template<> DYN_PUBLIC const std::int64_t& object::get<std::int64_t>() const;
    template<> DYN_PUBLIC const std::int32_t& object::get<std::int32_t>() const;
    template<> DYN_PUBLIC const std::int16_t& object::get<std::int16_t>() const;
    template<> DYN_PUBLIC const std::int8_t& object::get<std::int8_t>() const;

    template<> DYN_PUBLIC const std::uint64_t& object::get<std::uint64_t>() const;
    template<> DYN_PUBLIC const std::uint32_t& object::get<std::uint32_t>() const;
    template<> DYN_PUBLIC const std::uint16_t& object::get<std::uint16_t>() const;
    template<> DYN_PUBLIC const std::uint8_t& object::get<std::uint8_t>() const;

    template<> DYN_PUBLIC const double& object::get<double>() const;
    template<> DYN_PUBLIC const float& object::get<float>() const;

    template<> DYN_PUBLIC const char& object::get<char>() const;

    template<> DYN_PUBLIC const std::string& object::get<std::string>() const;
    template<> DYN_PUBLIC std::string& object::get<std::string>();

    template<> DYN_PUBLIC const std::wstring& object::get<std::wstring>() const;
    template<> DYN_PUBLIC std::wstring& object::get<std::wstring>();

    template<> DYN_PUBLIC const std::u16string& object::get<std::u16string>() const;
    template<> DYN_PUBLIC std::u16string& object::get<std::u16string>();

    template<> DYN_PUBLIC const std::u32string& object::get<std::u32string>() const;
    template<> DYN_PUBLIC std::u32string& object::get<std::u32string>();
}

// Unicode signature: Владимир Керимов
