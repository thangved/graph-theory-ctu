#include "define.h"

void add_edge(Graph *pG, int u, int v)
{
    if (u > pG->n || v > pG->n)
        return;
    if (u < 1 || v < 1)
        return;

    for (int i = 0; i < pG->m; i++)
        if (pG->edges[i].u == u && pG->edges[i].v == v)
            return;

    Edge e = {u, v};
    pG->edges[pG->m] = e;
    pG->m++;
}
