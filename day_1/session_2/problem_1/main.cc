#include "define.h"

void add_edge(Graph *pG, int u, int v)
{
    Edge e = {u, v};
    pG->edges[pG->m] = e;
    pG->m++;
}