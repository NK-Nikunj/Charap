#pragma once

#include <frontend/vector_impl.hpp>

#include <cassert>
#include <cstdint>
#include <type_traits>
#include <vector>

class Vector {
public:
  // Vector_Impl size can't exceed by the following value.
  const int size_ = 100000;

public:
  Vector() = delete;

  Vector(int size) {
    // Number of Vector_Impl objects required
    int num_arr = size / Vector::size_;
    // Size of the last Vector_Impl object
    int end_size = size % Vector::size_;

    vec_.reserve(num_arr + 1);

    for (int i = 0; i < num_arr; ++i)
      vec_.emplace_back(Vector::size_);

    if (end_size)
      vec_.emplace_back(end_size);
  }

  Vector(int size, int val) {
    // Number of Vector_Impl objects required
    int num_arr = size / Vector::size_;
    // Size of the last Vector_Impl object
    int end_size = size % Vector::size_;

    vec_.reserve(num_arr + 1);

    for (int i = 0; i < num_arr; ++i)
      vec_.emplace_back(Vector::size_, val);

    if (end_size)
      vec_.emplace_back(end_size, val);
  }

public:
  Vector_Impl const &operator[](int i) const { return vec_.at(i); }

  Vector_Impl &operator[](int i) { return vec_.at(i); }

public:
  int size() const { return vec_.size(); }

private:
  std::vector<Vector_Impl> vec_;
};

inline Vector operator+(Vector const &vec1, Vector const &vec2) {
  // Step 1 check. Ensure both vectors have same sizes.
  assert(vec1.size() == vec2.size());

  ckout << "size of temp vector: " << vec1.size() << endl;

  Vector temp{vec1.size()};

  for (int i = 0; i < vec1.size(); ++i)
    temp[i] = vec1[i] + vec2[i];

  return temp;
}