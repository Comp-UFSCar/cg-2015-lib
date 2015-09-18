#ifndef LINE_H
#define LINE_H

#include "structs.h"
#include "base_functions.h"

void drawLine(struct Point2D *p1, struct Point2D *p2, struct Window * win,
                      struct BufferDevice *device, int color);

#endif //LINE_H
