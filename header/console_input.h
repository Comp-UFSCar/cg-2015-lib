#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include<stdio.h>
#include<stdlib.h>

#define INPUT_ERROR -2
#define INPUT_MISTAKE -1
#define LINE_BRESENHAM 0
#define LINE_BRESENHAM_SRU 1

#define LINE_BRESENHAM_INCORRECT "\nIncorrect usage. To use '-line_bresenham' you must follow:\n" \
                                "\t-line_bresenham x0 y0 x1 y1\n" \
                                "All numbers must be integers\n\n"

#define LINE_BRESENHAM_SRU_INCORRECT "\nIncorrect usage. To use '-line_bresenham -sru' you must follow:\n" \
                                    "\t-line_bresenham -sru x0 y0 x1 y1 xmin ymin xmax ymax\n" \
                                    "Real number can be used.\n\n"

#define HELP_MENU "Usage: monitor_cthulhu [options]\n" \
                    "Options:\n" \
                    " -line_bresenham [-sru] <param>\n" \
                    "\t\t\t\tDraw a line using Bresenham's algorithm.\n" \
                    "\t\t\t\tParameter are all integers: 'x0 y0 x1 y1'\n" \
                    "\t\t\t\tThe '-sru' option receives points that\n" \
                    "\t\t\t\tare using the SRU, the parameters are\n" \
                    "\t\t\t\t'x0 y0 x1 y1 xmin ymin xmax ymax'\n"


void print_help_menu();
int input_parser(int argc, char *argv[]);

#endif //CONSOLE_INPUT_H
