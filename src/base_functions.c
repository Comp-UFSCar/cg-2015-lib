#include "../header/structs.h"
#include "../header/base_functions.h"

int init_x(){
    height = MAXIMOY;
    width = MAXIMOX;
    ret = True;

    if ((display = XOpenDisplay(NULL)) == NULL)
        ret = False;

    else {
        screen = DefaultScreen(display);
        dplanes = DisplayPlanes(display, screen);
        visual = XDefaultVisual(display, screen);

        if (!(window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, width, height, 1,
                                           BlackPixel(display, screen), WhitePixel(display, screen))))
            ret = False;

        else {
            XSelectInput(display, window, EventMask);
            XStoreName(display, window, "Monitor Cthulhu ^(;.;)^");
            gc = XCreateGC(display, window, 0, &values);

            XMapWindow(display, window);
            XSync(display, False);

            // variables
            ximage = XCreateImage(display, visual, dplanes, ZPixmap, 0, malloc(width * height * sizeof(int)), width,
                                  height, 8, 0);
        }
    }
    return ret;
}

void show_x(){
    char text[255];
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
}

void close_x(){
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

void init_image(struct Image *img){
    for(int i = 0; i < MAXIMOY; i++)
        for(int j = 0; j < MAXIMOX; j++)
            img->matrix[i][j] = 0;
}

void debug_image(struct Image img){
    for(int i = 0; i < MAXIMOY; i++){
        for(int j = 0; j < MAXIMOX; j++){
            printf("%d", img.matrix[i][j]);
        }
        printf("\n");
    }
}

void XDump(XImage *ximage, struct Image img) {
    int m, n, height = MAXIMOY, width = MAXIMOX;
    struct Color * cor;

    cor = (struct Color *) malloc(sizeof(struct Color));
    cor->red = 1.0;
    cor->green = 1.0;
    cor->blue = 1.0;

    for(m=0;m<height;m++) {
        for(n=0;n<width;n++) {
            if(img.matrix[m][n] > 0) {
                ximage -> data[(m*4)*width+n*4] = (char) 0;
                ximage -> data[(m*4)*width+n*4+1] = (char) 0;
                ximage -> data[(m*4)*width+n*4+2] = (char) 0;
                ximage -> data[(m*4)*width+n*4+3] = (char) 0;
            }
            else {
                ximage -> data[(m*4)*width+n*4] = (char) round((cor->blue)*255);
                ximage -> data[(m*4)*width+n*4+1] = (char) round((cor->green)*255);
                ximage -> data[(m*4)*width+n*4+2] = (char) round((cor->red)*255);
                ximage -> data[(m*4)*width+n*4+3] = (char) 0;
            }
        }
    }
}

// Sistema de Referencia do Universo para Sistema de Referencia Normalizado
struct Point sru2srn(struct Point p, double xmin, double ymin, double xmax, double ymax) {
    struct Point mc;

    mc.x = ( p.x - xmin ) / ( xmax - xmin );
    mc.y = ( p.y - ymin ) / ( ymax - ymin );

    return mc;
}

// Sistema de Referencia Normalizado para Sistema de Referencia do Dispositivo
struct Point srn2srd(struct Point mc){
    struct Point dc;

    dc.x = round(mc.x * (MAXIMOX - 1));
    dc.y = round(mc.y * (MAXIMOY - 1));

    return dc;
}