/*
 * #################################################################################################################
 * Computer Graphics and Multimedia - UFSCar/Fall 2015
 * Prof. Murillo Rodrigo Petrucelli Homem
 * Student: Thales Eduardo Adair Menato - 407976
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

    device = createBuffer(1024, 768);
    palette = createPalette(3);

    if (XInit(device) == True) {

        struct Window *window1 = createWindow(0, 1024, 0, 768);

        struct Point2D p1 = {10, 20};
        struct Point2D p2 = {250, 250};

        drawLine(&p1, &p2, window1, device, 255);

        XDump(ximage, device, palette);

        XClose();
    }

    return 0;
}