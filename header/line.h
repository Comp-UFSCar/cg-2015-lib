/** @file line.h
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

void plotLine(struct Point2D *p1, struct Point2D *p2, struct Window *win,
struct BufferDevice *device, int color);

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

/** @brief Given the radius, defines the points that composes a circle.
 *  @param radius Radius of the circle.
 *  @param color RGBColor number that will be used based on a Palette.
 *  @return Object2D with circle points.
 */
struct Object2D *createCircle(float radius, int color);
struct Object2D *plotCircle(struct Point2D *o, int r, int steps, int color);

#endif //LINE_H
