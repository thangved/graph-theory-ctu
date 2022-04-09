#include <stdio.h>

#define INFINITY __INT_MAX__
#define NO_EDGE INFINITY
#define MAX_NODE 100

typedef struct
{
    int n, m;
    int W[MAX_NODE][MAX_NODE];
} Graph;

/**
 * @brief Init Graph
 *
 * @param pG Pointer to Graph
 * @param n Num Node of Graph
 */
void initgraph(Graph *pG, int n)
{
    pG->m = 0;
    pG->n = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pG->W[i][j] = NO_EDGE;
}

/**
 * @brief Add Edge to Graph
 *
 * @param pG Pointer to Graph
 * @param u Start of Edge
 * @param v End of Edge
 * @param w Weight of Edge
 */
void addedge(Graph *pG, int u, int v, int w)
{
    pG->W[u][v] = w;
    pG->m++;
}

void printpath(int next[][MAX_NODE], int u, int v)
{
    if (u == v || next[u][v] == u)
    {
        printf("%d\n", u);
        return;
    }
    if (next[u][v] == -1)
    {
        puts("NO PATH");
        return;
    }
    printf("%d -> ", u);
    printpath(next, next[u][v], v);
}

void FloydWarshall(Graph *pG)
{
    int pi[MAX_NODE][MAX_NODE];
    int next[MAX_NODE][MAX_NODE];
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
        {
            pi[u][v] = INFINITY;
            next[u][v] = -1;
        }

    for (int u = 1; u <= pG->n; u++)
        pi[u][u] = 0;

    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
            if (pG->W[u][v] != NO_EDGE)
            {
                pi[u][v] = pG->W[u][v];
                next[u][v] = v;
            }

    for (int k = 1; k <= pG->n; k++)
        for (int u = 1; u <= pG->n; u++)
            for (int v = 1; v <= pG->n; v++)
                if (pi[u][k] + pi[k][v] < pi[u][v])
                {
                    if (pi[u][k] == INFINITY || pi[k][v] == INFINITY)
                        continue;
                    pi[u][v] = pi[u][k] + pi[k][v];
                    next[u][v] = next[u][k];
                }
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
        {
            printf("path(%d, %d): ", u, v);
            printpath(next, u, v);
        }
}

int main()
{
    Graph G;
    freopen("./graph.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    initgraph(&G, n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addedge(&G, u, v, w);
    }
    FloydWarshall(&G);
    return 0;
}