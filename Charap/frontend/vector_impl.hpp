#pragma once

#include <backend/addition.hpp>
#include <backend/garbage.hpp>
#include <backend/loader.hpp>
#include <backend/reducer.hpp>
#include <backend/substraction.hpp>

#include <frontend/scalar.hpp>

#include <util/is_compatible.hpp>
#include <util/result_type.hpp>

#include <cassert>
#include <memory>
#include <vector>

namespace aum {

    // Main implementation of smaller vector units
    template <typename _Tp>
    class Vector_Impl
    {
        static_assert((std::is_integral<_Tp>::value ||
                          std::is_floating_point<_Tp>::value),
            "aum::Vector_Impl does not work with non-integral types or "
            "non-floating point types.");

        static_assert(
            std::is_same<typename std::remove_cv<_Tp>::type, _Tp>::value,
            "aum::Vector_Impl must be a non-const, non-volatile value_type");

        using vector_t = std::vector<_Tp>;
        using CkFuture_t = ck::future<vector_t>;

    public:
        using value_type = _Tp;

        void pup(PUP::er& p)
        {
            p | vec_;
            p | size_;
        }

        // Do not allow empty initializations
        Vector_Impl() = delete;

        explicit Vector_Impl(int const& size)
          : size_(size)
        {
            vec_.set(vector_t(size));
        }

        explicit Vector_Impl(int const& size, int const& val)
          : size_(size)
        {
            vec_.set(vector_t(size, val));
        }

        Vector_Impl(Vector_Impl const& vec)
          : size_(vec.size())
        {
            CProxy_loader l = CProxy_loader::ckNew();
            l.load(vec_, vec.vector());
        }

        ~Vector_Impl()
        {
            garbage::collect(vec_);
        }

    public:
        Vector_Impl& operator=(Vector_Impl const& vec)
        {
            garbage::collect(vec_);

            vec_ = CkFuture_t{};
            CProxy_loader l = CProxy_loader::ckNew();
            l.load(vec_, vec.vector());

            return *this;
        }

    public:
        int const size() const
        {
            return size_;
        }

        CkFuture_t const& vector() const
        {
            return vec_;
        }

    private:
        // Vector stored in a state-full future
        CkFuture_t vec_;
        int size_;
    };

    template <typename _Tp1, typename _Tp2,
        typename Result = typename aum::util::result_type<_Tp1, _Tp2>::type,
        typename = typename aum::util::is_compatible<_Tp1, _Tp2>::type>
    Vector_Impl<Result> operator+(
        Vector_Impl<_Tp1> const& vec1, Vector_Impl<_Tp2> const& vec2)
    {
        // Step 2 check. Ensure both vector internals have same size
        assert(vec1.size() == vec2.size());

        Vector_Impl<Result> replacement{vec1.size()};

        // Fire and forget
        // CProxy_add_vector adder = CProxy_add_vector::ckNew();
        // adder.add(replacement.vector(), vec1.vector(), vec2.vector());

        return replacement;
    }

    template <typename _Tp1, typename _Tp2,
        typename Result = typename aum::util::result_type<_Tp1, _Tp2>::type,
        typename = typename aum::util::is_compatible<_Tp1, _Tp2>::type>
    Vector_Impl<Result> operator-(
        Vector_Impl<_Tp1> const& vec1, Vector_Impl<_Tp2> const& vec2)
    {
        // Step 2 check. Ensure both vector internals have same size
        assert(vec1.size() == vec2.size());

        Vector_Impl<Result> replacement{vec1.size()};

        // Fire and forget
        // CProxy_sub_vector sub = CProxy_sub_vector::ckNew();
        // sub.subtract(replacement.vector(), vec1.vector(), vec2.vector());

        return replacement;
    }
}    // namespace aum
