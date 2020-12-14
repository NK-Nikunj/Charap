#pragma once

#include <backend/operators.decl.h>

#include <vector>

class checker : public CBase_checker {
public:
    checker(ck::future<std::vector<double>> f) :
        f_(f) {}

    void check() {
        f_.get();
        ckout << "Checks out!" << endl;
    }
private:
    ck::future<std::vector<double>> f_;
};
