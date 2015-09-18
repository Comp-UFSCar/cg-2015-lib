#include <X11/Xlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

#ifndef FUNCTIONS_LIB_H
#define FUNCTIONS_LIB_H

// X11
int XInit(struct BufferDevice *);
void XShow();
void XClose();
void XDump(XImage *, struct BufferDevice *, struct Palette *);

// Structures
struct Universe * setUniverse(float, float, float, float);
struct BufferDevice * createBuffer(int, int);
struct Window * createWindow(float, float, float, float);
struct Point2D * sru2srn(struct Point2D *, struct Window *);
struct Point2D * srn2srd(struct Point2D *, struct BufferDevice *);
struct Point2D * setPoint(float, float, int);
struct Object2D * createObject(int);
struct Palette * createPalette(int);

#endif