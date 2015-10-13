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
    // Um pixel tem cor, um ponto não?

    struct BufferDevice *device;
    struct Palette *palette;
    struct Window *window1, *window2;

    device = createBuffer(640, 640);

    palette = createPalette(3);
    setColor(0, 0, 0, palette);
    setColor(1, 1, 1, palette);
    setColor(1, 0, 0, palette);

    window1 = createWindow(-10, 0, -10, 0);
//    window2 = createWindow(-50, 50, -50, 50);
    struct Point2D *p1, *p2;

//    p1 = setPoint(-9, -8, 1);
//    p2 = setPoint(-7, -3, 1);

//    struct Object2D *obj1 = createObject(5);
//
//    setObject(setPoint(-9, -8, 1), obj1);
//    setObject(setPoint(-7, -3, 1), obj1);
//    setObject(setPoint(-4, -4, 1), obj1);
//    setObject(setPoint(-3, -6, 1), obj1);
//    setObject(setPoint(-6, -9, 1), obj1);

    struct Object2D *obj1 = createObject(4);

    setObject(setPoint(-5, -5, 1), obj1);
    setObject(setPoint(-9, -3, 1), obj1);
    setObject(setPoint(-4, -4, 1), obj1);
    setObject(setPoint(-3, -10, 1), obj1);

    drawObject(obj1, window1, device);
//    drawObject(obj1, window2, device);

//    drawLine(p1, p2, window2, device, 1);


//    struct Point2D *origin = setPoint(0, 0, 1);
//    struct Object2D *circle, *circle2;
//    circle = plotCircle(origin, 10, 50, 2);
//    circle2 = createCircle(10.0, 1);

//    drawObject(circle, window2, device);
//    drawObject(circle2, window2, device);


//    for(int i=0; i<device->xmax; i++){
//        for (int j=0; j<device->ymax; j++) {
//            printf("%d", device->buffer[i][j]);
//        }
//        printf("\n");
//    }

    XDump(device, palette);

    return 0;
}