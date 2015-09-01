#include "../header/structs.h"
#include "../header/base_functions.h"

void init_image(struct Image *img){
    for(int i = 0; i < MAXIMOY; i++)
        for(int j = 0; j < MAXIMOX; j++)
            img->matrix[i][j] = 0;
}

void print_image(struct Image img){
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

struct Image drawLineDDA(struct Point p0, struct Point p1){

    struct Image line;
    init_image(&line);

    double x = p0.x, y = p0.y;
    double deltaX = p1.x - p0.x;
    double deltaY = p1.y - p0.y;

    double m = deltaY / deltaX;
    double error = m - (0.5); // abs(m)

    for(int i = 1; i < deltaX; i++)
    {
        line.matrix[(int)y][(int)x] = 1;

        while( error >= 0 ) {
            y++;
            error--;
        }

        x++;
        error += m;

    }
    return line;
}

struct Image inputLineDDA(char **argv){
    struct Point x0, x1;

    x0.x = atof(argv[2]);
    x0.y = atof(argv[3]);
    x1.x = atof(argv[4]);
    x1.y = atof(argv[5]);

    return drawLineDDA(x0, x1);
}

struct Image inputLineDDA_sru(char **argv){
    struct Point
        p0u = {atof(argv[3]), atof(argv[4])}, p0n, p0d,
        p1u = {atof(argv[5]), atof(argv[6])}, p1n, p1d;

    p0n = sru2srn(p0u, atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]));
    p1n = sru2srn(p1u, atof(argv[7]), atof(argv[8]), atof(argv[9]), atof(argv[10]));

    p0d = srn2srd(p0n);
    p1d = srn2srd(p1n);

    return drawLineDDA(p0d, p1d);
}