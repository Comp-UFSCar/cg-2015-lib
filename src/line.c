#include "../header/line.h"

void drawLine(struct Point2D *p1, struct Point2D *p2, struct Window *win,
              struct BufferDevice *device, int color) {

    double a, b;
    int i, j, aux;
    struct Point2D *pn1, *pd1, *pn2, *pd2;

    pn1 = sru2srn(p1, win);
    pd1 = srn2srd(pn1, device);
    pn2 = sru2srn(p2, win);
    pd2 = srn2srd(pn2, device);

    if (pd1->x > pd2->x) {
        aux = (int) pd1->x;
        pd1->x = pd2->x;
        pd2->x = aux;
        aux = (int) pd1->y;
        pd1->y = pd2->y;
        pd2->y = aux;
    }

    i = (int) pd1->x;
    j = (int) pd1->y;

    if (pd1->x == pd2->x) {
        while (j < pd2->y) {
            device->buffer[(device->ymax - j - 1) * device->xmax + i] = color;
            j++;
        }
    }
    else {
        a = (pd2->y - pd1->y) / (pd2->x - pd1->x);
        b = pd1->y - a * pd1->x;
        while (i < pd2->x) {
            device->buffer[(device->ymax - j - 1) * device->xmax + i] = color;
            aux = j;
            j = (int) round(a * (++i) + b);

            if (j > aux) {
                while (aux < j) {
                    device->buffer[(device->ymax - aux - 1) * device->xmax + i] = color;
                    aux++;
                }
            }
            if (j < aux) {
                while (aux > j) {
                    device->buffer[(device->ymax - aux - 1) * device->xmax + i] = color;
                    aux--;
                }
            }
        }
    }
}

struct Object2D *createCircle(float radius, int color) {
    struct Object2D *sphere;
    double x, y, th;
    int i;

    sphere = createObject(36);

    th = 0.0;
    for (i = 0; i < 10; i++) {
        x = radius * cos(th);
        y = sqrt(radius * radius - x * x);
        setObject(setPoint(x, y, color), sphere);
        th += (10.0 * PI) / 180;
    }
    for (i = 10 - 1; i >= 0; i--) {
        setObject(setPoint((-1.0) * sphere->points[i].x, sphere->points[i].y, color), sphere);
    }
    for (i = 19 - 1; i >= 9; i--) {
        setObject(setPoint(sphere->points[i].x, (-1.0) * sphere->points[i].y, color), sphere);
    }
    for (i = 28 - 1; i >= 18; i--) {
        setObject(setPoint((-1.0) * sphere->points[i].x, sphere->points[i].y, color), sphere);
    }

    return sphere;
}
