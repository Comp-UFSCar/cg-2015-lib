/** @file object2d_functions.c
 *  @brief Base object functions for the library.
 *
 *  @author Thales Menato (thamenato)
 *  @author Daniel Nobusada (nobusada)
 *  @author Marcelo Lopes Lotufo (0tho)
 *
 */
#include "../header/object2d_functions.h"

void drawLine(struct Point2D *p1, struct Point2D *p2, struct Window *win,
              struct BufferDevice *device, int color) {

    double a, b;
    int i, j, aux;
    struct Point2D *pn1, *pd1, *pn2, *pd2;

    pn1 = sru2srn(p1, win);
    pd1 = srn2srd(pn1, device);
    pn2 = sru2srn(p2, win);
    pd2 = srn2srd(pn2, device);

    if (pd1->x > pd2->x) {
        aux = (int) pd1->x;
        pd1->x = pd2->x;
        pd2->x = aux;
        aux = (int) pd1->y;
        pd1->y = pd2->y;
        pd2->y = aux;
    }

    i = (int) pd1->x;
    j = (int) pd1->y;

    if (pd1->x == pd2->x) {
        // fix to draw line from top-down
        if (pd2->y < pd1->y) {
            while (j >= pd2->y) {
                device->buffer[device->ymax - j - 1][i] = color;
                j--;
            }
        }
            // draw line from bottom-up
        else {
            while (j <= pd2->y) {   // '<=' fixes faulty pixel
                device->buffer[device->ymax - j - 1][i] = color;
                j++;
            }
        }
    }
    else {
        a = (pd2->y - pd1->y) / (pd2->x - pd1->x);
        b = pd1->y - a * pd1->x;
        while (i < pd2->x) {
            device->buffer[device->ymax - j - 1][i] = color;
            aux = j;
            j = (int) round(a * (++i) + b);

            if (j > aux) {
                while (aux < j) {
                    device->buffer[device->ymax - aux - 1][i] = color;
                    aux++;
                }
            }
            if (j < aux) {
                while (aux >= j) {
                    device->buffer[device->ymax - aux - 1][i] = color;
                    aux--;
                }
            }
        }
    }
    free(pn1);
    free(pn2);
    free(pd1);
    free(pd2);
}

struct Object2D *plotCircle(struct Point2D *o, int r, int steps, int fillColor, int borderColor) {
    double x, y;
    double theta = 0, h, k, step;
    step = 2 * PI / steps;
    h = o->x;
    k = o->y;
    struct Object2D *sphere;
    sphere = createObject(steps, borderColor, fillColor);

    for (theta = 0; theta < 2 * PI; theta += step) {
        x = h + r * cos(theta);
        y = k - r * sin(theta);
        setObject(setPoint(x, y), sphere);
    }

    return sphere;
}

//TODO Documentacao do drawObject
int drawObject(struct Object2D *object, struct Window *window, struct BufferDevice *device) {
    if (object->curr_point == 0)
        return False;

    //printf("%d point\n", object->curr_point);
    for (int i = 0; i < object->curr_point; i++) {
//        printf("\np1 = (%f,%f), p2 = (%f,%f)",
//               object->points[i].x,
//               object->points[i].y,
//               object->points[(i+1) % object->curr_point].x,
//               object->points[(i+1) % object->curr_point].y);

        drawLine(&object->points[i], &object->points[(i + 1) % object->curr_point],
                 window, device, object->borderColor);
    }

    return True;
}

/*
 * Translates object by X and Y
 */
void translate(struct Object2D *object, double x, double y) {
    int i;

    for (i = 0; i < object->curr_point; i++) {
        struct Point2D *p = &object->points[i];

        p->x += x;
        p->y += y;
    }
}

/*
 *  Translates object to a point
 */
void translateTo(struct Object2D *object, struct Point2D *point) {
    translate(object, point->x, point->y);
}

/*
 * Rotates object by radians around an axis (Point 2D)
 */
void rotate(struct Object2D *object, double radians, struct Point2D *axis) {

    int i;

    double rotateCos = cos(radians),
            rotateSin = sin(radians);

    translate(object, -axis->x, -axis->y);

    for (i = 0; i < object->curr_point; i++) {
        struct Point2D *p = &object->points[i];

        double  x = p->x,
                y = p->y;

        p->x = rotateCos*x - rotateSin*y;
        p->y = rotateSin*x + rotateCos*y;
    }

    translate(object, axis->x, axis->y);
}

/*
 * Rotates object by radians around an axis (x , y)
 */
void rotateXY(struct Object2D *object, double radians, double x, double y) {
    struct Point2D *point = setPoint(x, y);

    rotate(object, radians, point);
}

/*
 * Scales object by X and Y
 */
void scale(struct Object2D *object, double x, double y, struct Point2D *axis) {
    int i;

    translate(object, -axis->x, -axis->y);

    for (i = 0; i < object->curr_point; i++) {
        struct Point2D *p = &object->points[i];

        p->x *= x;
        p->y *= y;
    }

    translate(object, axis->x, axis->y);
}

/*
 *  Skew object by X and Y
 */
