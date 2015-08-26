//	Computer Graphics and Multimedia - UFSCar/Fall 2015
//	Prof. Murillo Rodrigo Petrucelli Homem
//	Student: Thales Eduardo Adair Menato - 407976

//TODO: Compilation description using make

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include "../lib/structs_lib.h"
#include "../lib/functions_lib.h"

#define EventMask (KeyPressMask | ExposureMask)

int main(int argc, char *argv[]) {

	// TODO: trabalhar input do codigo
	if(argc > 1)
		printf("\n%s\n", argv[1]);

	Display               * display;
	XImage                * ximage;
	Window                window;
	XEvent                an_event;
	GC                    gc;
	Visual                * visual;
	XGCValues             values;
	int                   screen, dplanes;
	int                   height, width, ret = 1;

	width = MAXIMOX;
	height = MAXIMOY;
	
	if ((display = XOpenDisplay(NULL)) == NULL) ret = 0;
	else {  
		screen = DefaultScreen(display);
		dplanes = DisplayPlanes(display,screen);   
		visual = XDefaultVisual(display,screen);
	
		if (!(window=XCreateSimpleWindow(display,RootWindow(display,screen),0,0,width,height,1,BlackPixel(display,screen),WhitePixel(display,screen)))) ret = 0;
		else {
			XSelectInput(display, window, EventMask);
			XStoreName(display, window, "Monitor Virtual");
			gc = XCreateGC(display, window, 0, &values);
	
			XMapWindow(display,window);
			XSync(display,False);
	
			ximage = XCreateImage(display,visual,dplanes,ZPixmap,0,malloc(width*height*sizeof(int)),width,height,8,0);

            XDump(ximage);

			/* Trata os eventos */
			while(1) {
			XNextEvent(display, &an_event);
				switch(an_event.type) {
					case Expose:
						XPutImage(display,window,gc,ximage,0,0,0,0,width,height);
						break;
					
					/* outros eventos ... */
				}
			}
		}
	}
	return 0;
}
	

