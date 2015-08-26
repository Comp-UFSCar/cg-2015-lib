#ifndef FUNCTIONS_LIB_H
#define FUNCTIONS_LIB_H

void XDump(XImage *ximage) {
  int m, n, height, width;
  struct Color * cor;
  width = MAXIMOX;
  height = MAXIMOY;

  // pintar apenas onde estiver preenchido - valor da matriz
  cor = (struct Color *) malloc(sizeof(struct Color)); 
  cor->red = 0.0;
  cor->green = 0.0;
  cor->blue = 0.0;

  // modificar essa estrutura para matriz de entrada
  for(m=0;m<height;m++) {
    for(n=0;n<width;n++) {
      ximage -> data[(m*4)*width+n*4] = (char) round((cor->blue)*255);
      ximage -> data[(m*4)*width+n*4+1] = (char) round((cor->green)*255);
      ximage -> data[(m*4)*width+n*4+2] = (char) round((cor->red)*255);
      ximage -> data[(m*4)*width+n*4+3] = (char) 0;
      }
    }
}

//TODO: SRU 2 SRN

/*
	mcx = ( x - xmin ) / ( xmax - xmin )
	mcy = ( y - ymin ) / ( ymax - ymin )
*/

//TODO: SRN 2 SRD

/*
	dcx = round(mcx * (mdh - 1))	// mdh - qtd entradas altura
	dcy = round(mcy * (mdv - 1))	// mdv - qtd entradas largura
*/

//TODO: drawLine using Bresenham's Line Algorithm
/*  pseudocode from Wikipedia
 *  function line(x0, y0, x1, y1)
     real deltax := x1 - x0
     real deltay := y1 - y0
     real error := 0
     real deltaerr := abs (deltay / deltax)    // Assume deltax != 0 (line is not vertical),
           // note that this division needs to be done in a way that preserves the fractional part
     int y := y0
     for x from x0 to x1
         plot(x,y)
         error := error + deltaerr
         while error ≥ 0.5 then
             plot(x, y)
             y := y + sign(y1 - y0)
             error := error - 1.0
 */


#endif