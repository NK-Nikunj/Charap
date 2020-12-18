#pragma once

#include <type_traits>

namespace aum { namespace util {

    template <typename _Tp1, typename _Tp2, typename Enable = void>
    struct is_compatible
    {
    };

    template <typename _Tp1, typename _Tp2>
    struct is_compatible<_Tp1, _Tp2,
        typename std::enable_if<((std::is_floating_point<_Tp1>::value &&
                                     std::is_floating_point<_Tp2>::value) ||
            (std::is_integral<_Tp1>::value &&
                std::is_integral<_Tp2>::value))>::type> : std::true_type
    {
    };

}}    // namespace aum::util
