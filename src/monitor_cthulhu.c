/** @file monitor_cthulhu.c
 *  @brief main c file containing examples on how to use the lib.
 *
 *  Computer Graphics and Multimedia - UFSCar/Fall 2015
 *
 *                          Prof. Murillo Rodrigo Petrucelli Homem
 *
 *  Students:
 *      Thales Eduardo Adair Menato     407976
 *      Daniel Nobusada                 344443
 *
 *  If you're compiling manually using gcc don't forget to add the flags:
 *      -lm -lX11 -std=c99
 */

#include "../header/monitor_cthulhu.h"

int main(int argc, char *argv[]) {

    struct BufferDevice *device;
    struct Palette *palette;
    struct Window *window1;

    device = createBuffer(500, 500);

    palette = createPalette(3);
    setColor(0, 0, 0, palette);
    setColor(1, 1, 1, palette);
    setColor(1, 0, 0, palette);

    window1 = createWindow(-10, 10, -10, 10);

//    drawObject(obj1, window1, device);
    struct Point2D *p1, *p2;

    struct Object2D *pol;
//    p1 = setPoint(-50, -50, 1);
//    p2 = setPoint(25, 25, 1);

//    drawLine(p1, p2, window1, device, 1);


    struct Point2D *origin = setPoint(-5, -5, 1);
    struct Object2D *circle, *circle2;
//    circle = plotCircle(origin, 1, 5, 2);
    circle2 = createCircle(10, 1);

//    drawObject(circle, window1, device);
    drawObject(circle2, window1, device);


    XDump(device, palette);

    return 0;
}