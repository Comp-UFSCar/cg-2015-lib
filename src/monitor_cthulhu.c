/** @file monitor_cthulhu.c
 *  @brief main c file containing examples on how to use the lib.
 *
 *  Computer Graphics and Multimedia - UFSCar/Fall 2015
 *
 *                          Prof. Murillo Rodrigo Petrucelli Homem
 *
 *  Students:
 *      Thales Eduardo Adair Menato     407976
 *      Marcelo Lopes Lotufo            407933
 *
 *  If you're compiling manually using gcc don't forget to add the flags:
 *      -lm -lX11 -std=c99
 */

#include "../header/monitor_cthulhu.h"

int main(int argc, char *argv[]) {

    struct Point3D *p1 = createPoint3D(0, 0, 0);
    struct Point3D *p2 = createPoint3D(1, 0, 0);
    struct Point3D *p3 = createPoint3D(1, 1, 0);
    struct Point3D *p4 = createPoint3D(0, 1, 0);

    struct Matrix3x3 *m = matrix3x3Identity();
    m->mat[0][1] = 1;
    m->mat[1][0] = 1;
    m->mat[2][0] = 1;

    struct Object3D *obj = createObject3D(1);
    struct Object3DFace *face = createFace(4);

    addPoint3DtoFace(p1, face);
    addPoint3DtoFace(p2, face);
    addPoint3DtoFace(p3, face);
    addPoint3DtoFace(p4, face);

    addFaceToObject3D(face, obj);

    struct Object3D *new_obj = convertObject3DBase(m, obj);

    printObject3D(*obj);
    printObject3D(*new_obj);

}

void printObject3D(struct Object3D obj){
    for(int i = 0; i < obj.curr_face; i++){
        printf("Face %d\n", i);
        printFace(obj.faces[i]);
    }
}

void printFace(struct Object3DFace face){
    for(int i = 0 ; i < face.curr_point; i++){
        printf("\tp%d :%f, %f, %f \n", i, face.points[i].x, face.points[i].y, face.points[i].z);
    }
}