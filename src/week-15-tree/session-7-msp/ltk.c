/**
 * @file ltk.c
 * @author thangved (thangved02@gmail.com)
 * @brief Lý Thường Kiệt (sinh năm 1019, mất 1105) là một danh tướng đời nhà Lý có công lớn trong việc đánh bại quân nhà Tống vào năm 1075-1077. Ông được cho là đã viết ra bản tuyên ngôn độc lập đầu tiên của dân tộc ("Nam Quốc Sơn Hà").

"Tháng 3 năm 1076, nhà Tống sai tuyên phủ sứ Quảng Nam là Quách Quỳ làm chiêu thảo sứ, Triệu Tiết làm phó, đem quân 9 tướng, hẹn với Chiêm Thành và Chân Lạp sang xâm lấn Đại Việt, ... Quân Tống tràn xuống, theo đường tắt qua dãy núi Đâu Đỉnh, tới phía tây bờ sông Phú Lương; trong khi đó, một cánh quân tách ra, vòng sang phía đông đánh bọc hậu quân Nam ở Giáp Khẩu (Chi Lăng) và thẳng tới sông Cầu.

Để đối phó với quân Tống trong tình hình này Lý Thường Kiệt lập chiến luỹ sông Như Nguyệt để chống Tống."

Chiến luỹ sông Như Nguyệt có n điểm trọng yếu cần phải bảo vệ, giả sử được đánh số từ 1 đến n. Lý Thường Kiệt cần phải bố trí các con đường an toàn để điều động quân lính từ một điểm trọng yếu này đến một điểm trọng yếu khác. Để xây dựng một con đường an toàn từ một điểm trọng yếu u này đến một điểm trọng yếu v cần một lượng đất đá là w(u, v) sọt.

Hãy giúp Lý Thường Kiệt tìm cách xây dựng các con đường an toàn sao cho từ bất kỳ một điểm trọng yếu nào cũng đều có thể đi đến một điểm trọng yếu khác bằng cách sử dụng các con đường an toàn và tổng số đất đá được sử dụng là ít nhất.
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