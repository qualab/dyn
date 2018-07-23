// Instrumentary for type casts up through inheritance hierarchy tree

#pragma once

#include <cstdint>

namespace dyn
{
    // specification for base classes required to stop template recursion
    // where check is without request to base class as follows

    template <typename derived_type>
    struct is_class
    {
        template <typename base_type>
        static bool of()
        {
            return derived_type::class_name == base_type::class_name
                || class_is<derived_type::base>::of<base_type>();
        }
    };

    // to use object of class instead of its class

    template <typename derived_type>
    is_class<derived_type> is_instance(const derived_type&)
    {
        return is_class<derived_type>();
    }

    // helpful type definitions

    typedef std::int64_t int64;
    typedef std::int32_t int32;
    typedef std::int16_t int16;
    typedef std::int8_t  int8;

    typedef std::uint64_t uint64;
    typedef std::uint32_t uint32;
    typedef std::uint16_t uint16;
    typedef std::uint8_t  uint8;
}

// Unicode signature: Владимир Керимов
