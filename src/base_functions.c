#include "../header/structs.h"
#include "../header/base_functions.h"

// Initialize the X
int XInit(struct BufferDevice * device){
    // define the height and width based on BufferDevice
    height = device->ymax;
    width = device->xmax;
    ret = True;

    if ((display = XOpenDisplay(NULL)) == NULL)
        ret = False;
    else {
        screen = DefaultScreen(display);
        dplanes = DisplayPlanes(display, screen);
        visual = XDefaultVisual(display, screen);

        if (!(window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, width, height, 1,
                                           BlackPixel(display, screen), WhitePixel(display, screen))))
            ret = False;
        else {
            XSelectInput(display, window, EventMask);
            XStoreName(display, window, "Monitor Cthulhu ^(;.;)^");
            gc = XCreateGC(display, window, 0, &values);

            XMapWindow(display, window);
            XSync(display, False);

            // ximage is what will be shown (where you should write your buffer)
            ximage = XCreateImage(display, visual, dplanes, ZPixmap, 0, malloc(width * height * sizeof(int)), width,
                                  height, 8, 0);
        }
    }
    return ret;
}

// Display with XImage as content
void XShow(){
    char text[255];
    do {
        XNextEvent(display, &an_event);
        switch (an_event.type) {
            case Expose:
                XPutImage(display, window, gc, ximage, 0, 0, 0, 0, width, height);
                break;
            case KeyPress:
                if (XLookupString(&an_event.xkey, text, 255, &key, 0) == 1) {

                }
                break;
        }
    } while (text[0] != 27); // ESCAPE to exit the loop
}

// Close the display and free the memory
void XClose(){
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

// Puts the BufferDevice content to XImage
void XDump(XImage *ximage, struct BufferDevice *device, struct Palette *palette) {

    int     m, n,
            height = device->ymax,
            width = device->xmax;
    struct Color *color;

    for(m = 0; m < height; m++) {
        for(n = 0; n < width; n++) {
            color = GetColor(device->buffer[m*width+n], palette);
            ximage->data[(m*4)*width+n*4] = (char) round((color->blue)*255);
            ximage->data[(m*4)*width+n*4+1] = (char) round((color->green)*255);
            ximage->data[(m*4)*width+n*4+2] = (char) round((color->red)*255);
            ximage->data[(m*4)*width+n*4+3] = (char) 0;
        }
    }

    XShow();
}

// Set the Universe boundaries
struct Universe * setUniverse(float xmin, float xmax, float ymin, float ymax) {
    struct Universe *universe = (struct Universe *) malloc(sizeof(struct Universe));

    universe->xmin = xmin;
    universe->xmax = xmax;
    universe->ymin = ymin;
    universe->ymax = ymax;

    return universe;
}

struct BufferDevice * createBuffer(int xmax, int ymax){
    struct BufferDevice *device = (struct BufferDevice *) malloc(sizeof(struct BufferDevice));

    device->xmax = xmax;
    device->ymax = ymax;
    device->buffer = (int *) malloc(sizeof(int) * xmax * ymax);
    /*
     * simulate the matrix using:
     *      int offset = i * cols + j; --> row-major ordering
     *      int offset = i + rows * j; --> column-major ordering
     */

    return device;
}

struct Window * createWindow(float xmin, float xmax, float ymin, float ymax){
    struct Window *win = (struct Window *) malloc(sizeof(struct Window));

    win->xmin = xmin;
    win->xmax = xmax;
    win->ymin = ymin;
    win->ymax = ymax;

    return win;
}

// Sistema de Referencia do Universo para Sistema de Referencia Normalizado
struct Point2D * sru2srn(struct Point2D *p, struct Window *win) {
    struct Point2D *normP = (struct Point2D *) malloc(sizeof(struct Point2D));

    normP->x = ( p->x - win->xmin ) / ( win->xmax - win->xmin );
    normP->y = ( p->y - win->ymin ) / ( win->ymax - win->ymin );

    return normP;
}

// Sistema de Referencia Normalizado para Sistema de Referencia do Dispositivo
struct Point2D * srn2srd(struct Point2D *normP, struct BufferDevice *device){
    struct Point2D *deviceP = (struct Point2D *) malloc(sizeof(struct Point2D));

    deviceP->x = round(normP->x * (device->xmax - 1));
    deviceP->y = round(normP->y * (device->ymax - 1));

    return deviceP;
}

// Allocate the memory for Point2D, set the values and returns it
struct Point2D * setPoint(float x, float y, int color) {
    struct Point2D *point = (struct Point2D *) malloc(sizeof(struct Point2D));

    point->x = x;
    point->y = y;
    point->color = color;

    return point;
}

// Create an object based on number of points and allocating those points
struct Object2D * createObject(int numberOfPoints){
    struct Object2D *object = (struct Object2D *) malloc(sizeof(struct Object2D));

    object->numberOfPoints = numberOfPoints;
    object->points = (struct Point2D*) malloc(sizeof(struct Point2D) * numberOfPoints);

    return object;
}

struct Palette * createPalette(int numberOfColors){
    struct Palette *palette = (struct Palette *) malloc(sizeof(struct Palette));

    palette->numberOfColors = numberOfColors;
    palette->colors = (struct Color *) malloc(sizeof(struct Color) * numberOfColors);

    return palette;
}

//TODO: Get Colors
struct Color * GetColor(int point, struct Palette * palette){
//
//    color->red = 1.0;
//    color->green = 1.0;
//    color->blue = 1.0;
//
//    return palette->colors;
}