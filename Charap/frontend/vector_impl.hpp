#pragma once

#include <backend/addition.hpp>

#include <cassert>
#include <vector>

class Vector_Impl {
public:
  // Do not allow empty initializations
  Vector_Impl() = delete;

  Vector_Impl(int const &size) : size_(size) {
    vec_.set(std::vector<double>(size));
  }

  Vector_Impl(int const &size, int const &val) : size_(size) {
    vec_.set(std::vector<double>(size, val));
  }

  Vector_Impl(Vector_Impl const &vec) : size_(vec.size()) {
    vec_ = vec.vector();
  }

public:
  Vector_Impl &operator=(Vector_Impl const &vec) {
    vec_ = vec.vector();

    return *this;
  }

public:
  ck::future<std::vector<double>> const &get() const { return vec_; }

  int const size() const { return size_; }

  ck::future<std::vector<double>> const &vector() const { return vec_; }

private:
  // Vector stored in a state-full future
  ck::future<std::vector<double>> vec_;
  const int size_;
};

inline Vector_Impl operator+(Vector_Impl const &vec1, Vector_Impl const &vec2) {
  // Step 2 check. Ensure both vector internals have same size
  assert(vec1.size() == vec2.size());

  Vector_Impl replacement{vec1.size()};

  // Fire and forget
  CProxy_add_vector::ckNew(replacement.get(), vec1.get(), vec2.get());

  return replacement;
}