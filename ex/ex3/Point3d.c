//  Copyright 2023 <Logan Sun, Yuhua Nie> [legal/copyright]
//  Emails: ysun01@uw.edu, nieyuhua@uw.edu
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "Point3d.h"

// typedef struct point3d {
//     int32_t x;
//     int32_t y;
//     int32_t z;
// } Point3d;

Point3d* Point3d_Allocate(int32_t x, int32_t y, int32_t z) {
    Point3d* pointer = (Point3d*)malloc(sizeof(Point3d));
    pointer->x = x;
    pointer->y = y;
    pointer->z = z;
    return pointer;
}
void Point3d_Scale(Point3d* pointer, int32_t scale) {
    pointer->x *= scale;
    pointer->y *= scale;
    pointer->z *= scale; 
}
Point3d Point3d_GetOrigin() {
    Point3d origin;
    origin.x = 0;
    origin.y = 0;
    origin.z = 0;
    return origin;
}