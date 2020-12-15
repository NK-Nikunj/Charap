#pragma once

#include <backend/addition.hpp>
#include <backend/loader.hpp>
#include <backend/substraction.hpp>

#include <backend/checker.hpp>
#include <backend/garbage.hpp>

#include <cassert>

class Vector_Impl;
class Vector;

class Scalar
{
public:
    Scalar() = default;

    explicit Scalar(double const& s)
    {
        s_.set(s);
    }

public:
    ck::future<double>& value()
    {
        return s_;
    }
    ck::future<double> const& value() const
    {
        return s_;
    }

private:
    ck::future<double> s_;
};
