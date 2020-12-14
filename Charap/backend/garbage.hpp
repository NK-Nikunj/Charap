#pragma once

#include "charm++.h"

struct garbage {
    static void collect(ck::future<std::vector<double>> &f) {
        futures.emplace_back(f);
    }

    static std::vector<ck::future<std::vector<double>>> futures;
};
