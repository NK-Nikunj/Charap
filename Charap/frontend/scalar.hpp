#pragma once

#include <backend/addition.hpp>
#include <backend/loader.hpp>
#include <backend/substraction.hpp>

#include <backend/garbage.hpp>

#include <cassert>

template <typename _Tp>
class Scalar
{
    static_assert((std::is_integral<_Tp>::value ||
                          std::is_floating_point<_Tp>::value),
            "aum::Vector does not work with non-integral types or non-floating "
            "point types.");

        static_assert(
            std::is_same<typename std::remove_cv<_Tp>::type, _Tp>::value,
            "aum::Vector must be a non-const, non-volatile value_type");

    using value_t = _Tp;
    using CkFuture_t = ck::future<value_t>;

public:

    using value_type = value_t;

    Scalar() = default;

    explicit Scalar(value_t const& s)
    {
        s_.set(s);
    }

public:
    CkFuture_t& value()
    {
        return s_;
    }
    CkFuture_t const& value() const
    {
        return s_;
    }

private:
    CkFuture_t s_;
};
