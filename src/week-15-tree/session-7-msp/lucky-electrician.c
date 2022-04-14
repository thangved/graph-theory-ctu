/**
 * @file lucky-electrician.c
 * @author thangved (thangved02@gmail.com)
 * @brief Hoàng là thợ điện. Anh được thuê sửa lại hệ thống điện cho một căn nhà. Tình trạng hiện tại của hệ thống điện như sau: nguồn điện chính được cung cấp từ đồng hồ điện. Chủ nhà muốn lấy điện từ nguồn điện chính để cấp điện cho n - 1 vị trí trong nhà bằng cách sử dụng dây điện (dĩ nhiên là phải dùng dây điện để dẫn điện rồi cười ). Để đơn giản hoá vấn đề ta có thể xem nguồn điện chính là vị trí 1, các vị trí cần lấy điện được đánh số lần lượt là 2, 3, ..., n. Hoàng có thể dùng dây điện để nối hai vị trí lại với nhau. Ngoài ra, Hoàng còn phải quan tâm đến loại dây điện sử dụng để nối hai vị trí này. Mỗi loại dây lại có một giá thành khác nhau.

Bài toán đặt ra cho Hoàng là sử dụng đây điện và nối dây như thế nào để tất cả các vị trí đều có điện với giá thành mua dây điện rẻ nhất.

Hãy lập trình để giúp Hoàng, anh ta sẽ cảm ơn bạn nhiều lắm !
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
        int u, v, s, d;
        scanf("%d%d%d%d", &u, &v, &s, &d);
        add_edge(&G, u, v, s * d);
    }

    prim(&G);
    return 0;
}