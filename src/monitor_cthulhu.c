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
    //region XInterface
    if (init_x() == True) {

        struct Image img;
        init_image(&img);

        struct Point p1 = {10, 20};
        struct Point p2 = {250, 250};

        img = drawLine(p1, p2);

        XDump(ximage, img);

        // main loop
        show_x();

        close_x();
    }
    //endregion

    return 0;
}