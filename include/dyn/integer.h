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

        class data;

        class out_of_range_exception;

        template <typename value_type>
        class out_of_range_exception_of;

    private:
        data* m_data;
    };

    class integer::data : public object::data
    {
    public:
        typedef object::data base;

        data(std::int64_t head = 0, std::uint64_t tail = 0);

        data(double value);
        data(float value);

        virtual object::data* move_to(void* buffer) override;
        virtual object::data* copy_to(void* buffer) override;

        virtual const char* name() const override;

        virtual bool as_bool() const override;
        virtual void output(std::ostream& stream) const override;

    private:
        std::int64_t m_head;
        std::uint64_t m_tail;
    };

    class integer::out_of_range_exception : public dyn::exception
    {
    public:
        typedef dyn::exception base;

        out_of_range_exception(double value);
        out_of_range_exception(float value);
    };

    template <typename value_type>
    class integer::out_of_range_exception_of : public integer::out_of_range_exception
    {
    public:
        typedef out_of_range_exception base;

        out_of_range_exception_of(value_type value);
    };

    template <typename value_type>
    integer::out_of_range_exception_of<value_type>::out_of_range_exception_of(value_type value)
        : base(value)
    {
    }
}

// Unicode signature: Владимир Керимов
