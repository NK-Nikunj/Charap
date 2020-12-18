#pragma once

#include <backend/operators.decl.h>

#include <vector>

class add_vector : public CBase_add_vector
{
public:
    add_vector() {}

    template <typename _Tp1, typename _Tp2, typename _Tp3>
    void add(ck::future<std::vector<_Tp1>> f1, ck::future<std::vector<_Tp2>> f2,
        ck::future<std::vector<_Tp3>> f3)
    {
        std::vector<_Tp2> vec2 = f2.get();
        std::vector<_Tp3> vec3 = f3.get();

        std::vector<_Tp1> vec1;
        vec1.reserve(vec2.size());

        for (int i = 0; i < vec2.size(); ++i)
            vec1.emplace_back(vec2.at(i) + vec3.at(i));

        f1.set(vec1);
    }
};