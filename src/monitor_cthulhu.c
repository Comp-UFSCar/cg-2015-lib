/** @file monitor_cthulhu.c
 *  @brief main c file containing examples on how to use the lib.
 *
 *  Computer Graphics and Multimedia - UFSCar/Fall 2015
 *
 *                          Prof. Murillo Rodrigo Petrucelli Homem
 *
 *  Students:
 *      Thales Eduardo Adair Menato     407976
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
    struct BufferDevice *device,
            *viewport1,
            *viewport2,
            *viewport3,
            *viewport4;
    struct Palette *palette;
    struct Window 	*window1,
            *window2,
            *window3,
            *window4;

    device = createBuffer(640, 480);

    viewport1 = createBuffer(320, 240);
    viewport2 = createBuffer(320, 240);
    viewport3 = createBuffer(320, 240);
    viewport4 = createBuffer(320, 240);

    // paleta com 6 cores
    palette = createPalette(6);
    addRGBColorToPalette(newRGBColor(0, 0, 0), palette);    // preto
    addRGBColorToPalette(newRGBColor(255, 255, 255), palette);    // branco
    addRGBColorToPalette(newRGBColor(255, 0, 0), palette);  // vermelho
    addRGBColorToPalette(newRGBColor(0, 0, 255), palette);  // azul
    addRGBColorToPalette(newRGBColor(0, 255, 0), palette);  // verde
    addRGBColorToPalette(newRGBColor(255, 255, 0), palette);  // amarelo

    // Poligono que representa a letra A
    struct Object2D *polygonA = createObject2D(6, 2, 2);

    addPoint2DToObject2D(createPoint2D(-6, -1), polygonA);
    addPoint2DToObject2D(createPoint2D(-1, -11), polygonA);
    addPoint2DToObject2D(createPoint2D(-3, -11), polygonA);
    addPoint2DToObject2D(createPoint2D(-4, -9), polygonA);
    addPoint2DToObject2D(createPoint2D(-8, -9), polygonA);
    addPoint2DToObject2D(createPoint2D(-9, -11), polygonA);
    addPoint2DToObject2D(createPoint2D(-11, -11), polygonA);

    // Poligono para fazer a "abertura" na letra
    struct Object2D *polygonCenter = createObject2D(3, 2, 0);

    addPoint2DToObject2D(createPoint2D(-6, -4), polygonCenter);
    addPoint2DToObject2D(createPoint2D(-4, -7.5), polygonCenter);
    addPoint2DToObject2D(createPoint2D(-8, -7.5), polygonCenter);

    // Matriz identidade
    struct Matrix3x3 *matTransf;

    // Janelas de visualização para cada viewport
    window1 = createWindow(-13, -13, 0, 0);
    window2 = createWindow(-9, -9, 5, 5);
    window3 = createWindow(-9, -9, 0, 0);
    window4 = createWindow(-2, -2, 2, 2);

    //VIEWPORT1
    matTransf = matrix3x3Identity();
    matTransf = matrix3x3Scale(0.9, 0.9, *createPoint2D(0,0), *matTransf);
    matrix3x3TransformPoints(polygonA, *matTransf);
    matrix3x3TransformPoints(polygonCenter, *matTransf);

    // Desenha e preenche todos os polígonos
    scanFill(polygonA, window1, viewport1);
    scanFill(polygonCenter, window1, viewport1);
    drawObject(polygonA, window1, viewport1);

    //VIEWPORT2
    setObject2DColor(polygonA, 1, 1); // define a cor Branca para o polígono
    matTransf = matrix3x3Identity();
    matTransf = matrix3x3Scale(0.9, 0.9, *createPoint2D(0,0), *matTransf);
    matTransf = matrix3x3Translate(2, 2, *matTransf);
    matrix3x3TransformPoints(polygonA, *matTransf);
    matrix3x3TransformPoints(polygonCenter, *matTransf);

    skew(polygonA, 0.25, 0, getCenter(polygonA));
    skew(polygonCenter, 0.25, 0, getCenter(polygonCenter));

    scanFill(polygonA, window2, viewport2); 	// Preenchimento extra
    scanFill(polygonCenter, window2, viewport2); 	// Preenchimento extra

    drawObject(polygonA, window2, viewport2);


    //VIEWPORT3
    setObject2DColor(polygonA, 3, 3); // define a cor Azul para o polígono
    matTransf = matrix3x3Identity();
    matTransf = matrix3x3Scale(0.6, 0.6, *createPoint2D(0,0), *matTransf);
    matTransf = matrix3x3Translate(-3, -2, *matTransf);
    matrix3x3TransformPoints(polygonA, *matTransf);
    matrix3x3TransformPoints(polygonCenter, *matTransf);

    skew(polygonA, -0.9, 0, getCenter(polygonA));
    skew(polygonCenter, -0.9, 0, getCenter(polygonCenter));

    scanFill(polygonA, window3, viewport3);
    scanFill(polygonCenter, window3, viewport3);

    drawObject(polygonA, window3, viewport3);


    //VIEWPORT4
    setObject2DColor(polygonA, 4, 4);	// define a cor Verde
    matTransf = matrix3x3Identity();
    matTransf = matrix3x3Scale(0.5, 0.2, *createPoint2D(0,0), *matTransf);
    matTransf = matrix3x3Translate(-2, 0, *matTransf);
    matrix3x3TransformPoints(polygonA, *matTransf); // aplica transf. no pol1
    matrix3x3TransformPoints(polygonCenter, *matTransf); // aplica transf. no pol1

    scanFill(polygonA, window4, viewport4); 	// Preenchimento extra
    scanFill(polygonCenter, window4, viewport4); 	// Preenchimento extra

    drawObject(polygonA, window4, viewport4);

    // Passa a informação das viewports para o device
    for(int i = 0; i < 320; i++){
        for(int j = 0; j < 240; j++){
            device->buffer[j][i] = viewport1->buffer[j][i];
            device->buffer[j+240][i] = viewport2->buffer[j][i];
            device->buffer[j][i+320] = viewport3->buffer[j][i];
            device->buffer[j+240][i+320] = viewport4->buffer[j][i];
        }
    }

    /*
    	O nome da função que estamos utilizando para geração da forma itálica se chama: skew
    */

    XDump(device, palette);

    return 0;

    /*
        Resposta da pergunta opcional:

        Todas as ferramentas de computação acabam com o tempo.
        Sim, aprender os conceitos fundamentais nos permite entender e utilizar qualquer ferramenta,
        além de criar novas tecnologias.

    */

}