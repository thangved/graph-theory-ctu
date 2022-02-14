#include "define.h"

int degree(Graph *pG, int u)
{
    int deg = 0;
    for (int i = 1; i <= pG->n; i++)
    {
        deg += pG->A[u][i];
        deg += pG->A[i][u];
    }
    return deg;
}
