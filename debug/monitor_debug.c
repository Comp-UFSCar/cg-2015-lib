#include "../header/base_functions.h"

int main(int argc, char *argv[]) {
    printf("##############\tMonitor Debug\t##############\n");

    struct Point    p0u = {3, 5}, p0n, p0d,
                    p1u = {15, 15}, p1n, p1d;
    struct Image img;


    // SRU 2 SRN
    printf("SRU 2 SRN\n");
    p0n = sru2srn(p0u, -50, -50, 50, 50);
    p1n = sru2srn(p1u, -50, -50, 50, 50);

    printf("x: %lf y: %lf\n", p0n.x, p0n.y);
    printf("x: %lf y: %lf\n", p1n.x, p1n.y);

    // SRN 2 SRD
    printf("SRN 2 SRD\n");

    p0d = srn2srd(p0n);
    p1d = srn2srd(p1n);

    printf("x: %lf y: %lf\n", p0d.x, p0d.y);
    printf("x: %lf y: %lf\n", p1d.x, p1d.y);

//    init_image(&img);
//    print_image(img);

    img = drawLine_Bresenham(p0d, p1d);

//    printf("\n Depois \n");
//    print_image(img);

    return 0;
}