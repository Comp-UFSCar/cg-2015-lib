#include <X11/Xlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

#ifndef FUNCTIONS_LIB_H
#define FUNCTIONS_LIB_H

// X11
int init_x();
void show_x();
void close_x();

// Structures
void init_image(struct Image *img);
void debug_image(struct Image img);
void XDump(XImage *ximage, struct Image img);
struct Point sru2srn(struct Point p, double xmin, double ymin, double xmax, double ymax);
struct Point srn2srd(struct Point mc);

#endif