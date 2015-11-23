/** @file object3d_functions.c
 *  @brief Base Object3D functions for the library.
 *
 *  @author Thales Menato (thamenato)
 *  @author Marcelo Lopes Lotufo (0tho)
 */

#include "../header/object3d_functions.h"

/*
 * 4x4 Identity Matrix.
 */
struct Matrix4x4 *matrix4x4Identity() {
    struct Matrix4x4 *identity = malloc(sizeof(struct Matrix4x4));

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            identity->mat[i][j] = (i == j);
    }

    return identity;
}

/*
 * Multiply two 4x4 matrix and return the result.
 */
struct Matrix4x4 *matrix4x4Multiply(struct Matrix4x4 a, struct Matrix4x4 b){
    struct Matrix4x4 *mult = malloc(sizeof(struct Matrix4x4));

    for(int row = 0; row < 4; row++)
        for(int col = 0; col < 4; col++)
            mult->mat[row][col] = a.mat[row][0] * b.mat[0][col] +
                                  a.mat[row][1] * b.mat[1][col] +
                                  a.mat[row][2] * b.mat[2][col] +
                                  a.mat[row][3] * b.mat[3][col];

    return mult;
}

/*
 * Translation using Homogeneous coordinates.
 */
struct Matrix4x4 *matrix4x4Translate(float tx, float ty, float tz, struct Matrix4x4 mat) {
    struct Matrix4x4 *translate = matrix4x4Identity();

    translate->mat[0][3] = tx;
    translate->mat[1][3] = ty;
    translate->mat[2][3] = tz;

    return matrix4x4Multiply(*translate, mat);
}

/*
 * Scale using Homogeneous coordinates.
 */
struct Matrix4x4 *matrix4x4Scale(float sx, float sy, float sz, struct Point3D axis, struct Matrix4x4 mat) {
    struct Matrix4x4 *scale = matrix4x4Identity();

    scale->mat[0][0] = sx;
    scale->mat[0][3] = (1 - sx) * axis.x;
    scale->mat[1][1] = sy;
    scale->mat[1][3] = (1 - sy) * axis.y;
    scale->mat[2][2] = sz;
    scale->mat[2][3] = (1 - sz) * axis.z;

    return matrix4x4Multiply(*scale, mat);
}

/*
 * Rotation using radians and Homogeneous coordinates.
 */
struct Matrix4x4 *matrix4x4RotateRadians(float radian, struct Point3D p1, struct Point3D p2, struct Matrix4x4 mat) {
    struct Matrix4x4 *rotate = matrix4x4Identity();
    struct Matrix4x4 *translate = matrix4x4Identity();

    float length = (float) sqrt((p2.x - p1.x) * (p2.x - p1.x) +
                                (p2.y - p1.y) * (p2.y - p1.y) +
                                (p2.z - p1.z) * (p2.z - p1.z));
    float cosA2 = cosf(radian / 2.0f);
    float sinA2 = sinf(radian / 2.0f);
    float a = sinA2 * (p2.x - p1.x) / length;
    float b = sinA2 * (p2.y - p1.y) / length;
    float c = sinA2 * (p2.z - p1.z) / length;

    translate = matrix4x4Translate(-p1.x, -p1.y, -p1.z, mat);

    rotate->mat[0][0] = 1.0f - 2*b*b - 2*c*c;
    rotate->mat[0][1] = 2*a*b - 2*cosA2*c;
    rotate->mat[0][2] = 2*a*c + 2*cosA2*b;
    rotate->mat[1][0] = 2*a*b + 2*cosA2*c;
    rotate->mat[1][1] = 1.0f - 2*a*a - 2*c*c;
    rotate->mat[1][2] = 2*b*c - 2*cosA2*a;
    rotate->mat[2][0] = 2*a*c - 2*cosA2*b;
    rotate->mat[2][1] = 2*b*c + 2*cosA2*a;
    rotate->mat[2][2] = 1.0f - 2*a*a - 2*b*b;

    return matrix4x4Multiply(*rotate, *translate);
}

/*
 * Apply homogeneous coordinates to Object3D.
 */
void matrix4x4TransformPoints(struct Object3D *object3D, struct Matrix4x4 transform) {
    float temp[3];
    for(int i = 0; i < object3D->curr_point; i++){
        for(int j = 0; j < 3; j++)
            temp[j] = transform.mat[j][0] * object3D->points[i].x +
                    transform.mat[j][1] * object3D->points[i].y +
                    transform.mat[j][2] * object3D->points[i].z +
                    transform.mat[j][3];

            object3D->points[i].x = temp[0];
            object3D->points[i].y = temp[1];
            object3D->points[i].z = temp[2];
    }
}
