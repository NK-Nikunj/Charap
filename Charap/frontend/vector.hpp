#pragma once

#include <frontend/scalar.hpp>
#include <frontend/vector_impl.hpp>

#include <util/is_compatible.hpp>
#include <util/result_type.hpp>

#include <boost/range/algorithm_ext.hpp>

#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

namespace aum {

    // Entry point for any Vector based storage and computation
    template <typename _Tp>
    class Vector
    {
        static_assert((std::is_integral<_Tp>::value ||
                          std::is_floating_point<_Tp>::value),
            "aum::Vector does not work with non-integral types or non-floating "
            "point types.");

        static_assert(
            std::is_same<typename std::remove_cv<_Tp>::type, _Tp>::value,
            "aum::Vector must be a non-const, non-volatile value_type");

        using Vector_Impl_t = aum::Vector_Impl<_Tp>;

    public:
        using value_type = _Tp;

        Vector() = delete;

        Vector(Vector const& vec)
          : size_(vec.size())
          , is_transposed_(false)
        {
            vec_.reserve(vec.length());

            for (Vector_Impl_t const& elem : vec.vector())
                vec_.emplace_back(elem);
        }

        explicit Vector(int const& size)
          : size_(size)
          , is_transposed_(false)
        {
            // Number of Vector_Impl objects required
            const int num_arr = size / arr_size_;
            // Size of the last Vector_Impl object
            const int end_size = size % arr_size_;

            vec_.reserve(num_arr + 1);

            for (int i = 0; i < num_arr; ++i)
                vec_.emplace_back(arr_size_);

            if (end_size)
                vec_.emplace_back(end_size);
        }

        explicit Vector(int const& size, int const& val)
          : size_(size)
          , is_transposed_(false)
        {
            // Number of Vector_Impl objects required
            const int num_arr = size / arr_size_;
            // Size of the last Vector_Impl object
            const int end_size = size % arr_size_;

            vec_.reserve(num_arr + 1);

            for (int i = 0; i < num_arr; ++i)
                vec_.emplace_back(arr_size_, val);

            if (end_size)
                vec_.emplace_back(end_size, val);
        }

    public:
        Vector& operator=(Vector const& vec)
        {
            assert(size_ == vec.size());

            if (this != &vec)
            {
                for (int i = 0; i < vec_.size(); ++i)
                    vec_[i] = vec[i];
            }

            return *this;
        }

        Vector_Impl_t const& operator[](int const& i) const
        {
            return vec_.at(i);
        }

        Vector_Impl_t& operator[](int const& i)
        {
            return vec_.at(i);
        }

        Vector& transpose()
        {
            is_transposed_ = !is_transposed_;

            return *this;
        }

    public:
        int size() const
        {
            return size_;
        }
        int length() const
        {
            return vec_.size();
        }
        const std::vector<Vector_Impl_t>& vector() const
        {
            return vec_;
        }
        std::vector<Vector_Impl_t>& vector()
        {
            return vec_;
        }
        bool is_transposed() const
        {
            return is_transposed_;
        }

    private:
        std::vector<Vector_Impl_t> vec_;
        const int size_;

        bool is_transposed_;

        // Vector_Impl size can't exceed by the following value.
        const int arr_size_ = 100000;
    };

    template <typename _Tp1, typename _Tp2,
        typename Result = typename aum::util::result_type<_Tp1, _Tp2>::type,
        typename = typename aum::util::is_compatible<_Tp1, _Tp2>::type>
    Vector<Result> operator+(Vector<_Tp1> const& vec1, Vector<_Tp2> const& vec2)
    {
        // Step 1 check. Ensure both vectors have same sizes.
        assert(vec1.size() == vec2.size());

        Vector<Result> temp{vec1.size()};

        for (int i = 0; i < vec1.length(); ++i)
        {
            temp[i] = vec1[i] + vec2[i];
        }

        return temp;
    }

    template <typename _Tp1, typename _Tp2,
        typename Result = typename aum::util::result_type<_Tp1, _Tp2>::type,
        typename = typename aum::util::is_compatible<_Tp1, _Tp2>::type>
    Vector<Result> operator-(Vector<_Tp1> const& vec1, Vector<_Tp2> const& vec2)
    {
        // Step 1 check. Ensure both vectors have same sizes and 2nd is transposed.
        assert(vec1.size() == vec2.size());

        Vector<Result> temp{vec1.size()};

        for (int i = 0; i < vec1.length(); ++i)
        {
            temp[i] = vec1[i] - vec2[i];
        }

        return temp;
    }

    template <typename _Tp1, typename _Tp2,
        typename Result = typename aum::util::result_type<_Tp1, _Tp2>::type,
        typename = typename aum::util::is_compatible<_Tp1, _Tp2>::type>
    Vector<Result> operator*(Vector<_Tp1> const& vec1, Vector<_Tp2> const& vec2)
    {
        // Step 1 check. Ensure both vectors have same sizes.
        assert((vec1.size() == vec2.size()) && vec2.is_transposed());

        Vector<Result> temp{1};

        // CProxy_reducer reducer =
        //     CProxy_reducer::ckNew(temp[0].vector(), vec1.size());

        // for (int i = 0; i < vec1.length(); ++i)
        // {
        //     reducer[i].mul_then_add(vec1[i].vector(), vec2[i].vector());
        // }

        // int i = 0;
        // boost::range::for_each(vec1, vec2, [&reducer, &i](Vector_Impl const& vec1, Vector_Impl const& vec2) {
        //   reducer[i++].mul_then_add(vec1.vector(), vec2.vector());
        // });

        return temp;
    }

    template <typename _Tp1, typename _Tp2,
        typename Result = typename aum::util::result_type<_Tp1, _Tp2>::type,
        typename = typename aum::util::is_compatible<_Tp1, _Tp2>::type>
    Scalar<Result> dot(Vector<_Tp1> const& vec1, Vector<_Tp2> const& vec2)
    {
        // Step 1 check. Ensure both vectors have same sizes.
        assert((vec1.size() == vec2.size()) && vec2.is_transposed());

        Scalar<Result> temp{};

        // CProxy_reducer reducer =
        //     CProxy_reducer::ckNew(temp.value(), vec1.size());

        // for (int i = 0; i < vec1.length(); ++i)
        // {
        //     reducer[i].mul_then_add(vec1[i].vector(), vec2[i].vector());
        // }

        // boost::range::for_each(vec1, vec2, [&reducer, &i](Vector_Impl const& vec1, Vector_Impl const& vec2) {
        //   reducer[i++].mul_then_add(vec1.vector(), vec2.vector());
        // });

        return temp;
    }
}    // namespace aum
