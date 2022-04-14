/**
 * @file simp-lord.c
 * @author thangved (thangved02@gmail.com)
 * @brief "Ngưu Lang là vị thần chăn trâu của Ngọc Hoàng Thượng đế, vì say mê một tiên nữ phụ trách việc dệt vải tên là Chức Nữ nên bỏ bễ việc chăn trâu, để trâu đi nghênh ngang vào điện Ngọc Hư. Chức Nữ cũng vì mê tiếng tiêu của Ngưu Lang nên trễ nải việc dệt vải. Ngọc Hoàng giận dữ, bắt cả hai phải ở cách xa nhau, người đầu sông Ngân, kẻ cuối sông.

Mỗi năm một lần, Sau đó, Ngọc Hoàng thương tình nên ra ơn cho hai người mỗi năm được gặp nhau vào ngày 7 tháng Bảy âm lịch. Khi tiễn biệt nhau, Ngưu Lang và Chức Nữ khóc sướt mướt. Nước mắt của họ rơi xuống trần hóa thành cơn mưa và được người dưới trần gian đặt tên là mưa ngâu." (Theo wikipedia.com)

Để gặp được nhau vào ngày 7/7, Ngưu Lang và Chức Nữ phải nhờ đến bầy quạ đen bắt cầu (gọi là Ô kiều) cho mình đi qua để gặp nhau.

Sông Ngân Hà có n ngôi sao, giả sử được đánh số từ 1 đến n. Ngưu Lang ở tại ngôi sao Ngưu (Altair), được đánh số 1, còn Chức Nữ thì mỗi năm lại ở tại một ngôi sao khác nhau trong các ngôi sao từ 2 đến n. Để bắt được một cây cầu từ ngôi sao này sang ngôi sao kia cần một số lượng quạ nào đó. Một khi con quạ ở cây cầu nào thì phải ở đó cho đến khi Ngưu Lang và Chức Nữ gặp được nhau.

Vì không biết Chức Nữ đang ở ngôi sao nào nên Ngưu Lang cần bắt cầu sao cho từ ngôi sao số 1, anh ta có thể đi đến được tất cả các ngôi sao khác (dĩ nhiên là để tìm Chức Nữ).

Quạ thì càng ngày càng hiếm, mà Ngưu Lang chỉ có đủ tiền để thuê được tối đa k con quạ thôi nên Ngưu Lang phải tính toán sao cho số lượng quạ dùng để bắt cầu ít nhất có thể.

Hãy giúp Ngưu Lang viết chương trình tính xem Ngưu Lang có thể gặp được Chức Nữ không. Nếu thiếu thì thiếu bao nhiêu con quạ.
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

void prim(Graph *pG, int k)
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

    T.w <= k ? puts("OK") : printf("%d", T.w - k);
}

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    Graph G = init_graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    prim(&G, k);
    return 0;
}