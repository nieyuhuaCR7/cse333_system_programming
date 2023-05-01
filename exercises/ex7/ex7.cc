// Copyright [2023] <Yuhua Nie, Yanxiao Sun> [legal/copyright]
// nieyuhua@uw.edu, ysun01@uw.edu
#include <cassert>
#include <iostream>
#include <sstream>
#include "Vector.h"

int main() {
  // test default constructor
  vector333::Vector zerovector;
  if (zerovector.get_x() != 0
  || zerovector.get_y() != 0 || zerovector.get_z() !=0) {
    std::cerr << "default constrcutor test failed" << std::endl;
    return EXIT_FAILURE;
  }

  // test general constructor
  vector333::Vector v1(7.0f, 7.0f, 7.0f);
  if (v1.get_x() != 7.0f || v1.get_y() != 7.0f || v1.get_z() !=7.0f) {
    std::cerr << "general constrcutor test failed" << std::endl;
    return EXIT_FAILURE;
  }

  // test copy constrcutor
  vector333::Vector v2(v1);
  if (v2.get_x() != 7.0f || v2.get_y() != 7.0f || v2.get_z() != 7.0f) {
    std::cerr << "copy constructor test failed" << std::endl;
    return EXIT_FAILURE;
  }

  // test assignment operator
  zerovector = v1;
  if (zerovector.get_x() != 7.0f
  || zerovector.get_y() != 7.0f || zerovector.get_z() != 7.0f) {
    std::cerr << "assignment operator test failed" << std::endl;
    return EXIT_FAILURE;
  }

  // test += operator
  v1 += v2;
  if (v1.get_x() != 14.0f || v1.get_y() != 14.0f || v1.get_z() != 14.0f) {
    std::cerr << "+= operator test failed" << std::endl;
    return EXIT_FAILURE;
  }

  // test -= operator
  v1 -= v2;
  if (v1.get_x() != 7.0f || v1.get_y() != 7.0f || v1.get_z() != 7.0f) {
    std::cerr << "-= operator test failed" << std::endl;
    return EXIT_FAILURE;
  }

  // test dot product operator
  vector333::Vector v3(1, 2, 3);
  vector333::Vector v4(3, 2, 1);
  float dot_product = v3 * v4;
  if (dot_product != 10) {
    std::cerr << "dot product operator test failed" << std::endl;
    return EXIT_FAILURE;
  }

  // test vector addition
  vector333::Vector v5 = v3 + v4;
  if (v5.get_x() != 4.0f || v5.get_y() != 4.0f || v5.get_z() != 4.0f) {
    std::cerr << "vector addition test failed" << std::endl;
    return EXIT_FAILURE;
  }

  // test vector subtraction
  vector333::Vector v6 = v5 - v4;
  if (v6.get_x() != 1.0f || v6.get_y() != 2.0f || v6.get_z() != 3.0f) {
    std::cerr << "vector subtraction test failed" << std::endl;
    return EXIT_FAILURE;
  }

  // test vector multiplication
  vector333::Vector v7 = v6 * 7;
  if (v7.get_x() != 7.0f || v7.get_y() != 14.0f || v7.get_z() != 21.0f) {
    std::cerr << "vector multiplication test failed" << std::endl;
    return EXIT_FAILURE;
  }

  vector333::Vector v8 = 7 * v7;
  if (v8.get_x() != 49.0f || v8.get_y() != 98.0f || v8.get_z() != 147.0f) {
    std::cerr << "vector multiplication test failed" << std::endl;
    return EXIT_FAILURE;
  }

  // test vector stream output
  vector333::Vector v9(7, 77, 777);
  std::stringstream ss;
  ss << v9;
  assert(ss.str() == "(7,77,777)" && "it should print (7,77,777)");
  return 0;
}
