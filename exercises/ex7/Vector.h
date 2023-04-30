// Copyright [2023] <Yuhua Nie, Yanxiao Sun> [legal/copyright]
// nieyuhua@uw.edu, ysun01@uw.edu
#include <iostream>

#ifndef VECTOR_H_
#define VECTOR_H_

namespace vector333 {
class Vector {
 public:
  Vector();  // default constructor
  Vector(const float x, const float y, const float z);  // general constructor
  Vector(const Vector& copyme);  // copy constructor
  ~Vector();  // destructor

  // float get_x() const;  // inline member function
  // float get_y() const;  // inline member function
  // float get_z() const;  // inline member function
  float get_x() const { return data_[0]; }
  float get_y() const { return data_[1]; }
  float get_z() const { return data_[2]; }

  Vector& operator=(const Vector& rhs);  // assignment operator
  Vector& operator+=(const Vector& rhs);  // add operator
  Vector& operator-=(const Vector& rhs);  // subtract operator
  // float operator*(const Vector& rhs);  // dot product operator

 private:
  float* data_;
};  // class vector

float operator*(const Vector& lhs, const Vector& rhs);  // dot product operator
Vector operator+(const Vector& u, const Vector& v);
Vector operator-(const Vector& u, const Vector& v);
Vector operator*(const Vector& u, const float number);
Vector operator*(const float number, const Vector& u);
std::ostream& operator<<(std::ostream& os, const Vector& u);

}  // namespace vector

#endif  // VECTOR_H_
