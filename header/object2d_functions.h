/** @file object2d_functions.h
 *  @brief Header for Line functions.
 *
 *  This contains functions that draw lines or circles.
 *  - Straight lines, given two points in space.
 *  - Circle, given the radius.
 *
 *  @author Thales Menato (thamenato)
 *  @author Daniel Nobusada (nobusada)
 */

#ifndef LINE_H
#define LINE_H

#include "structs.h"
#include "base_functions.h"

/** @brief Draw a straight line given two points
 *
 *  Two points on space will be first normalized to the window,
 *  and then converted to the device space. With the points now
 *  set to the device reference, the algorithm tracks and plots a
 *  line between the two points.
 *
 *  @param p1 A point in space.
 *  @param p2 Another point in space.
 *  @param win Window where this should be based on.
 *  @param device BufferDevice where this will be allocated.
 *  @param color RGBColor number that will be used based on a Palette.
 */
void drawLine(struct Point2D *p1, struct Point2D *p2, struct Window *win,
              struct BufferDevice *device, int color);

/** @brief Given the point of origin, radius, and how many steps, defines the points that composes a circle.
 *  @param origin The origin point of the circle.
 *  @param radius Radius of the circle.
 *  @param color RGBColor number that will be used based on a Palette.
 *  @param steps How many steps to be used, more means precision.
 *  @param color Color number that will be used based on a Palette.
 *  @return Object2D with circle points.
 */
struct Object2D *plotCircle(struct Point2D *origin, int radius, int steps, int color);

//TODO Documentacao do drawObject
int drawObject(struct Object2D *object, struct Window *window, struct BufferDevice *device);

void translate ( struct Object2D *, double x, double y );
void translateTo ( struct Object2D *object, struct Point2D *point );
void rotate ( struct Object2D *object, double radians, struct Point2D * axis );
void rotateXY ( struct Object2D *object, double radians, double x, double y );
void scale ( struct Object2D *object, double x, double y, struct Point2D * axis );
void skew (struct Object2D *object, double x, double y, struct Point2D * axis );
struct Point2D* getCenter( struct Object2D *object );

struct Matrix3x3 *matrix3x3Identity();
struct Matrix3x3 *matrix3x3Multiply(struct Matrix3x3 a, struct Matrix3x3 b);
struct Matrix3x3 *matrix3x3Translate(float tx, float ty, struct Matrix3x3 mat);
struct Matrix3x3 *matrix3x3Scale(float sx, float sy, struct Point2D axis, struct Matrix3x3 mat);
struct Matrix3x3 *matrix3x3RotateRadians(float radian, struct Point2D axis, struct Matrix3x3 mat);
struct Matrix3x3 *matrix3x3RotateDegrees(float degree, struct Point2D axis, struct Matrix3x3 mat);
void matrix3x3TransformPoints(struct Object2D *object2D, struct Matrix3x3 transform);

double getWidth( struct Object2D *object );
double getHeight( struct Object2D *object );
double getMinY( struct Object2D *object );

#endif //LINE_H
