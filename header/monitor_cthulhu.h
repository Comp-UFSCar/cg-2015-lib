#ifndef MONITOR_CTHULHU_H
#define MONITOR_CTHULHU_H

#define MAXIMOX 1024
#define MAXIMOY 768

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "structs.h"

#define EventMask (KeyPressMask | ExposureMask)

// Global variables
struct Universe universe;  // Define the Universe

Display * display;
Window window;
GC gc;
Visual * visual;
XGCValues values;
XImage *ximage;
XEvent an_event;
KeySym key;
int screen, dplanes, height, width, ret;

#endif //MONITOR_CTHULHU_H
