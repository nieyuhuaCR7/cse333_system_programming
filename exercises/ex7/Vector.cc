// Copyright [2023] <Yuhua Nie, Yanxiao Sun> [legal/copyright]
// nieyuhua@uw.edu, ysun01@uw.edu
#include <cmath>
#include "Vector.h"

namespace vector333 {

    // default constructor
    Vector::Vector() {
        data_ = new float[3];
        data_[0] = 0;
        data_[1] = 0;
        data_[2] = 0;
    }

    // general constructor
    Vector::Vector(const float x, const float y, const float z) {
        data_ = new float[3];
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
    }

    // copy constructor
    Vector::Vector(const Vector& copyme) {
        data_ = new float[3];
        data_[0] = copyme.get_x();
        data_[1] = copyme.get_y();
        data_[2] = copyme.get_z();
    }

    // destrcutor
    Vector::~Vector() {
        delete[] data_;
    } 

    // getters
    float Vector::get_x() const { return data_[0]; }
    float Vector::get_y() const { return data_[1]; }
    float Vector::get_z() const { return data_[2]; }

    // assignment operator
    Vector& Vector::operator=(const Vector& rhs) {
        if (this != &rhs) {
            data_[0] = rhs.get_x();
            data_[1] = rhs.get_y();
            data_[2] = rhs.get_z();
        }
        return *this;
    }

    // add operator
    Vector& Vector::operator+=(const Vector& rhs) {
        data_[0] += rhs.get_x();
        data_[1] += rhs.get_y();
        data_[2] += rhs.get_z();
        return *this;
    }

    // subtract operator
    Vector& Vector::operator-=(const Vector& rhs) {
        data_[0] -= rhs.get_x();
        data_[1] -= rhs.get_y();
        data_[2] -= rhs.get_z();
        return *this;
    }

    // implementation of vector addition
    Vector operator+(const Vector u, const Vector v) {
        return Vector(u.get_x() + v.get_x(), u.get_y() + v.get_y(), u.get_z() + v.get_z());
    }

    // implementation of vector subtraction
    Vector operator-(const Vector u, const Vector v) {
        return Vector(u.get_x() - v.get_x(), u.get_y() - v.get_y(), u.get_z() - v.get_z());
    }

    // implementation of vector multiplication
    Vector operator*(const Vector u, const float number) {
        return Vector(number * u.get_x(), number * u.get_y(), number * u.get_z());
    }

    Vector operator*(const float number, const Vector u) {
        return Vector(number * u.get_x(), number * u.get_y(), number * u.get_z());
    }

    // dot product operator
    float operator*(const Vector& lhs, const Vector& rhs) {
        float product = lhs.get_x() * rhs.get_x()
            + lhs.get_y() * rhs.get_y() + lhs.get_z() * rhs.get_z();
        return product;
    }

    std::ostream& operator<<(std::ostream& os, const Vector& u) {
        os << "(" << u.get_x() << "," << u.get_y() << "," << u.get_z() << ")";
        return os;
    }

}  // namespace vector
