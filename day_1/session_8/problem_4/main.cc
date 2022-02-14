#include "define.h"

void add_edge(Graph *pG, int u, int v)
{
    pG->A[u][v]++;
    pG->m++;
}