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
    if(p->x != 7*7){
        printf("after scaling, the value of p->x is not correct\n");
        return EXIT_FAILURE;
    }

    if(p->y != 7*17){
        printf("after scaling, the value of p->y is not correct\n");
        return EXIT_FAILURE;
    }

    if(p->y != 7*77){
        printf("after scaling, the value of p->z is not correct\n");
        return EXIT_FAILURE;
    }

    Point3d origin = Point3d_GetOrigin();
    printf("origin:\nx: %d, y: %d, z: %d\n",origin.x,origin.y,origin.z);
    if(origin.x != 0){
        printf("get_origin function for x is not correct\n");
        return EXIT_FAILURE;
    }

    if(origin.y != 0){
        printf("get_origin function for y is not correct\n");
        return EXIT_FAILURE;
    }

    if(origin.z !=0){
        printf("get_origin function for z is not correct\n");
        return EXIT_FAILURE;
    }
    
    free(p);

    return 0;


}