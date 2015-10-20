#include "../header/object2d_functions.h"

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
        // fix to draw line from top-down
        if (pd2->y < pd1->y) {
            while (j >= pd2->y) {
                device->buffer[device->ymax - j - 1][i] = color;
                j--;
            }
        }
            // draw line from bottom-up
        else {
            while (j <= pd2->y) {   // '<=' fixes faulty pixel
                device->buffer[device->ymax - j - 1][i] = color;
                j++;
            }
        }
    }
    else {
        a = (pd2->y - pd1->y) / (pd2->x - pd1->x);
        b = pd1->y - a * pd1->x;
        while (i < pd2->x) {
            device->buffer[device->ymax - j - 1][i] = color;
            aux = j;
            j = (int) round(a * (++i) + b);

            if (j > aux) {
                while (aux < j) {
                    device->buffer[device->ymax - aux - 1][i] = color;
                    aux++;
                }
            }
            if (j < aux) {
                while (aux >= j) {
                    device->buffer[device->ymax - aux - 1][i] = color;
                    aux--;
                }
            }
        }
    }
    free(pn1);
    free(pn2);
    free(pd1);
    free(pd2);
}

struct Object2D *plotCircle(struct Point2D *o, int r, int steps, int color) {
    double x, y;
    double theta = 0, h, k, step;
    step = 2 * PI / steps;
    h = o->x;
    k = o->y;
    struct Object2D *sphere;
    sphere = createObject(steps);

    for (theta = 0; theta < 2 * PI; theta += step) {
        x = h + r * cos(theta);
        y = k - r * sin(theta);
        setObject(setPoint(x, y, color), sphere);
    }

    return sphere;
}

//TODO Documentacao do drawObject
int drawObject(struct Object2D *object, struct Window *window, struct BufferDevice *device) {
    if (object->curr_point == 0)
        return False;

    //printf("%d point\n", object->curr_point);
    for (int i = 0; i < object->curr_point; i++) {
//        printf("\np1 = (%f,%f), p2 = (%f,%f)",
//               object->points[i].x,
//               object->points[i].y,
//               object->points[(i+1) % object->curr_point].x,
//               object->points[(i+1) % object->curr_point].y);

        drawLine(&object->points[i], &object->points[(i + 1) % object->curr_point],
                 window, device, object->points[i].color);
    }

    return True;
}