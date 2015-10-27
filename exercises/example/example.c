/* Computer Graphics and Multimedia - UFSCar/Fall 2015
 *
 * First Activity
 *
 * Student: Thales Eduardo Adair Menato - 407976
 *
 * Instruction: to run this file, use command 'make' on this directory.
 */

#include "example.h"

/*
 * Obs: A documentação das funções da biblioteca está contida dentro dos arquivos
 *      de cabeçalho na pasta 'header', o arquivo .c correspondente está dentro da
 *      pasta 'src'.
 */

int main() {

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
    window1 = createWindow(-10, 0, -10, 0);

    struct Object2D *polygon1 = createObject(5);
    struct Object2D *polygon2 = createObject(4);

    setObject(setPoint(-7, -3, 1), polygon1);
    setObject(setPoint(-4, -4, 1), polygon1);
    setObject(setPoint(-3, -6, 1), polygon1);
    setObject(setPoint(-6, -9, 1), polygon1);
    setObject(setPoint(-9, -8, 1), polygon1);

    setObject(setPoint(-1, -2, 2), polygon2);
    setObject(setPoint(-1, -6, 2), polygon2);
    setObject(setPoint(-6, -6, 2), polygon2);
    setObject(setPoint(-6, -2, 2), polygon2);

    // criacao do poligono 3 com mesmas informacoes do poligono 1 - exerc. a
    struct Object2D *polygon3 = createObject(polygon1->max_points);

    for(int i = 0; i < polygon1->curr_point; i++) {
        setObject(setPoint(polygon1->points[i].x, polygon1->points[i].y, polygon1->points[i].color),
                  polygon3);
    }
    // rotacao de 45 graus no eixo (0,0)
    matTransf = matrix3x3RotateDegrees(45, *setPoint(0,0,0), *matTransf);

    // usar a matriz transformacao no poligono 3
    matrix3x3TransformPoints(polygon3, *matTransf);

    // modificar as cores
    addHSVColorToPalette(newHSVColor(261, 0.87 * 255, 0.5 * 255), palette); // (H = 261º , S = 87%, V = 50%)
    addHSVColorToPalette(newHSVColor(355, 0.89 * 255, 0.43 * 255), palette); // (H = 355º, S = 89%, V = 43%)
    addHSVColorToPalette(newHSVColor(129, 0.70 * 255, 0.46 * 255), palette); // (H = 129º, S = 70%, V = 46%)

    setObject2DColor(polygon1, 3);
    setObject2DColor(polygon2, 4);
    setObject2DColor(polygon3, 5);

    window2 = createWindow(-10, 5, -13, 5);

    drawObject(polygon1, window2, device);
    drawObject(polygon2, window2, device);
    drawObject(polygon3, window2, device);

    XDump(device, palette);

    return 0;

}