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
    class object;
    template <typename> class scalar;
}

// Unicode signature: Владимир Керимов
