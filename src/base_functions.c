/** @file base_function.c
 *  @brief Base Functions for the library.
 *
 *  @author Thales Menato (thamenato)
 *  @author Daniel Nobusada (nobusada)
 *
 */

#include "../header/base_functions.h"

/*
 * Creates a virtual device and displays the BufferDevice content on it.
 */
int XDump(struct BufferDevice *device, struct Palette *palette) {

    Display *display;
    XImage *ximage;
    Window window;
    XEvent an_event;
    GC gc;
    Visual *visual;
    XGCValues values;
    int m, n, screen, dplanes;
    int width, height;
    struct RGBColor *color;

    width = device->xmax;
    height = device->ymax;

    if ((display = XOpenDisplay(NULL)) == NULL)
        return False;
    else {
        screen = DefaultScreen(display);
        dplanes = DisplayPlanes(display, screen);
        visual = XDefaultVisual(display, screen);

        if (!(window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, width, height, 1,
                                           BlackPixel(display, screen), WhitePixel(display, screen))))
            return False;
        else {
            XSelectInput(display, window, EventMask);
            XStoreName(display, window, "^(;,;)^ Monitor Cthulhu ^(;,;)^");
            gc = XCreateGC(display, window, 0, &values);

            XMapWindow(display, window);
            XSync(display, False);

            ximage = XCreateImage(display, visual, dplanes, ZPixmap, 0,
                                  malloc(width * height * sizeof(int)), width, height, 8, 0);

            for (m = 0; m < height; m++) {
                for (n = 0; n < width; n++) {
                    color = getColor(device->buffer[m][n], palette);
                    ximage->data[(m * 4) * width + n * 4] = (char) round((color->blue));
                    ximage->data[(m * 4) * width + n * 4 + 1] = (char) round((color->green));
                    ximage->data[(m * 4) * width + n * 4 + 2] = (char) round((color->red));
                    ximage->data[(m * 4) * width + n * 4 + 3] = (char) 0;
                }
            }

            XPutImage(display, window, gc, ximage, 0, 0, 0, 0, width, height);

            KeySym key;
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

            XFreeGC(display, gc);
            XDestroyWindow(display, window);
            XCloseDisplay(display);
        }
    }
    return True;
}

/*
 * Set the World values.
 */
void setWorld(float xmin, float xmax, float ymin, float ymax) {
    world_xmin = xmin;
    world_xmax = xmax;
    world_ymin = ymin;
    world_ymax = ymax;
}

/*
 * Allocates the memory for BufferDevice based on parameters.
 */
struct BufferDevice *createBuffer(int xmax, int ymax) {
    struct BufferDevice *device = (struct BufferDevice *) malloc(sizeof(struct BufferDevice *));

    device->xmax = xmax;
    device->ymax = ymax;

    device->buffer = (int **) malloc(ymax * sizeof(int *));
    for (int i = 0; i < ymax; i++)
        device->buffer[i] = (int *) malloc(xmax * sizeof(int));

    /*
     * simulate the matrix using:
     *      int offset = i * cols + j; --> row-major ordering
     *      int offset = i + rows * j; --> column-major ordering
     */

    return device;
}

/*
 * Allocates the memory for Window and set parameters.
 */
struct Window *createWindow(float xmin, float xmax, float ymin, float ymax) {
    struct Window *win = (struct Window *) malloc(sizeof(struct Window *));

    win->xmin = xmin;
    win->xmax = xmax;
    win->ymin = ymin;
    win->ymax = ymax;

    return win;
}

/*
 * Normalizes Point2D from Universe to Window.
 */
struct Point2D *sru2srn(struct Point2D *p, struct Window *win) {
    struct Point2D *normP = (struct Point2D *) malloc(sizeof(struct Point2D *));

    normP->x = (p->x - win->xmin) / (win->xmax - win->xmin);
    normP->y = (p->y - win->ymin) / (win->ymax - win->ymin);

    return normP;
}

/*
 * Normalized Point2D to BufferDevice position.
 */
struct Point2D *srn2srd(struct Point2D *normP, struct BufferDevice *device) {
    struct Point2D *deviceP = (struct Point2D *) malloc(sizeof(struct Point2D *));

    deviceP->x = round(normP->x * (device->xmax - 1));
    deviceP->y = round(normP->y * (device->ymax - 1));

    return deviceP;
}

/*
 * Allocates memory and set values for Point2D members.
 */
