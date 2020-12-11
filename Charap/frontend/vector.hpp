#pragma once

#include <frontend/vector_impl.hpp>

#include <cassert>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <vector>

class Vector {
public:
  // Vector_Impl size can't exceed by the following value.
  const int arr_size_ = 100000;

public:
  Vector() = delete;

  Vector(Vector const& vec) : size_(vec.size()) {
    vec_.reserve(vec.length());

    for (Vector_Impl const& elem : vec.vector())
      vec_.emplace_back(elem);
  }

  explicit Vector(int const& size) : size_(size) {
    // Number of Vector_Impl objects required
    int num_arr = size / arr_size_;
    // Size of the last Vector_Impl object
    int end_size = size % arr_size_;

    vec_.reserve(num_arr + 1);

    for (int i = 0; i < num_arr; ++i)
      vec_.emplace_back(arr_size_);

    if (end_size)
      vec_.emplace_back(end_size);
  }

  explicit Vector(int const& size, int const& val) : size_(size) {
    // Number of Vector_Impl objects required
    int num_arr = size / arr_size_;
    // Size of the last Vector_Impl object
    int end_size = size % arr_size_;

    vec_.reserve(num_arr + 1);

    for (int i = 0; i < num_arr; ++i)
      vec_.emplace_back(arr_size_, val);

    if (end_size)
      vec_.emplace_back(end_size, val);
  }

public:
  Vector& operator=(Vector const& vec)
  {
    assert(size_ == vec.size());

    if (this != &vec) {
      for (int i = 0; i < vec_.size(); ++i)
        vec_[i] = vec[i];
    }

    return *this;
  }

  Vector_Impl const &operator[](int const& i) const { return vec_.at(i); }

  Vector_Impl &operator[](int const& i) { return vec_.at(i); }

public:
  const int size() const { return size_; }
  const int length() const { return vec_.size(); }
  const std::vector<Vector_Impl>&  vector() const { return vec_; }

private:
  std::vector<Vector_Impl> vec_;
  const int size_;
};

inline Vector operator+(Vector const &vec1, Vector const &vec2) {
  // Step 1 check. Ensure both vectors have same sizes.
  assert(vec1.size() == vec2.size());

  Vector temp{vec1.size()};

  for (int i = 0; i < vec1.length(); ++i) {
    temp[i] = vec1[i] + vec2[i];
  }

  return temp;
}