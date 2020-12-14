#pragma once

#include <backend/addition.hpp>
#include <backend/loader.hpp>
#include <backend/substraction.hpp>

#include <backend/garbage.hpp>
#include <backend/checker.hpp>

#include <cassert>

class Vector_Impl;
class Vector;

class Scalar {
public:
    // Do not allow empty initializations
    Scalar() = delete;

    explicit Scalar(double const& s) { s_.set(s); }

private:
    ck::future<double> s_;
};
