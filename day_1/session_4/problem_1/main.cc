#include "define.h"

int includes(Graph g, Edge e)
{
    for (int i = 0; i < g.m; i++)
    {
        if (g.edges[i].u == e.u && g.edges[i].v == e.v)
            return 1;

        if (g.edges[i].u == e.v && g.edges[i].v == e.u)
            return 1;
    }

    return 0;
}

int adjacent(Graph *pG, int u, int v) // Edge e = {u, v}
{
    Edge e = {u, v};
    return includes(*pG, e);
}