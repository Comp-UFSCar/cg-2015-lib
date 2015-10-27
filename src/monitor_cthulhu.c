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

    device = createBuffer(640, 640);

    palette = createPalette(4);
    // black, white, red, green
    addHSVColorToPalette(newHSVColor(0, 0, 0), palette);
    addHSVColorToPalette(newHSVColor(0, 0, 1 * 255), palette);          // 1 * 255 = 100%
    addHSVColorToPalette(newHSVColor(0, 1 * 255, 1 * 255), palette);
    addRGBColorToPalette(newRGBColor(0, 255, 0), palette);

    window1 = createWindow(-10, 0, -10, 0);

    struct Object2D *obj1 = plotCircle(setPoint(-5,-5,1), 1, 30, 1);

    struct Object2D *obj2 = createObject(6);

    setObject(setPoint(-9, -8, 1), obj2);
    setObject(setPoint(-5, -6, 2), obj2);
    setObject(setPoint(-2, -7, 1), obj2);
    setObject(setPoint(-4, -2, 2), obj2);

    setObject2DColor(obj2, 3);

//    scale(obj2, 0.25, 0.25, getCenter(obj2));
//    translate(obj2, -2, -3);
//    rotate(obj2, 0.78, getCenter(obj2));
//    skew(obj2, 0, 0, getCenter(obj2));

//    struct Object2D *obj1 = createObject(3);
//
//    setObject(setPoint(-9, -9, 1), obj1);
//    setObject(setPoint(-5, -1, 1), obj1);
//    setObject(setPoint(-1, -9, 1), obj1);

//    struct Object2D *obj1 = createObject(3);
//
//    setObject(setPoint(-4, -4, 1), obj1);
//    setObject(setPoint(-9, -4, 1), obj1);
//    setObject(setPoint(-9, -9, 1), obj1);
//    setObject(setPoint(-4, -9, 1), obj1);

//    struct Object2D *obj1 = createObject(5);
//
//    setObject(setPoint(-1, -4, 1), obj1);
//    setObject(setPoint(-5, -6, 1), obj1);
//    setObject(setPoint(-9, -4, 1), obj1);
//    setObject(setPoint(-9, -5, 1), obj1);
//    setObject(setPoint(-6, -6, 1), obj1);
//    setObject(setPoint(-4, -7, 1), obj1);


    //obj1 = createCircle(5, 1);

//    struct Object2D *obj1 = plotCircle(setPoint(-5,-5,1), 2, 30, 1);

    //translate(obj1, 5, 0);
//    scale(obj1, 0.1, 0.1, getCenter(obj1));
//    rotate(obj1, 5, getCenter(obj1));
//    //skew(obj1, 0.5, 0.5, getCenter(obj1));
//
//    drawObject(obj1, window1, device);
//    scanFill(obj1, window1, device);

//    for(int i=0; i<device->xmax; i++){
//        for (int j=0; j<device->ymax; j++) {
//            printf("%d", device->buffer[i][j]);
//        }
//        printf("\n");
//    }

//    drawObject(obj1, window1, device);

    struct Matrix3x3 *matTransf = matrix3x3Identity();

    matTransf = matrix3x3Translate(0, 0, *matTransf);
    matTransf = matrix3x3Scale(0.5, 0.5, *getCenter(obj2), *matTransf);
    matTransf = matrix3x3RotateDegrees(90, *getCenter(obj2), *matTransf);
//    matTransf = matrix3x3RotateRadians(0.785, *setPoint(0,0,0), *matTransf);

    matrix3x3TransformPoints(obj2, *matTransf);

    drawObject(obj1, window1, device);
    scanFill(obj1, window1, device);
    drawObject(obj2, window1, device);
    scanFill(obj2, window1, device);

    XDump(device, palette);

    return 0;
}