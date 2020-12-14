#pragma once

#include <backend/operators.decl.h>

#include <vector>

class loader : public CBase_loader {
public:
    loader() = default;

    void load(ck::future<std::vector<double>> f1, ck::future<std::vector<double>> f2) {
        std::vector<double> vec = f2.get();
        f1.set(vec);
    }
};