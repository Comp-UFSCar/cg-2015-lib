/** @file object2d_functions.h
 *  @brief Header for Line functions.
 *
 *  This contains functions that draw lines or circles.
 *  - Straight lines, given two points in space.
 *  - Circle, given the radius.
 *
 *  @author Thales Menato (thamenato)
 *  @author Daniel Nobusada (nobusada)
 *  @author Marcelo Lopes Lotufo (0tho)
 *
 */

#ifndef LINE_H
#define LINE_H

#include "structs.h"
#include "base_functions.h"

/** @brief Draw a straight line given two points.
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

/** @brief Given the point of origin, radius, and how many steps,
 * defines the points that composes a circle.
 *
 *  @param origin The origin point of the circle.
 *  @param radius Radius of the circle.
 *  @param color RGBColor number that will be used based on a Palette.
 *  @param steps How many steps to be used, more means precision.
 *  @param color Color number that will be used based on a Palette.
 *  @return Object2D with circle points.
 */
struct Object2D *plotCircle(struct Point2D *o, int r, int steps, int borderColor, int fillColor);

/*  @brief Given Object2D, Window and BufferDevice, define the object on device.
 *
 *  Verify if object have any defined points and draw a line between consecutive
 *  points until it connects the last point with first one, closing the polygon.
 *
 *  @param object The object wanted to be defined on device.
 *  @param window Universe window that will be used.
 *  @param device BufferDevice where window will be seen.
 *  @return True if object is defined, false otherwise.
 */
int drawObject(struct Object2D *object, struct Window *window, struct BufferDevice *device);

/** @brief Translates object by x and y.
 *  @param object Object to be translated.
 *  @param x Double value of x axis translation.
 *  @param y Double value of y axis translation.
 */
void translate(struct Object2D *object, double x, double y);

/** @brief Translate object to a point.
 *  @param object Object to be translated.
 *  @param point Point where object will be translated to.
 */
void translateTo(struct Object2D *object, struct Point2D *point);

/** @brief Rotates object by radians around an axis (Point 2D).
 *  @param object Object to be rotated.
 *  @param radians Radian value that will be used for rotation.
 *  @param axis Point2D that will be used as origin axis for rotation function.
 */
void rotate(struct Object2D *object, double radians, struct Point2D *axis);

/** @brief Rotates object by radians around an axis (x,y).
 *  @param object Object to be rotated.
 *  @param radians Radian value that will be used for rotation.
 *  @param x X component of axis.
 *  @param y Y component of axis.
 */
void rotateXY(struct Object2D *object, double radians, double x, double y);

/** @brief Scales object by X and Y.
 *  @param object Object to be scaled.
 *  @param x Value for X component to be scaled.
 *  @param y Value for Y component to be scaled.
 *  @param axis Point to be used as origin axis for function.
 */
void scale(struct Object2D *object, double x, double y, struct Point2D *axis);

/** @brief Skew object by X and Y.
 *  @param object Object to receive skew.
 *  @param x Value for X component to be skewed.
 *  @param y Value for Y component to be skewed.
 *  @param axis Point to be used as origin axis for function.
 */
void skew(struct Object2D *object, double x, double y, struct Point2D *axis);

/** @brief Get object's center point.
 *  @param object The object that the center point is wanted.
 *  @return Point2D that is the object's center.
 */
struct Point2D *getCenter(struct Object2D *object);

/** @brief 3x3 Identity Matrix.
 *  @return A 3x3 Identity Matrix inside struct Matrix3x3.
 */
struct Matrix3x3 *matrix3x3Identity();

/** @brief Multiply two 3x3 matrix.
 *  @param a A matrix.
 *  @param b B matrix.
 *  @return 3x3 matrix that is the multiplication of A by B.
 */
struct Matrix3x3 *matrix3x3Multiply(struct Matrix3x3 a, struct Matrix3x3 b);

/** @brief Translation using Homogeneous coordinates.
 *  @param tx Value for translation on X axis.
 *  @param ty Value for translation on Y axis.
 *  @param mat Matrix3x3 that translation will be applied.
 *  @return 3x3 matrix containing translation.
 */
struct Matrix3x3 *matrix3x3Translate(float tx, float ty, struct Matrix3x3 mat);

/** @brief Scale using Homogeneous coordinates.
 *  @param sx Value for scale on X axis.
 *  @param sy Value for scale on Y axis.
 *  @param axis Origin axis to be used for scale transformation.
 *  @param mat Matrix3x3 that scale will be applied.
 *  @return 3x3 matrix containing scale function.
 */
struct Matrix3x3 *matrix3x3Scale(float sx, float sy, struct Point2D axis, struct Matrix3x3 mat);

/** @brief Rotation using radians and Homogeneous coordinates.
 *  @param radian Values, in radian, to be rotate.
 *  @param axis Origin axis to be used on rotation.
 *  @param mat Matrix3x3 that rotation will be applied.
 *  @return 3x3 matrix containing rotation function.
 */
struct Matrix3x3 *matrix3x3RotateRadians(float radian, struct Point2D axis, struct Matrix3x3 mat);

/** @brief Rotation using degrees and Homogeneous coordinates.
 *  @param degree Values, in degrees, to be rotate.
 *  @param axis Origin axis to be used on rotation.
 *  @param mat Matrix3x3 that rotation will be applied.
 *  @return 3x3 matrix containing rotation function.
 */
struct Matrix3x3 *matrix3x3RotateDegrees(float degree, struct Point2D axis, struct Matrix3x3 mat);

/** @brief Apply homogeneous coordinates to Object2D.
 *  @param object2D Object where homogeneous coordinates will be applied.
 *  @param transform The matrix containing the homogeneous coordinates.
 */
void matrix3x3TransformPoints(struct Object2D *object2D, struct Matrix3x3 transform);

/** @brief Get the width of an Object2D.
 *  @param object The object that width will be measured.
 *  @return Width of the object.
 */
double getWidth(struct Object2D *object);

/** @brief Get the height of an Object2D.
 *  @param object The object that height will be measured.
 *  @return Height of the object.
 */
double getHeight(struct Object2D *object);

/** @brief Get minimum Y value defined inside Object2D.
 *  @param object The object that will be used to get minimum Y.
 *  @return The minimum Y.
 */
double getMinY(struct Object2D *object);

#endif //LINE_H
