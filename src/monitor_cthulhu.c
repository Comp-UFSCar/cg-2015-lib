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
#include "../header/console_input.h"
#include "../header/base_functions.h"

// Global variables
Display * display;
Window window;
GC gc;
Visual * visual;
XGCValues values;
int screen, dplanes, height = MAXIMOY, width = MAXIMOX, ret = TRUE;

int init_x(){
    if ((display = XOpenDisplay(NULL)) == NULL)
        ret = FALSE;

    else {
        screen = DefaultScreen(display);
        dplanes = DisplayPlanes(display, screen);
        visual = XDefaultVisual(display, screen);

        if (!(window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, width, height, 1,
                                           BlackPixel(display, screen), WhitePixel(display, screen))))
            ret = FALSE;

        else {
            XSelectInput(display, window, EventMask);
            XStoreName(display, window, "Monitor Cthulhu ^(;.;)^");
            gc = XCreateGC(display, window, 0, &values);

            XMapWindow(display, window);
            XSync(display, False);
        }
    }
    return ret;
}

void close_x(){
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

int main(int argc, char *argv[]) {
    int input = FALSE;

    if(argc > 1)
        input = TRUE;
    else
        print_help_menu();

    //region XInterface
    if (init_x() == TRUE && input == TRUE) {

        // variables
        XImage *ximage;
        ximage = XCreateImage(display, visual, dplanes, ZPixmap, 0, malloc(width * height * sizeof(int)), width,
                              height, 8, 0);
        XEvent an_event;
        KeySym key;

        struct Image img;
        init_image(&img);

        // parse the user input
        switch(input_parser(argc, argv)){
            case LINE_DDA:
                img = inputLineDDA(argv);
                break;
            case LINE_DDA_SRU:
                img = inputLineDDA_sru(argv);
                break;
            case INPUT_MISTAKE:
                input = FALSE;
                break;
            case INPUT_ERROR:
                input = FALSE;
                print_help_menu();
                break;
        };

        XDump(ximage, img);

        char text[255];
        if(input == TRUE)
            do {
                XNextEvent(display, &an_event);
                switch (an_event.type) {
                    case Expose:
                        XPutImage(display, window, gc, ximage, 0, 0, 0, 0, width, height);
                        break;
                    case KeyPress:
                        if (XLookupString(&an_event.xkey, text, 255, &key, 0) == 1) {

                        }
                        break;
                }
            } while (text[0] != 27); // ESCAPE to exit the loop

        close_x();
    }
    //endregion

    return 0;
}