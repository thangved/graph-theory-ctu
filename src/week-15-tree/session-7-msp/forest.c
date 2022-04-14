/**
 * @file forest.c
 * @author thangved (thangved02@gmail.com)
 * @brief Trong một khu rừng nọ, có một bầy nai và n bãi cỏ. Để đi từ bãi cỏ này sang bãi cỏ kia, bầy nai sẽ đi theo những con đường mòn được tạo ra từ trước. Sau một thời gian, bầy nai nhận ra rằng chúng chỉ cần một số đường mòn là có thể đi từ một bãi cõ bất kỳ đến một bãi cỏ khác. Trên mỗi con đường mòn có một số nguy rình rập bầy nai (ví dụ có hổ, sói, ...). Để đơn giản ta có thể giả sử độ nguy hiểm của mỗi con đường là 1 số nguyên từ 1 (ít nguy hiểm nhất) đến 100 (nhiều nguy hiểm nhất).

Hãy viết chương trình giúp bầy nai tìm các con đường mòn cần thiết sao cho tổng độ nguy hiểm thấp nhất.
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022 Kim Minh Thang
 *
 */
#include <stdio.h>

#define INFINITY __INT_MAX__
#define NO_EDGE INFINITY
#define MAX_NODE 100

typedef struct
{
    int n, m, w;
    int W[MAX_NODE][MAX_NODE];
} Graph;

typedef Graph GTree;

Graph init_graph(int n)
{
    Graph G;
    G.n = n;
    G.m = 0;
    G.w = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            G.W[i][j] = NO_EDGE;
    return G;
}

void add_edge(Graph *pG, int u, int v, int w)
{
    pG->W[u][v] = w;
    pG->W[v][u] = w;
    pG->m++;
    pG->w += w;
}

GTree init_tree(int n)
{
    return init_graph(n);
}

int find_root(int parents[], int u)
{
    while (u != parents[u])
        u = parents[u];
    return u;
}

void prim(Graph *pG)
{
    int pi[MAX_NODE];
    int p[MAX_NODE] = {};
    int parents[MAX_NODE];
    int marked[MAX_NODE] = {};

    for (int i = 0; i < MAX_NODE; i++)
    {
        pi[i] = INFINITY;
        parents[i] = i;
    }

    GTree T = init_tree(pG->n);
    pi[1] = 0;

    while (T.m != T.n - 1)
    {
        int u = 0;
        for (int i = 1; i <= T.n; i++)
        {
            if (marked[i])
                continue;
            if (pi[i] >= pi[u])
                continue;
            u = i;
        }

        int root_u = find_root(parents, p[u]);
        int root_v = find_root(parents, u);
        if (root_u == root_v)
            continue;
        if (p[u] != 0)
        {
            add_edge(&T, p[u], u, pi[u]);
            parents[root_v] = root_u;
        }
        marked[u] = 1;

        for (int v = 1; v <= T.n; v++)
        {
            if (u == v || pG->W[u][v] == NO_EDGE || pG->W[u][v] >= pi[v])
                continue;

            pi[v] = pG->W[u][v];
            p[v] = u;
        }
    }

    printf("%d", T.w);
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    Graph G = init_graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    prim(&G);
    return 0;
}