#include "define.h"

void add_edge(Graph *pG, int u, int v)
{
    if (u > pG->n || v > pG->n)
        return;
    if (u < 1 || v < 1)
        return;

    Edge e = {u, v};
    pG->edges[pG->m] = e;
    pG->m++;
}
