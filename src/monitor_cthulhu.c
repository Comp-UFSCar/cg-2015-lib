/*
 * #################################################################################################################
 * Computer Graphics and Multimedia - UFSCar/Fall 2015
 * Prof. Murillo Rodrigo Petrucelli Homem
 * Students:
 *      Thales Eduardo Adair Menato     407976
 *      Daniel Nobusada                 344443
 * #################################################################################################################
 * References:
 * http://math.msu.su/~vvb/2course/Borisenko/CppProjects/GWindow/xintro.html#vars
 * http://www.linuxjournal.com/files/linuxjournal.com/linuxjournal/articles/048/4879/4879l1.html
 * #################################################################################################################
 * If you're compiling manually using gcc don't forget to add the flags: -lm -lX11 -std=c99
 */

#include "../header/monitor_cthulhu.h"
#include "../header/base_functions.h"
#include "../header/line.h"

int main(int argc, char *argv[]) {

    struct BufferDevice *device;
    struct Palette *palette;
    struct Window *window1;

    device = createBuffer(640, 480);

    palette = createPalette(2);
    setColor(0, 0, 0, palette);
    setColor(1, 1, 1, palette);

    window1 = createWindow(-10, 10, -10, 10);

    struct Point2D *p1, *p2;

    p1 = setPoint(-5, -5, 1);
    p2 = setPoint(5, 5, 1);

//    drawLine(p1, p2, window1, device, 1);


    struct Object2D *circle;
    circle = createCircle(5.0, 1);
    drawObject(circle, window1, device);

    struct Point2D *origin;
    origin = setPoint(200, 50, 0);

//    plotCircle(origin, 10, device, 1);

    XDump(device, palette);

    return 0;
}