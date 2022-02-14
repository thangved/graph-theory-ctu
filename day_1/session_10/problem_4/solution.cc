#include "define.h"

int outdegree(Graph *pG, int u)
{
    int deg = 0;
    for (int i = 1; i <= pG->n; i++)
        deg += pG->A[u][i];
    return deg;
}
