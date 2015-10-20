/* Computer Graphics and Multimedia - UFSCar/Fall 2015
 *
 * First Activity
 *
 * Student: Thales Eduardo Adair Menato - 407976
 *
 * Instruction: to run this file, use command 'make' on this directory.
 */

#include "first_activity.h"

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
    struct Window *window;

    device = createBuffer(640, 480);

    // paleta com 3 cores
    palette = createPalette(3);
    setColor(0, 0, 0, palette); // preto
    setColor(1, 0, 0, palette); // vermelho
    setColor(0, 0, 1, palette); // azul


/*
 *  P: Como é classificado o dispositivo de saída que você está utilizando? Por que?
 *
 *  R: O dispositivo de saída (struct BufferDevice), é classificado como matricial.
 *      Funciona como um "frame buffer" onde a imagem a ser exibida é armazenada
 *      na forma de uma matriz de valores, onde cada valor representa uma cor da paleta.
 *
 *  P: A janela de visualização está adequada para desenhar o objeto por completo, senão,
 *  qual janela poderia ser utilizada.
 *
 *  R: Ela não está adequada, as extremidades da janela não abrangem todos os pontos dos
 *      polígonos, portanto uma parte do mesmo está "fora" da janela de visualização.
 *      Uma janela ideal seria utilizar os valores que já estão na grade min(-10, -10) e
 *      max(10,10).
 */

//    windows with points min(-8,-7), max(5,5)
//    window = createWindow(-8, 5, -7, 5);

    // Janela de visualização ideal para este caso
    window = createWindow(-10, 0, -10, 0);

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

    drawObject(polygon1, window, device);
    drawObject(polygon2, window, device);

    XDump(device, palette);

    return 0;

}