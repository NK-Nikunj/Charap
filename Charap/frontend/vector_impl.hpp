#pragma once

#include <backend/addition.hpp>
#include <backend/loader.hpp>

#include <backend/garbage.hpp>

#include <cassert>
#include <memory>
#include <vector>

class Vector_Impl {
public:
  void pup(PUP::er &p) {
    p | vec_;
    p | size_;
  }

  // Do not allow empty initializations
  Vector_Impl() = delete;

  explicit Vector_Impl(int const &size) : size_(size),
  vec_(std::unique_ptr<ck::future<std::vector<double>>>{}) {
    vec_ -> set(std::vector<double>(size));
  }

  explicit Vector_Impl(int const &size, int const &val) : size_(size),
    vec_(std::unique_ptr<ck::future<std::vector<double>>>{}) {
    vec_ -> set(std::vector<double>(size, val));
  }

  Vector_Impl(Vector_Impl const &vec) : size_(vec.size()),
    vec_(std::unique_ptr<ck::future<std::vector<double>>>{}) {
    CProxy_loader::ckNew(*vec_, vec.vector());
  }

  ~Vector_Impl() {
    garbage::collect(vec_);

    assert(!vec_);
  }

public:
  Vector_Impl &operator=(Vector_Impl const &vec) {
    garbage::collect(vec_);

    vec_ = std::unique_ptr<ck::future<std::vector<double>>>{};
    CProxy_loader::ckNew(*vec_, vec.vector());

    return *this;
  }

public:

  int const size() const { return size_; }

  ck::future<std::vector<double>> const &vector() const { return *vec_; }

private:
  // Vector stored in a state-full future
  // ck::future<std::vector<double>> vec_;
  std::unique_ptr<ck::future<std::vector<double>>> vec_;
  int size_;
};

inline Vector_Impl operator+(Vector_Impl const &vec1, Vector_Impl const &vec2) {
  // Step 2 check. Ensure both vector internals have same size
  assert(vec1.size() == vec2.size());

  Vector_Impl replacement{vec1.size()};

  // Fire and forget
  CProxy_add_vector::ckNew(replacement.vector(), vec1.vector(), vec2.vector());

  return replacement;
}