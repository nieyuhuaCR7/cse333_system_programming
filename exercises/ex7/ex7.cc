// Copyright [2023] <Yuhua Nie, Yanxiao Sun> [legal/copyright]
// nieyuhua@uw.edu, ysun01@uw.edu
#include <iostream>
#include "Vector.h"

// using vector;

void Increment(vector333::Vector instance) {
    instance += vector333::Vector(1, 1, 1);
}

bool VerifyAddress(const vector333::Vector& instance, void* address) {
    return &instance == address;
}

int main() {
    // test default constructor
    vector333::Vector zerovector;
    if (zerovector.get_x() != 0
    || zerovector.get_y() != 0 || zerovector.get_z() !=0) {
        std::cout << "default constrcutor test failed" << std::endl;
        return EXIT_FAILURE;
    }

    // test general constructor
    vector333::Vector v1(7.0f, 7.0f, 7.0f);
    if (v1.get_x() != 7.0f || v1.get_y() != 7.0f || v1.get_z() !=7.0f) {
        std::cout << "general constrcutor test failed" << std::endl;
        return EXIT_FAILURE;
    }

    // test copy constrcutor
    vector333::Vector v2(v1);
    if (v2.get_x() != 7.0f || v2.get_y() != 7.0f || v2.get_z() != 7.0f) {
        std::cout << "copy constructor test failed" << std::endl;
        return EXIT_FAILURE;
    }

    // test assignment operator
    zerovector = v1;
    if (zerovector.get_x() != 7.0f
    || zerovector.get_y() != 7.0f || zerovector.get_z() != 7.0f) {
        std::cout << "assignment operator test failed" << std::endl;
        return EXIT_FAILURE;
    }

    // test += operator
    v1 += v2;
    if (v1.get_x() != 14.0f || v1.get_y() != 14.0f || v1.get_z() != 14.0f) {
        std::cout << "+= operator test failed" << std::endl;
        return EXIT_FAILURE;
    }

    // test -= operator
    v1 -= v2;
    if (v1.get_x() != 7.0f || v1.get_y() != 7.0f || v1.get_z() != 7.0f) {
        std::cout << "-= operator test failed" << std::endl;
        return EXIT_FAILURE;
    }

    // test dot product operator
    vector333::Vector v3(1, 2, 3);
    vector333::Vector v4(3, 2, 1);
    float dot_product = v3 * v4;
    if (dot_product != 10) {
        std::cout << "dot product operator test failed" << std::endl;
        return EXIT_FAILURE;
    }

    // test increment function
    Increment(v3);  // pass by value
    if (v3.get_x() == 1) {
        std::cout << "Vector: pass-by-value" << std::endl;
    } else {
        std::cout << "Vector: pass-by-reference" << std::endl;
    }

    if (VerifyAddress(v4, &v4)) {
        std::cout << "Ref: same address" << std::endl;
    } else {
        std::cout << "Ref: different address" << std::endl;
    }
    return 0;
}
