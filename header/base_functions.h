#include <X11/Xlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

#ifndef FUNCTIONS_LIB_H
#define FUNCTIONS_LIB_H

void XDump(XImage *ximage, struct Image img);
struct Point sru2srn(struct Point p, double xmin, double ymin, double xmax, double ymax);
struct Point srn2srd(struct Point mc);
struct Image drawLine_Bresenham(struct Point p0, struct Point p1);
void init_image(struct Image *img);
void print_image(struct Image img);
struct Image input_line_bresenham(char *argv[]);
struct Image input_line_bresenham_sru(char *argv[]);

#endif