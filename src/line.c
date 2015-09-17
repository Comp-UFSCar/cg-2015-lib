#include "../header/line.h"

struct Image drawLine(struct Point p0, struct Point p1){

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