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
    struct Window *window1, *window2;

    device = createBuffer(640, 480);

    palette = createPalette(3);
    setColor(0, 0, 0, palette);
    setColor(1, 1, 1, palette);
    setColor(1, 0, 0, palette);

    window1 = createWindow(-10, 0, -10, 0);
    window2 = createWindow(-10, 10, -10, 10);

//    struct Object2D *obj1 = createObject(6);

//    setObject(setPoint(-9, -9, 1), obj1);
//    setObject(setPoint(-5, -1, 1), obj1);
//    setObject(setPoint(-1, -9, 1), obj1);

//    obj1 = createCircle(5, 1);

    struct Object2D *obj1 = plotCircle(setPoint(-5,-5,1), 2, 30, 1);

    drawObject(obj1, window1, device);

//    for(int i=0; i<device->xmax; i++){
//        for (int j=0; j<device->ymax; j++) {
//            printf("%d", device->buffer[i][j]);
//        }
//        printf("\n");
//    }

    XDump(device, palette);

    return 0;
}