void skew(struct Object2D *object, double x, double y, struct Point2D *axis) {
    int i;

    translate(object, -axis->x, -axis->y);

    for (i = 0; i < object->curr_point; i++) {
        struct Point2D *p = &object->points[i];

        printf("%d %d %d", p->x, p->y, x, y);
        p->x += x * p->y;
        p->y += y * p->x;
    }

    translate(object, axis->x, axis->y);
}

struct Point2D *getCenter(struct Object2D *object) {

    int i;
    double minX, minY, maxX, maxY;

    maxX = minX = object->points[0].x;
    maxY = minY = object->points[0].y;

    for (i = 1; i < object->curr_point; i++) {
        struct Point2D *p = &object->points[i];

        if (maxX < p->x) {
            maxX = p->x;
        }

        if (minX > p->y) {
            minX = p->y;
        }

        if (maxY < p->y) {
            maxY = p->y;
        }

        if (minY > p->y) {
            minY = p->y;
        }
    };

    return setPoint((minX + maxX) / 2.0, (minY + maxY) / 2);
}

struct Matrix3x3 *matrix3x3Identity() {
    struct Matrix3x3 *identity = malloc(sizeof(struct Matrix3x3));

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            identity->mat[i][j] = (i == j);

    return identity;
}

struct Matrix3x3 *matrix3x3Multiply(struct Matrix3x3 a, struct Matrix3x3 b) {
    struct Matrix3x3 *mult = malloc(sizeof(struct Matrix3x3));

    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            mult->mat[row][col] = a.mat[row][0] * b.mat[0][col] +
                              a.mat[row][1] * b.mat[1][col] +
                              a.mat[row][2] * b.mat[2][col];

    return mult;
}

struct Matrix3x3 *matrix3x3Translate(float tx, float ty, struct Matrix3x3 mat) {
    struct Matrix3x3 *translate = matrix3x3Identity();

    translate->mat[0][2] = tx;
    translate->mat[1][2] = ty;

    return matrix3x3Multiply(*translate, mat);
}

struct Matrix3x3 *matrix3x3Scale(float sx, float sy, struct Point2D axis, struct Matrix3x3 mat) {
    struct Matrix3x3 *scale = matrix3x3Identity();

    scale->mat[0][0] = sx;
    scale->mat[0][2] = (1 - sx) * (float) axis.x;
    scale->mat[1][1] = sy;
    scale->mat[1][2] = (1 - sy) * (float) axis.y;

    return matrix3x3Multiply(*scale, mat);
}

struct Matrix3x3 *matrix3x3RotateRadians(float radian, struct Point2D axis, struct Matrix3x3 mat) {
    struct Matrix3x3 *rotate = matrix3x3Identity();

    rotate->mat[0][0] = cosf(radian);
    rotate->mat[0][1] = -sinf(radian);
    rotate->mat[0][2] = (float) axis.x * (1 - cosf(radian)) + (float) axis.y * sinf(radian);
    rotate->mat[1][0] = sinf(radian);
    rotate->mat[1][1] = cosf(radian);
    rotate->mat[1][2] = (float)axis.y * (1 - cosf(radian)) - (float)axis.y * sinf(radian);

    return matrix3x3Multiply(*rotate, mat);
}

struct Matrix3x3 *matrix3x3RotateDegrees(float degree, struct Point2D axis, struct Matrix3x3 mat) {
    float radian = (float)(PI / 180.0) * degree;

    return matrix3x3RotateRadians(radian, axis, mat);
}

void matrix3x3TransformPoints(struct Object2D *object2D, struct Matrix3x3 transform) {
    float temp;

    for(int i = 0; i < object2D->curr_point; i++){
        temp = (float)(transform.mat[0][0] * object2D->points[i].x +
                transform.mat[0][1] * object2D->points[i].y +
                transform.mat[0][2]);
        object2D->points[i].y = transform.mat[1][0] * object2D->points[i].x +
                transform.mat[1][1] * object2D->points[i].y + transform.mat[1][2];
        object2D->points[i].x = temp;

    }
}

//TODO: This function may not be necessary. Delete if confirmed.
double getWidth( struct Object2D *object ) {

    int i;
    double minX, maxX;

    maxX = minX = object->points[0].x;

    for( i = 1; i < object->curr_point; i++ ) {
        struct Point2D *p = &object->points[i];

        if( maxX < p->x ) {
            maxX = p->x;
        }

        if( minX > p->y ) {
            minX = p->y;
        }

    };

    return maxX - minX;

}

//TODO: This function may not be necessary. Delete if confirmed.
double getHeight( struct Object2D *object ) {

    int i;
    double minY, maxY;

    maxY = minY = object->points[0].y;

    for( i = 1; i < object->curr_point; i++ ) {
        struct Point2D *p = &object->points[i];

        if( maxY < p->y ) {
            maxY = p->y;
        }

        if( minY > p->y ) {
            minY = p->y;
        }
    };

    return maxY - minY;
}

//TODO: This function may not be necessary. Delete if confirmed.
double getMinY( struct Object2D *object ) {

    int i;
    double minY;

    minY = object->points[0].y;

    for( i = 1; i < object->curr_point; i++ ) {
        struct Point2D *p = &object->points[i];

        if( minY > p->y ) {
            minY = p->y;
        }
    };

    return minY;
}

