/** @file object3d_functions.h
 *  @brief Header for Object3D functions.
 *
 *  This contains functions for transformation to a Object3D:
 *  translate, rotate, scale.
 *
 *  @author Thales Menato (thamenato)
 *  @author Marcelo Lopes Lotufo (0tho)
 *
 */

#ifndef MONITOR_CTHULHU_OBJECT3D_FUNCTIONS_H
#define MONITOR_CTHULHU_OBJECT3D_FUNCTIONS_H

#include "structs.h"
#include "base_functions.h"

struct Matrix4x4 *matrix4x4Identity();
struct Matrix4x4 *matrix4x4Multiply(struct Matrix4x4 a, struct Matrix4x4 b);
struct Matrix4x4 *matrix4x4Translate(float tx, float ty, float tz, struct Matrix4x4 mat);
struct Matrix4x4 *matrix4x4Scale(float sx, float sy, float sz, struct Point3D axis, struct Matrix4x4 mat);
struct Matrix4x4 *matrix4x4RotateRadians(float radian, struct Point3D p1, struct Point3D p2, struct Matrix4x4 mat);
void matrix4x4TransformPoints(struct Object3D *object3D, struct Matrix4x4 transform);

/*
    point3d * VectorProduct3d(point3d *, point3d *);            // DONE - crossProduct
    float Modulo3d(point3d *);                                  // DONE - euclideanNormPoint3D
    point3d * Versor3d(point3d *);                              // DONE - unitVector3D
    point3d * LinearTransf3d(matrix3d *, point3d *);            // DONE - linearTransfPoint3D
    face * CreateFace(int);                                     // DONE - createFace
    int SetPointFace(point3d *, face *);                        // DONE - addPoint3DtoFace
    object3d * CreateObject3D(int);                             // DONE - createObject3D
    int SetObject3D(face *, object3d *);                        // DONE - addFaceToObject3D
    object3d * ConvertObjectBase(matrix3d *, object3d *);       // 0tho
    object * PerspProjFaces(object3d *, float, float);          // 0tho
 */

#endif //MONITOR_CTHULHU_OBJECT3D_FUNCTIONS_H
