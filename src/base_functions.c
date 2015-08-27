#include "../header/base_functions.h"

void init_image(struct Image *img){
    for(int i = 0; i < MAXIMOX; i++)
        for(int j = 0; j < MAXIMOY; j++)
            img->matrix[i][j] = 0;
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

//TODO: drawLine using Bresenham's Line Algorithm
struct Image drawLine_Bresenham(struct Point p0, struct Point p1){

    struct Image line;
    init_image(&line);

    double x = p0.x, y = p0.y;
    double deltaX = p1.x - p0.x;
    double deltaY = p1.y - p0.y;

    double m = deltaY / deltaX;
    double error = m - (1.0/2.0); // abs(m)

    for(int i = 1; i < deltaX; i++)
    {
        // escreve na matriz
        // desenha(x, y)

        while( error >= 0 ) {
            y++;
            error--;
        }

        x++;
        error += m;

    }

//  pseudocode from Wikipedia
// *  function line(x0, y0, x1, y1)
//     real deltax := x1 - x0
//     real deltay := y1 - y0
//     real error := 0
//     real deltaerr := abs (deltay / deltax)    // Assume deltax != 0 (line is not vertical),
//           // note that this division needs to be done in a way that preserves the fractional part
//     int y := y0
//     for x from x0 to x1
//         plot(x,y)
//         error := error + deltaerr
//         while error ≥ 0.5 then
//             plot(x, y)
//             y := y + sign(y1 - y0)
//             error := error - 1.0

}

