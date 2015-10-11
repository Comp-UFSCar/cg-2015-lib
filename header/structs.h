/** @file structs.h
 *  @brief All the struct for this lib.
 *
 *  @author Thales Menato (thamenato)
 *  @author Daniel Nobusada (nobusada)
 */

#ifndef STRUCTS_H
#define STRUCTS_H

#include "monitor_cthulhu.h"

/* @def PI Approximation of PI */
#define PI 3.14159265358979323846

float world_xmin, world_xmax, world_ymin, world_ymax;

/** @struct Window
 *  @brief Defines the Window boundaries.
 *  @var Window::xmin
 *  Member 'xmin' contains the minimum value of x.
 *  @var Window::xmax
 *  Member 'xmax' contains the maximum value of x.
 *  @var Window::ymin
 *  Member 'ymin' contains the minimum value of y.
 *  @var Window::ymax
 *  Member 'ymax' contains the maximum value of y.
 */
struct Window {
    float xmin, xmax,
            ymin, ymax;
};

/** @struct ViewPort
 *  @brief Defines the ViewPort boundaries.
 *  @var ViewPort::xmin
 *  Member 'xmin' contains the minimum value of x.
 *  @var ViewPort::xmax
 *  Member 'xmax' contains the maximum value of x.
 *  @var ViewPort::ymin
 *  Member 'ymin' contains the minimum value of y.
 *  @var ViewPort::ymax
 *  Member 'ymax' contains the maximum value of y.
 */
struct ViewPort {
    int xmin, xmax,
            ymin, ymax;
};

/** @struct Point2D
 *  @brief Defines a point in a 2D space.
 *  @var Point2D::x
 *  Member 'x' contains the x position.
 *  @var Point2D::y
 *  Member 'y' contains the y position.
 *  @var Point2D::color
 *  Member 'color' contains Color reference number of a Palette.
 */
struct Point2D {
    double x, y;
    int color;
};

/** @struct Object2D
 *  @brief Defines an object in a 2D space with multiple Point2D.
 *  @var Object2D::max_points
 *  Member 'max_points' sets the maximum number of points this object will have.
 *  @var Object2D::curr_point
 *  Member 'curr_point' is the current point set inside points array.
 *  @var Object2D::points
 *  Member 'points' is an array os points limited by max_points.
 */
struct Object2D {
    int max_points;
    int curr_point;
    struct Point2D *points;
};

/** @struct Color
 *  @brief Defines a color, using RGB.
 *
 *  A Color is not accessed directly, it is added inside a Palette.
 *
 *  @note The value of colors must be in range [0,1].
 *  @var Color::red
 *  Member 'red' is a float number in range [0,1].
 *  @var Color::green
 *  Member 'green' is a float number in range [0,1].
 *  @var Color::blue
 *  Member 'blue' is a float number in range [0,1].
 */
struct Color {
    float red,
            green,
            blue;
};

/** @struct Palette
 *  @brief Defines a palette to be used.
 *
 *  A palette is a set of colors that will be accessed by their index.
 *  Use the function setColor to add new Color to palette.
 *  @see setColor
 *
 *  @var Palette::numberOfColors
 *  Member 'numberOfColors' defines the maximum number for this palette.
 *  @var Palette::currentColor
 *  Member 'currentColor' is colors current index value.
 *  @var Palette::colors
 *  Member 'colors' is the Color array.
 */
struct Palette {
    int numberOfColors;
    int currentColor;
    struct Color *colors;
};

/** @struct BufferDevice
 *  @brief Defines a device to be used.
 *
 *  This device will be used inside the function DumpX and it will be
 *  displayed to the user so one can see the results of one's operations
 *  using the lib.
 *
 *  @var BufferDevice::xmax
 *  Member 'xmax' is the maximum value of x, also the width.
 *  @var BufferDevice::ymax
 *  Member 'ymax' is the maximum value of y, also the height.
 *  @var BufferDevice::buffer
 *  Member 'buffer' is a matrix of int[xmax][ymax].
 */
struct BufferDevice {
    int xmax, ymax;
    int **buffer;
};

#endif
