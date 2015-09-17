#ifndef MONITOR_CTHULHU_H
#define MONITOR_CTHULHU_H

#define MAXIMOX 640
#define MAXIMOY 480

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "structs.h"

// Global variables
Display * display;
Window window;
GC gc;
Visual * visual;
XGCValues values;
XImage *ximage;
XEvent an_event;
KeySym key;
int screen, dplanes, height, width, ret;

#define EventMask (KeyPressMask | ExposureMask)

#endif //MONITOR_CTHULHU_H