struct Point2D *setPoint(double x, double y, int color) {
    struct Point2D *point = (struct Point2D *) malloc(sizeof(struct Point2D *));

    point->x = x;
    point->y = y;
    point->color = color;

    return point;
}

/*
 * Creates an Object2D allocating it's memory based on number of points.
 */
struct Object2D *createObject(int max_points) {
    struct Object2D *object = (struct Object2D *) malloc(sizeof(struct Object2D *));

    object->max_points = max_points;
    object->curr_point = 0;
    object->points = (struct Point2D *) malloc(sizeof(struct Point2D) * max_points);

    return object;
}

//TODO Documentacao do setObject
int setObject(struct Point2D *p, struct Object2D *obj) {
    if (obj->curr_point > obj->max_points)
        return False;

    obj->points[obj->curr_point] = *p;
    obj->curr_point++;
    return True;
}


//TODO documentacao do changeColor
struct Object2D *changeColor(struct Object2D *object, int color) {
    struct Object2D *clone = createObject(object->max_points);

    for (int i = 0; i < object->curr_point; i++) {
        clone->points[i] = object->points[i];
        clone->points[i].color = color;
    }

    return clone;
}

/*
 * Create a Palette with parameter number of colors.
 */
struct Palette *createPalette(int numberOfColors) {
    struct Palette *palette = (struct Palette *) malloc(sizeof(struct Palette *));

    palette->numberOfColors = numberOfColors;
    palette->currentColor = 0;
    palette->colors = (struct RGBColor *) malloc(sizeof(struct RGBColor) * numberOfColors);

    return palette;
}

/*
 * Set a new color to a Palette.
 */
int setColor(float red, float green, float blue, struct Palette *palette) {
    if (palette->currentColor >= palette->numberOfColors)
        return False;

    palette->colors[palette->currentColor].red = red;
    palette->colors[palette->currentColor].green = green;
    palette->colors[palette->currentColor].blue = blue;

    palette->currentColor++;

    return True;
}

/*
 * Get a RGBColor from Palette.
 */
struct RGBColor *getColor(int colorNumber, struct Palette *palette) {

    return &palette->colors[colorNumber];
}

/*
 * Based on https://gist.github.com/yoggy/8999625#file-rgb2hsv-cpp-L13
 */
struct HSVColor *rgb2hsv(struct RGBColor rgbColor) {

    float   r = rgbColor.red / 255.0f,
            g = rgbColor.green / 255.0f,
            b = rgbColor.blue / 255.0f,
            min, max, h, s, v;

    struct HSVColor *hsvColor = (struct HSVColor *) malloc(sizeof(struct HSVColor));

    max = fmaxf(r, fmaxf(g, b));
    min = fminf(r, fminf(g, b));

    v = max;

    if (max == 0.0f) {
        s = 0;
        h = 0;
    }
    else if (max - min == 0.0f) {
        s = 0;
        h = 0;
    }
    else {
        s = (max - min) / max;

        if (max == r) {
            h = 60 * ((g - b) / (max - min)) + 0;
        }
        else if (max == g) {
            h = 60 * ((b - r) / (max - min)) + 120;
        }
        else {
            h = 60 * ((r - g) / (max - min)) + 240;
        }
    }

    if (h < 0) h += 360.0f;

    hsvColor->hue = h/2;                // 0 - 180
    hsvColor->saturation = s * 255;     // 0 - 255
    hsvColor->value = v * 255;          // 0 - 255

    return hsvColor;
}

/*
 * Based on https://gist.github.com/yoggy/8999625#file-rgb2hsv-cpp-L55
 */
struct RGBColor *hsv2rgb(struct HSVColor hsvColor) {
    struct RGBColor *rgbColor = (struct RGBColor *) malloc(sizeof(struct RGBColor));

    float   h = hsvColor.hue * 2.0f,
            s = hsvColor.saturation / 255.0f,
            v = hsvColor.value / 255.0f;

    float r, g, b;

    int   hi = (int)(h / 60.0f) % 6;
    float f  = (h / 60.0f) - hi;
    float p  = v * (1.0f - s);
    float q  = v * (1.0f - s * f);
    float t  = v * (1.0f - s * (1.0f - f));

    switch(hi) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
        default: r = 0, g = 0, b = 0; break;
    }

    rgbColor->red = r * 255;
    rgbColor->green = g * 255;
    rgbColor->blue = b * 255;
    return rgbColor;
}
