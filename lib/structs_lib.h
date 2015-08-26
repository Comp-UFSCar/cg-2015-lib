#ifndef STRUCTS_LIB_H
#define STRUCTS_LIB_H

#define MAXIMOX 640
#define MAXIMOY 480

struct Color {
  float red,
        green,
        blue;
        };

struct Point {
	float x,
		y;
};

struct Image {
	int matrix[MAXIMOX][MAXIMOY];
};

#endif
