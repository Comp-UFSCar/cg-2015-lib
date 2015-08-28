#include "../header/console_input.h"
#include <string.h>

void print_help_menu(){
    printf(HELP_MENU);
}

int input_parser(int argc, char *argv[]){
    // function drawLine_Bresenham
    if(strcmp(argv[1],"-line_bresenham") == 0) {
        if(argc < 3){
            printf(LINE_BRESENHAM_INCORRECT);
            return INPUT_MISTAKE;
        }
        else {
            // Convert from SRU to SRN to SRD
            // -line_bresenham -sru <x0> <y0> <x1> <y1> <xmin> <ymin> <xmax> <ymax>
            if(strcmp(argv[2],"-sru") == 0) {
                if(argc != 11) {
                    printf(LINE_BRESENHAM_SRU_INCORRECT);
                    return INPUT_MISTAKE;
                }
                else {
                    return LINE_BRESENHAM_SRU;
                }
            }
            // Default mode - already SRD
            // -line_bresenham <x0> <y0> <x1> <y1>
            else {
                if(argc == 6)
                    return LINE_BRESENHAM;
                else {
                    printf(LINE_BRESENHAM_INCORRECT);
                    return INPUT_MISTAKE;
                }
            }
        }
    }
    return INPUT_ERROR;
}

