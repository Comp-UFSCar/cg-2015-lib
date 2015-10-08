#ifndef MONITOR_CTHULHU_H
#define MONITOR_CTHULHU_H

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

#endif //MONITOR_CTHULHU_H
