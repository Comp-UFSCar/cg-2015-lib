/* Computer Graphics and Multimedia - UFSCar/Fall 2015
 *
 * First Activity
 *
 * Student: Thales Eduardo Adair Menato
 *
 * Instruction: to run this file, use command 'make' on this directory.
 */

#include "first_activity.h"

int main() {

    world_xmin = -20;
    world_ymin = -20;
    world_xmax = 10;
    world_ymax = 15;

    struct BufferDevice *device;
    struct Palette *palette;
    struct Window *window;

    device = createBuffer(640, 640);    // utilizando matriz quadrada pois retangular esta com problema

    // Palette with 3 colors
    palette = createPalette(3);
    setColor(1, 1, 1, palette); // black
    setColor(1, 0, 0, palette); // red
    setColor(0, 0, 1, palette); // blue

    // windows with points min(-8,-7), max(5,5)
//    window = createWindow(-8, 5, -7, 5);
    // Como é classificado o dispositivo de saída que você está utilizando? por que?

    // A janela de visualização está adequada para desenhar o objeto por completo, senão, qual janela poderia ser utilizada.

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