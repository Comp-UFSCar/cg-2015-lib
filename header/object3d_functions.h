/** @file object3d_functions.h
 *  @brief Header for Object3D functions.
 *
 *  This contains functions for transformation to a Object3D:
 *  translate, rotate, scale.
 *
 *  @author Thales Menato (thamenato)
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

#endif //MONITOR_CTHULHU_OBJECT3D_FUNCTIONS_H
