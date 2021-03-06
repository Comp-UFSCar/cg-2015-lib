/** @file scanLine.c
 *  @brief Scan line algorithm for filling a polygons.
 *
 *  @author Thales Menato (thamenato)
 *  @author Daniel Nobusada (nobusada)
 *  @author Marcelo Lopes Lotufo (0tho)
 *
 */

#include "../header/scanLine.h"

/* Inserts edge into list in order of increasing xIntersect field. */
void insertEdge (Edge * list, Edge * edge)
{
    Edge * p, * q = list;

    p = q->next;
    while (p != NULL) {
        if (edge->xIntersect < p->xIntersect)
            p = NULL;
        else {
            q = p;
            p = p->next;
        }
    }
    edge->next = q->next;
    q->next = edge;
}

/* For an index, return y-coordinate of next nonhorizontal line */
int yNext (int k, int cnt, struct Point2D * pts)
{
    int j;

    if ((k+1) > (cnt-1))
        j = 0;
    else
        j = k + 1;
    while (pts[k].y == pts[j].y)
        if ((j+1) > (cnt-1))
            j = 0;
        else
            j++;
    return (pts[j].y);
}

/* Store lower-y coordinate and inverse slope for each edge.  Adjust
   and store upper-y coordinate for edges that are the lower member
   of a monotically increasing or decreasing pair of edges */
void makeEdgeRec
        (struct Point2D lower, struct Point2D upper, int yComp, Edge * edge, Edge * edges[])
{
    edge->dxPerScan =
            (float) (upper.x - lower.x) / (upper.y - lower.y);
    edge->xIntersect = lower.x;
    if (upper.y < yComp)
        edge->yUpper = upper.y - 1;
    else
        edge->yUpper = upper.y;
    insertEdge (edges[(int) lower.y], edge);
}

void buildEdgeList (int cnt, struct Point2D * pts, Edge * edges[])
{
    Edge * edge;
    struct Point2D v1, v2;
    int i, yPrev = (int) pts[cnt - 2].y;

    v1.x = pts[cnt-1].x; v1.y = pts[cnt-1].y;
    for (i=0; i<cnt; i++) {
        v2 = pts[i];
        if (v1.y != v2.y) {                /* nonhorizontal line */
            edge = (Edge *) malloc (sizeof (Edge));
            if (v1.y < v2.y)                 /* up-going edge      */
                makeEdgeRec (v1, v2, yNext (i, cnt, pts), edge, edges);
            else                             /* down-going edge    */
                makeEdgeRec (v2, v1, yPrev, edge, edges);
        }
        yPrev = v1.y;
        v1 = v2;
    }
}

void buildActiveList (int scan, Edge * active, Edge * edges[])
{
    Edge * p, * q;

    p = edges[scan]->next;
    while (p) {
        q = p->next;
        insertEdge (active, p);
        p = q;
    }
}

void fillScan (int scan, Edge * active, struct Window *window, struct BufferDevice *device, int color)
{
    Edge * p1, * p2;
    int i;
    //TODO: For some reason the image was inverted so I inverted again. Find the real reason and fix it.
    int j = device->ymax - scan;

    p1 = active->next;
    while (p1) {
        p2 = p1->next;
        for (i= (int) p1->xIntersect; i<p2->xIntersect; i++) {
            //setPixel((int) i, scan);
            device->buffer[j][i] = color;
        }
        p1 = p2->next;
    }
}

void deleteAfter (Edge * q)
{
    Edge * p = q->next;

    q->next = p->next;
    free (p);
}

/* Delete completed edges. Update 'xIntersect' field for others */
void updateActiveList (int scan, Edge * active)
{
    Edge * q = active, * p = active->next;

    while (p)
        if (scan >= p->yUpper) {
            p = p->next;
            deleteAfter (q);
        }
        else {
            p->xIntersect = p->xIntersect + p->dxPerScan;
            q = p;
            p = p->next;
        }
}

void resortActiveList (Edge * active)
{
    Edge * q, * p = active->next;

    active->next = NULL;
    while (p) {
        q = p->next;
        insertEdge (active, p);
        p = q;
    }
}

void scanFill (struct Object2D * object, struct Window *window, struct BufferDevice *device)
{
    int i;
    struct Point2D *pts = malloc(sizeof(object->points));
    struct Point2D *pn1, *pd1;

    int cor = object->fillColor;

    for (i = 0; i < object->curr_point; i++) {
        struct Point2D * p = &object->points[i];

        pn1 = sru2srn(p, window);
        pd1 = srn2srd(pn1, device);
        pts[i].x = pd1->x;
        pts[i].y = pd1->y;
        //pts[i].color = pd1->color;
    }

    int cnt = object->curr_point;
    int height = device->ymax;

    Edge * edges[height], * active;
    int scan;

    for (i=0; i<height; i++) {
        edges[i] = (Edge *) malloc (sizeof (Edge));
        edges[i]->next = NULL;
    }
    buildEdgeList (cnt, pts, edges);
    active = (Edge *) malloc (sizeof (Edge));
    active->next = NULL;

    for (scan=0; scan<height; scan++) {
        buildActiveList (scan, active, edges);
        if (active->next) {
            fillScan (scan, active, window, device, cor);
            updateActiveList (scan, active);
            resortActiveList (active);
        }
    }
    /* Free edge records that have been malloc'ed ... */
}