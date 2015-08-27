#ifndef STRUCTS_H
#define STRUCTS_H

#include "monitor_cthulhu.h"

struct Color {
  float red,
        green,
        blue;
        };

struct Point {
	double x,
		y;
};

struct Image {
	int matrix[MAXIMOX][MAXIMOY];
};

#endif
