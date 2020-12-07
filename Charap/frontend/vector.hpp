#pragma once

#include <backend/vector_b.hpp>

#include <cstdint>
#include <type_traits>
#include <vector>

class Vector
{
public:
    // Operators allowed for vector class
    enum class operators : std::int16_t
    {
        addition
    };

    using type = Vector;

// List of all constructors
public:

    // Disallowing empty vector initializations
    Vector() = delete;

    // Copy constructor (temp object): No implicit
    // dependency required for temperory objects.
    Vector(Vector&& vec)
    {
        ckout << "Copy constructor called (temp)" << endl;
        
        ck::future<bool> f;
        f_.push_back(f);

        CProxy_vector_b proxy = vec.get_proxy();

        vec_ = CProxy_vector_b::ckNew(f, proxy);
    }

    // Copy constructor: There is an implicit 
    // dependency. Do not let vec change while
    // we assign the new vector its value from
    // vec.
    Vector(Vector& vec)
    {
        ckout << "Copy constructor called (ref)" << endl;

        ck::future<bool> f;
        f_.push_back(f);

        std::vector<ck::future<bool> > deps = vec.get_dependencies();
        CProxy_vector_b proxy = vec.get_proxy();

        // Add dependency on vector to prevent
        // its further use.
        ck::future<bool> f_rhs;
        vec.add_dependecy(f_rhs);

        vec_ = CProxy_vector_b::ckNew(f, deps, proxy, f_rhs);
    }

    // When a new vector is constructed. There are
    // no dependencies. Hence add to the pile of 
    // vectors and generate the vector.
    Vector(std::vector<double>&& vec)
    {
        ck::future<bool> f;
        f_.push_back(f);
        vec_ = CProxy_vector_b::ckNew(vec, f);
    }

    // When a new vector is constructed. There are
    // no dependencies. Hence add to the pile of 
    // vectors and generate the vector.
    Vector(std::initializer_list<double>&& list)
    {
        ck::future<bool> f;
        f_.push_back(f);
        vec_ = CProxy_vector_b::ckNew(list, f);
    }

// List of all operators and operators based constructors
public:

    Vector(Vector& vec1, Vector& vec2, operators op)
    {
        ck::future<bool> f;
        f_.push_back(f);

        if (op == operators::addition)
        {
            vec_ = CProxy_vector_b::ckNew();

            // Get dependencies for vec1 and vec2
            std::vector<ck::future<bool> > deps1 = vec1.get_dependencies();
            CProxy_vector_b proxy1 = vec1.get_proxy();

            std::vector<ck::future<bool> > deps2 = vec2.get_dependencies();
            CProxy_vector_b proxy2 = vec2.get_proxy();

            // Add dependency on vector to prevent
            // its further use.
            ck::future<bool> f_rhs1;
            vec1.add_dependecy(f_rhs1);

            ck::future<bool> f_rhs2;
            vec2.add_dependecy(f_rhs2);

            vec_.adder(f, deps1, deps2, proxy1, proxy2, f_rhs1, f_rhs2);
        }
    }

    Vector(Vector&& vec1, Vector&& vec2, operators op)
    {
        ck::future<bool> f;
        f_.push_back(f);

        if (op == operators::addition)
        {
            vec_ = CProxy_vector_b::ckNew();

            // Get dependencies for vec1 and vec2
            std::vector<ck::future<bool> > deps1 = vec1.get_dependencies();
            CProxy_vector_b proxy1 = vec1.get_proxy();

            std::vector<ck::future<bool> > deps2 = vec2.get_dependencies();
            CProxy_vector_b proxy2 = vec2.get_proxy();

            ck::future<bool> f_rhs1;
            ck::future<bool> f_rhs2;

            vec_.adder(f, deps1, deps2, proxy1, proxy2, f_rhs1, f_rhs2);
        }
    }

    Vector(Vector&& vec1, Vector& vec2, operators op)
    {
        ck::future<bool> f;
        f_.push_back(f);

        if (op == operators::addition)
        {
            vec_ = CProxy_vector_b::ckNew();

            // Get dependencies for vec1 and vec2
            std::vector<ck::future<bool> > deps1 = vec1.get_dependencies();
            CProxy_vector_b proxy1 = vec1.get_proxy();

            std::vector<ck::future<bool> > deps2 = vec2.get_dependencies();
            CProxy_vector_b proxy2 = vec2.get_proxy();

            // Add dependency on vector to prevent
            // its further use.
            ck::future<bool> f_rhs1;

            ck::future<bool> f_rhs2;
            vec2.add_dependecy(f_rhs2);

            vec_.adder(f, deps1, deps2, proxy1, proxy2, f_rhs1, f_rhs2);
        }
    }

    Vector(Vector& vec1, Vector&& vec2, operators op)
    {
        ck::future<bool> f;
        f_.push_back(f);

        if (op == operators::addition)
        {
            vec_ = CProxy_vector_b::ckNew();

            // Get dependencies for vec1 and vec2
            std::vector<ck::future<bool> > deps1 = vec1.get_dependencies();
            CProxy_vector_b proxy1 = vec1.get_proxy();

            std::vector<ck::future<bool> > deps2 = vec2.get_dependencies();
            CProxy_vector_b proxy2 = vec2.get_proxy();

            // Add dependency on vector to prevent
            // its further use.
            ck::future<bool> f_rhs1;
            vec1.add_dependecy(f_rhs1);

            ck::future<bool> f_rhs2;

            vec_.adder(f, deps1, deps2, proxy1, proxy2, f_rhs1, f_rhs2);
        }
    }

// List of all helper functions
public:
    // A helper function to add dependencies of a
    // Vector to equations where it occurs on the
    // RHS to prevent write before read.
    void add_dependecy(ck::future<bool>& f)
    {
        f_.push_back(f);
    }

    // A helper function to get all dependencies of 
    // a Vector.
    std::vector<ck::future<bool> > get_dependencies() const
    {
        return f_;
    }

    // A helper function to get access to proxy to 
    // the underneath vector
    CProxy_vector_b get_proxy() const
    {
        return vec_;
    }

    void print_vector()
    {
        ck::future<bool> f;
        vec_.print_vector(f, f_);

        f_.push_back(f);
    }

private:
    CProxy_vector_b vec_;
    std::vector<ck::future<bool> > f_;
};

inline Vector operator+(Vector& vec1, Vector& vec2)
{
    Vector temp = {vec1, vec2, Vector::operators::addition};

    return temp;
}

inline Vector operator+(Vector&& vec1, Vector& vec2)
{
    Vector temp = {vec1, vec2, Vector::operators::addition};

    return temp;
}

inline Vector operator+(Vector& vec1, Vector&& vec2)
{
    Vector temp = {vec1, vec2, Vector::operators::addition};

    return temp;
}

inline Vector operator+(Vector&& vec1, Vector&& vec2)
{
    Vector temp = {vec1, vec2, Vector::operators::addition};

    return temp;
}