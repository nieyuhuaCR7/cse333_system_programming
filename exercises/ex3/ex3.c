#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "Point3d.h"

int main(){
    Point3d* p = Point3d_Allocate(7,17,77);
    if(p == NULL){
        printf("Point3d_Allocate failed to allocate space for pointer\n");
        return EXIT_FAILURE;
    }

    if(p->x != 7){
        printf("the value of x is not correct\n");
        return EXIT_FAILURE;
    }

    if(p->y != 17){
        printf("the value of y is not correct\n");
        return EXIT_FAILURE;
    }

    if(p->z != 77){
        printf("the value of z is not correct\n");
        return EXIT_FAILURE;
    }

    Point3d_Scale(p, 7);
    printf("x: %d, y: %d, z: %d\n", p->x,p->y, p->z);

    Point3d origin = Point3d_GetOrigin();
    printf("origin:\nx: %d, y: %d, z: %d\n",origin.x,origin.y,origin.z);

    return 0;


}