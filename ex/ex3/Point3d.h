#ifndef POINT3D_H_
#define POINT3D_H_


typedef struct point3d {
    int32_t x;
    int32_t y;
    int32_t z;
} Point3d;

Point3d* Point3d_Allocate(int32_t x, int32_t y, int32_t z);

void Point3d_Scale(Point3d* pointer, int32_t scale);

Point3d Point3d_GetOrigin();

#endif // POINT3D_H_