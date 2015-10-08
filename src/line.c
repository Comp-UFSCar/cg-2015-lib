#include "../header/line.h"

void drawLine(struct Point2D *p1, struct Point2D *p2, struct Window *win,
              struct BufferDevice *device, int color) {

    float a, b;
    int i, j, aux;
    struct Point2D *pn1, *pd1, *pn2, *pd2;

    pn1 = sru2srn(p1, win);
    pd1 = srn2srd(pn1, device);
    pn2 = sru2srn(p2, win);
    pd2 = srn2srd(pn2, device);

    if (pd1->x > pd2->x) {
        aux = pd1->x;
        pd1->x = pd2->x;
        pd2->x = aux;
        aux = pd1->y;
        pd1->y = pd2->y;
        pd2->y = aux;
    }

    i = pd1->x;
    j = pd1->y;

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
            j = round(a * (++i) + b);

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