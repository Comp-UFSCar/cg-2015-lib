#ifndef STRUCTS_H
#define STRUCTS_H

#include "monitor_cthulhu.h"

#define PI 3.1415926535

struct Universe {
    float   xmin, xmax,
            ymin, ymax;
};

struct Window {
    float   xmin, xmax,
            ymin, ymax;
};

struct ViewPort {
    int     xmin, xmax,
            ymin, ymax;
};

struct Point2D {
	double  x,
		    y;
    int     color;
};

struct Object2D {
    int     numberOfPoints;
    struct Point2D * points;
};

struct Color {
    float   red,
            green,
            blue;
};

struct Palette {
    int numberOfColors;
    struct Color * colors;
};

struct BufferDevice {
    int     xmax, ymax;
    int *   buffer;
};

#endif
