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
 *      Marcelo Lopes Lotufo            407933
 *
 *  If you're compiling manually using gcc don't forget to add the flags:
 *      -lm -lX11 -std=c99
 */

#include "../header/monitor_cthulhu.h"

int main(int argc, char *argv[]) {

    // limites extremos
    world_xmin = -20;
    world_ymin = -20;
    world_xmax = 10;
    world_ymax = 15;

    // definição das estruturas estão dentro do arquivo header/structs.h
    struct BufferDevice *device;
    struct Palette *palette;
    struct Window *window1, *window2;
    struct Matrix3x3 *matTransf = matrix3x3Identity();

    device = createBuffer(640, 480);

    // paleta com 6 cores
    palette = createPalette(7);
    addRGBColorToPalette(newRGBColor(0, 0, 0), palette);    // preto
    addRGBColorToPalette(newRGBColor(255, 0, 0), palette);  // vermelho
    addRGBColorToPalette(newRGBColor(0, 0, 255), palette);  // azul

    // Janela de visualização ideal para este caso
    window1 = createWindow(-10, -10, 0, 0);

    struct Object2D *polygon1 = createObject2D(5, 1, 1);
    struct Object2D *polygon2 = createObject2D(4, 2, 2);

    addPoint2DToObject2D(createPoint2D(-7, -3), polygon1);
    addPoint2DToObject2D(createPoint2D(-4, -4), polygon1);
    addPoint2DToObject2D(createPoint2D(-3, -6), polygon1);
    addPoint2DToObject2D(createPoint2D(-6, -9), polygon1);
    addPoint2DToObject2D(createPoint2D(-9, -8), polygon1);

    addPoint2DToObject2D(createPoint2D(-1, -2), polygon2);
    addPoint2DToObject2D(createPoint2D(-1, -6), polygon2);
    addPoint2DToObject2D(createPoint2D(-6, -6), polygon2);
    addPoint2DToObject2D(createPoint2D(-6, -2), polygon2);

    // criacao do poligono 3 com mesmas informacoes do poligono 1 - exerc. a
    struct Object2D *polygon3 = getObject2DClone(polygon1);

    // rotacao de 45 graus no eixo (0,0)
    matTransf = matrix3x3RotateDegrees(45, *createPoint2D(0,0), *matTransf);

    // usar a matriz transformacao no poligono 3
    matrix3x3TransformPoints(polygon3, *matTransf);

    // modificar as cores
    addHSVColorToPalette(newHSVColor(261, 0.87 * 255, 0.5 * 255), palette); // (H = 261º , S = 87%, V = 50%)
    addHSVColorToPalette(newHSVColor(355, 0.89 * 255, 0.43 * 255), palette); // (H = 355º, S = 89%, V = 43%)
    addHSVColorToPalette(newHSVColor(129, 0.70 * 255, 0.46 * 255), palette); // (H = 129º, S = 70%, V = 46%)

    setObject2DColor(polygon1, 3, 3);
    setObject2DColor(polygon2, 4, 4);
    setObject2DColor(polygon3, 5, 5);

    window2 = createWindow(-10, -13, 5, 5);

    drawObject(polygon1, window2, device);
    drawObject(polygon2, window2, device);
    drawObject(polygon3, window2, device);

    XDump(device, palette);

    return 0;

}