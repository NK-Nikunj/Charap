#pragma once

#include <backend/array_t.decl.h>

#include <vector>

class vector_b : public CBase_vector_b
{
public:
    vector_b() {}

    vector_b(std::vector<double> vec, ck::future<bool> f)
    {
        vec_ = std::move(vec);
        f.set(true);
    }

    vector_b(ck::future<bool> f, CProxy_vector_b proxy)
    {
        ck::future<std::vector<double> > f_;
        proxy.get_vector(f_);

        vec_ = f_.get();

        f.set(true);
    }

    vector_b(ck::future<bool> f, std::vector<ck::future<bool> > deps,
            CProxy_vector_b proxy, ck::future<bool> f_rhs)
    {
        // Wait until any prior compute remains of the copy-ing vector
        for (auto& dep : deps)
            dep.get();

        ck::future<std::vector<double> > f_;
        proxy.get_vector(f_);

        vec_ = f_.get();

        f.set(true);
        f_rhs.set(true);
    }

    void adder(ck::future<bool> f, std::vector<ck::future<bool> > deps1,
             std::vector<ck::future<bool> > deps2, CProxy_vector_b proxy1,
             CProxy_vector_b proxy2, ck::future<bool> f_rhs1, ck::future<bool> f_rhs2)
    {
        // Wait until any prior compute remains of the copy-ing vector
        for (auto& dep1: deps1)
            dep1.get();
        
        for (auto& dep2: deps2)
            dep2.get();
        
        ck::future<std::vector<double> > f1;
        ck::future<std::vector<double> > f2;

        proxy1.get_vector(f1);
        proxy2.get_vector(f2);

        std::vector<double> vec1 = std::move(f1.get());
        std::vector<double> vec2 = std::move(f2.get());

        f_rhs1.set(true);
        f_rhs2.set(true);

        if (vec1.size() != vec2.size())
            ckout << "Vector size mismatch!" << endl;
        else
        {
            vec_.resize(vec1.size());
            std::transform(vec1.begin(), vec1.end(), vec2.begin(),
                    vec_.begin(), std::plus<double>());            
        }

        f.set(true);
    }

    void get_vector(ck::future<std::vector<double> > f)
    {
        f.set(vec_);
    }

    void print_vector(ck::future<bool> f, std::vector<ck::future<bool> > f_)
    {
        // Wait until previous compute is done
        for (auto& f__ : f_)
            f__.get();

        ckout << "Contents of vector: ";
        for (double const& elem : vec_)
            ckout << elem << ",";
        ckout << endl;

        f.set(true);
    }

private:
    std::vector<double> vec_;
};
