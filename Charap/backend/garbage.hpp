#pragma once

#include "charm++.h"

struct garbage {
    static void collect(std::unique_ptr<ck::future<std::vector<double>>> &f) {
        futures.emplace_back(std::move(f));
    }

    static std::vector<std::unique_ptr<ck::future<std::vector<double>>>> futures;
};
