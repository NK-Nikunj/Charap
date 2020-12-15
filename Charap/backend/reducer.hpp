#pragma once

#include <backend/operators.decl.h>

#include <boost/range/algorithm_ext.hpp>
#include <boost/variant.hpp>

#include <vector>

class reducer : public CBase_reducer
{
public:
    struct visitor : public boost::static_visitor<void>
    {
        visitor() = default;
        visitor(double val)
          : val_(val)
        {
        }

        void operator()(ck::future<double>& f)
        {
            f.set(val_);
        }
        void operator()(ck::future<std::vector<double>>& f)
        {
            f.set(std::vector<double>{val_});
        }

        double val_;
    };

public:
    reducer() = default;
    reducer(ck::future<double> f)
      : f_(f)
    {
    }
    reducer(ck::future<std::vector<double>> f)
      : f_(f)
    {
    }

    void mul_then_add(
        ck::future<std::vector<double>> f1, ck::future<std::vector<double>> f2)
    {
        std::vector<double> vec1 = f1.get();
        std::vector<double> vec2 = f2.get();

        double res = 0.;
        boost::range::for_each(
            vec1, vec2, [&res](double d1, double d2) { res += (d1 + d2); });

        CkCallback cb(CkReductionTarget(reducer, store), thisProxy);
        contribute(sizeof(int), &res, CkReduction::sum_double, cb);
    }

    void store(double val)
    {
        visitor visit{val};
        boost::apply_visitor(visit, f_);
    }

private:
    boost::variant<ck::future<double>, ck::future<std::vector<double>>> f_;
};
