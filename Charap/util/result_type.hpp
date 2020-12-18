#pragma once

#include <type_traits>

namespace aum { namespace util {

    template <typename _Tp1, typename _Tp2>
    struct result_type
    {
        using type =
            typename std::conditional<(std::numeric_limits<_Tp1>::max() >
                                          std::numeric_limits<_Tp2>::max()),
                _Tp1, _Tp2>::type;
    };

}}    // namespace aum::util
