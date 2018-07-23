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

        template <typename derived_type>
        bool is() const;

        template <typename derived_type>
        bool is_not() const;

        template <typename derived_type>
        derived_type& as();

        template <typename derived_type>
        const derived_type& as() const;

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

		virtual void output(std::ostream& stream) const;
		virtual void output_data(std::ostream& stream) const;

        bool operator ! () const;
        operator bool() const;

        template <typename value_type>
        const value_type& get() const;

        template <typename value_type>
        value_type& get();

        static const size_t max_data_size = DYN_OBJECT_MAX_DATA_SIZE;

        class exception;

        static const char* const class_name;
        virtual const char* const get_class_name() const;

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

        template <typename derived_data_type>
        bool is() const;

        template <typename derived_data_type>
        bool is_not() const;

        template <typename derived_data_type>
		derived_data_type& as();

		template <typename derived_data_type>
		const derived_data_type& as() const;

        virtual bool as_bool() const;
        virtual void output(std::ostream& stream) const = 0;

        static const char* const class_name;
        virtual const char* const get_class_name() const;
    };

	DYN_PUBLIC std::ostream& operator << (std::ostream& stream, const object::data& argument);

    class object::exception : public dyn::exception
    {
    public:
        typedef dyn::exception base;

        explicit exception(const std::string& message);

        static const char* const class_name;
        virtual const char* const get_class_name() const;
    };

    // object base class "is_class" template specification

    template <>
    struct is_class<object>
    {
        template <typename base_type>
        static bool of()
        {
            return object::class_name == base_type::class_name;
        }
    };

    // object data base class "is_class" template specification

    template <>
    struct is_class<object::data>
    {
        template <typename base_type>
        static bool of()
        {
            return object::data::class_name == base_type::class_name;
        }
    };

    // implementation of template methods

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
		static_assert(sizeof(derived_data_type) <= max_data_size,
			"Size of derived data is too big to inplace it into internal object buffer.");
		derived_data_type* result = nullptr;
        reset();
        m_data = result = new(m_buffer) derived_data_type(arg...);
        return result;
    }

    template <typename derived_data_type>
    const derived_data_type& object::data_as() const
    {
        if (!m_data)
            throw typecast_exception("Unable to cast data of null object to any data type.");
        return typecast_to<derived_data_type>::from(*m_data);
    }

    template <typename derived_data_type>
    derived_data_type& object::data_as()
    {
        return const_cast<derived_data_type&>(
            static_cast<const object*>(this)->data_as<derived_data_type>()
        );
    }

    template <typename derived_type>
    bool object::is() const
    {
        return object::is_instance(*this).of<derived_type>();
    }

    template <typename derived_type>
    bool object::is_not() const
    {
        return !is<derived_type>();
    }

    template <typename derived_type>
    derived_type& object::as()
    {
        return typecast_to<derived_type>::from(*this);
    }

    template <typename derived_type>
    const derived_type& object::as() const
    {
        return typecast_to<derived_type>::from(*this);
    }

    template <typename derived_type>
	bool object::data::is() const
	{
        return is_instance(*this).of<derived_type>();
	}

    template <typename derived_type>
    bool object::data::is_not() const
    {
        return !is<derived_type>();
    }

    template <typename derived_type>
	const derived_type& object::data::as() const
	{
		return typecast_to<derived_type>::from(*this);
	}

	template <typename derived_type>
	derived_type& object::data::as()
	{
        return typecast_to<derived_type>::from(*this);
    }

	template<> DYN_PUBLIC object& object::operator = (const bool& value);

    template<> DYN_PUBLIC object& object::operator = (const int64& value);
    template<> DYN_PUBLIC object& object::operator = (const int32& value);
    template<> DYN_PUBLIC object& object::operator = (const int16& value);
    template<> DYN_PUBLIC object& object::operator = (const int8& value);

    template<> DYN_PUBLIC object& object::operator = (const uint64& value);
    template<> DYN_PUBLIC object& object::operator = (const uint32& value);
    template<> DYN_PUBLIC object& object::operator = (const uint16& value);
    template<> DYN_PUBLIC object& object::operator = (const uint8& value);

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

    template<> DYN_PUBLIC const int64& object::get<int64>() const;
    template<> DYN_PUBLIC const int32& object::get<int32>() const;
    template<> DYN_PUBLIC const int16& object::get<int16>() const;
    template<> DYN_PUBLIC const int8&  object::get<int8>() const;

    template<> DYN_PUBLIC const uint64& object::get<uint64>() const;
    template<> DYN_PUBLIC const uint32& object::get<uint32>() const;
    template<> DYN_PUBLIC const uint16& object::get<uint16>() const;
    template<> DYN_PUBLIC const uint8&  object::get<uint8>() const;

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
