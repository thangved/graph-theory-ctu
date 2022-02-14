#include "define.h"

void add_edge(Graph *pG, int u, int v)
{
    pG->A[u][v] = 1;
    pG->m++;
}