#pragma once

#include <backend/operators.decl.h>

#include <vector>

class sub_vector : public CBase_sub_vector
{
public:
    sub_vector() {}

    void subtract(ck::future<std::vector<double>> f1,
        ck::future<std::vector<double>> f2, ck::future<std::vector<double>> f3)
    {
        std::vector<double> vec2 = f2.get();
        std::vector<double> vec3 = f3.get();

        std::vector<double> vec1;
        vec1.reserve(vec2.size());

        for (int i = 0; i < vec2.size(); ++i)
            vec1.emplace_back(vec2.at(i) - vec3.at(i));

        f1.set(vec1);
    }
};