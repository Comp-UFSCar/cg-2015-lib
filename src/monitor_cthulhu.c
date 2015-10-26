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

    device = createBuffer(640, 640);

    palette = createPalette(3);
    setColor(0, 0, 0, palette);
    setColor(255, 255, 255, palette);
    setColor(255, 0, 0, palette);

    window1 = createWindow(-10, 0, -10, 0);
//    window2 = createWindow(-10, 10, -10, 10);

    struct Object2D *obj1 = plotCircle(setPoint(-5,-5,1), 1, 30, 1);

    struct Object2D *obj2 = createObject(6);

    setObject(setPoint(-9, -8, 1), obj2);
    setObject(setPoint(-5, -6, 1), obj2);
    setObject(setPoint(-2, -7, 1), obj2);
    setObject(setPoint(-4, -2, 1), obj2);

//    scale(obj2, 0.25, 0.25, getCenter(obj2));
//    translate(obj2, -2, -3);
//    rotate(obj2, 0.78, getCenter(obj2));
//    skew(obj2, 0, 0, getCenter(obj2));

//    drawObject(obj1, window1, device);

//    for(int i=0; i<device->xmax; i++){
//        for (int j=0; j<device->ymax; j++) {
//            printf("%d", device->buffer[i][j]);
//        }
//        printf("\n");
//    }

//
//    struct RGBColor *rgbColor = (struct RGBColor *) malloc(sizeof(struct RGBColor));
//
//    rgbColor->red = 0;
//    rgbColor->green = 255;
//    rgbColor->blue = 255;
//
//    printf("\nRGB: %f, %f, %f", rgbColor->red, rgbColor->green, rgbColor->blue);
//
//    struct HSVColor *hsvColor = rgb2hsv(*rgbColor);
//
//    printf("\nHSV: %f, %f, %f", hsvColor->hue, hsvColor->saturation, hsvColor->value);
//
//    rgbColor = hsv2rgb(*hsvColor);
//
//    printf("\nRGB: %f, %f, %f", rgbColor->red, rgbColor->green, rgbColor->blue);
//    printf("\nHSV: %f, %f, %f", hsvColor->hue, hsvColor->saturation, hsvColor->value);

    struct Matrix3x3 *matTransf = matrix3x3Identity();

    matTransf = matrix3x3Translate(0, 0, *matTransf);
    matTransf = matrix3x3Scale(0.5, 0.5, *getCenter(obj2), *matTransf);
    matTransf = matrix3x3RotateDegrees(90, *getCenter(obj2), *matTransf);
//    matTransf = matrix3x3RotateRadians(0.785, *setPoint(0,0,0), *matTransf);

//    for(int j = 0; j < 3; j++) {
//        for(int i = 0; i < 3; i++)
//            printf(" %.2f ",matTransf->mat[i][j]);
//        printf("\n");
//    }

    matrix3x3TransformPoints(obj2, *matTransf);

    drawObject(obj2, window1, device);

    XDump(device, palette);

    return 0;
}