// dynamic typification library declarations

#pragma once

#if !defined(_WIN32) || defined(DYN_STATIC)
#   define DYN_PUBLIC
#elif defined(DYN_EXPORTS)
#   define DYN_PUBLIC __declspec(dllexport)
#else
#   define DYN_PUBLIC __declspec(dllimport)
#endif 

namespace dyn
{
    // dynamic typified object
    class object;

    // scalar container with in-place data
    template<typename> class scalar;

    // reference container with copy-on-write model
    template<typename> class reference;

    // base exception class
    class exception;
}

// Unicode signature: Владимир Керимов
