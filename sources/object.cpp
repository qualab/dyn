// dynamically typified object

#include <dyn/object.h>
#include <dyn/scalar.h>
#include <dyn/reference.h>
#include <iostream>
#include <utility>
#include <string>

namespace dyn
{
    object::object()
        : m_data(nullptr)
    {
    }

    object::~object()
    {
        reset();
    }

    object::object(const object& another)
        : m_data(nullptr)
    {
        *this = another;
    }

    object::object(object&& temporary)
        : m_data(nullptr)
    {
        *this = std::move(temporary);
    }

    object& object::operator = (const object& another)
    {
        reset();
        if (another.m_data)
            m_data = another.m_data->copy_to(m_buffer);
        return *this;
    }

    object& object::operator = (object&& temporary)
    {
        reset();
        if (temporary.m_data)
            m_data = temporary.m_data->move_to(m_buffer);
        return *this;
    }

    void object::reset()
    {
        if (m_data)
        {
            m_data->~data();
            m_data = nullptr;
        }
    }

    bool object::is_null() const
    {
        return m_data == nullptr;
    }

    bool object::is_not_null() const
    {
        return !is_null();
    }

    const object::data* object::get_data() const
    {
        return m_data;
    }

    object::data* object::get_data()
    {
        return m_data;
    }

    const char* object::data::name() const
    {
        return "data";
    }

    bool object::data::as_bool() const
    {
        return true;
    }

    void object::data::output(std::ostream& stream) const
    {
        stream << "data{name='" << name() << "'}";
    }

    void object::output_data(std::ostream& stream) const
    {
        if (m_data)
            m_data->output(stream);
        else
            stream << "null";
    }

    bool object::operator ! () const
    {
        return !as_bool();
    }

    object::operator bool() const
    {
        return as_bool();
    }

    bool object::as_bool() const
    {
        return m_data ? m_data->as_bool() : false;
    }

    std::ostream& operator << (std::ostream& stream, const object& argument)
    {
        stream << "object{";
        argument.output_data(stream);
        return stream << '}';
    }

    object::exception::exception(const std::string& message)
        : base(message)
    {
    }

    object::data_size_exception::data_size_exception()
        : base("Object data size is too big for object internal buffer.")
    {
    }

    object::representation_exception::representation_exception()
        : base("Object can not be represented by the type specified.")
    {
    }

    template <> object& object::operator = (const bool& value)
    {
        initialize<scalar<bool>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::int64_t& value)
    {
        initialize<scalar<std::int64_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::int32_t& value)
    {
        initialize<scalar<std::int32_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::int16_t& value)
    {
        initialize<scalar<std::int16_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::int8_t& value)
    {
        initialize<scalar<std::int8_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::uint64_t& value)
    {
        initialize<scalar<std::uint64_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::uint32_t& value)
    {
        initialize<scalar<std::uint32_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::uint16_t& value)
    {
        initialize<scalar<std::uint16_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::uint8_t& value)
    {
        initialize<scalar<std::uint8_t>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const double& value)
    {
        initialize<scalar<double>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const float& value)
    {
        initialize<scalar<float>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const char& value)
    {
        initialize<scalar<char>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const char* const& value)
    {
        initialize<reference<std::string>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::string& value)
    {
        initialize<reference<std::string>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const wchar_t* const& value)
    {
        initialize<reference<std::wstring>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::wstring& value)
    {
        initialize<reference<std::wstring>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const char16_t* const& value)
    {
        initialize<reference<std::u16string>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::u16string& value)
    {
        initialize<reference<std::u16string>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const char32_t* const& value)
    {
        initialize<reference<std::u32string>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::u32string& value)
    {
        initialize<reference<std::u32string>::data>(value);
        return *this;
    }

    template <> object& object::operator = (const std::nullptr_t&)
    {
        reset();
        return *this;
    }

    template <> const bool& object::get<bool>() const
    {
        return data_as<scalar<bool>::data>().value();
    }

    template <> const std::int64_t& object::get<std::int64_t>() const
    {
        return data_as<scalar<std::int64_t>::data>().value();
    }

    template <> const std::int32_t& object::get<std::int32_t>() const
    {
        return data_as<scalar<std::int32_t>::data>().value();
    }

    template <> const std::int16_t& object::get<std::int16_t>() const
    {
        return data_as<scalar<std::int16_t>::data>().value();
    }

    template <> const std::int8_t& object::get<std::int8_t>() const
    {
        return data_as<scalar<std::int8_t>::data>().value();
    }

    template <> const std::uint64_t& object::get<std::uint64_t>() const
    {
        return data_as<scalar<std::uint64_t>::data>().value();
    }

    template <> const std::uint32_t& object::get<std::uint32_t>() const
    {
        return data_as<scalar<std::uint32_t>::data>().value();
    }

    template <> const std::uint16_t& object::get<std::uint16_t>() const
    {
        return data_as<scalar<std::uint16_t>::data>().value();
    }

    template <> const std::uint8_t& object::get<std::uint8_t>() const
    {
        return data_as<scalar<std::uint8_t>::data>().value();
    }

    template <> const double& object::get<double>() const
    {
        return data_as<scalar<double>::data>().value();
    }

    template <> const float& object::get<float>() const
    {
        return data_as<scalar<float>::data>().value();
    }

    template <> const char& object::get<char>() const
    {
        return data_as<scalar<char>::data>().value();
    }

    template <> const std::string& object::get<std::string>() const
    {
        return *data_as<reference<std::string>::data>().get_shared();
    }

    template <> std::string& object::get<std::string>()
    {
        return *data_as<reference<std::string>::data>().get_unique();
    }

    template <> const std::wstring& object::get<std::wstring>() const
    {
        return *data_as<reference<std::wstring>::data>().get_shared();
    }

    template <> std::wstring& object::get<std::wstring>()
    {
        return *data_as<reference<std::wstring>::data>().get_unique();
    }

    template <> const std::u16string& object::get<std::u16string>() const
    {
        return *data_as<reference<std::u16string>::data>().get_shared();
    }

    template <> std::u16string& object::get<std::u16string>()
    {
        return *data_as<reference<std::u16string>::data>().get_unique();
    }

    template <> const std::u32string& object::get<std::u32string>() const
    {
        return *data_as<reference<std::u32string>::data>().get_shared();
    }

    template <> std::u32string& object::get<std::u32string>()
    {
        return *data_as<reference<std::u32string>::data>().get_unique();
    }
}

// Unicode signature: Владимир Керимов
