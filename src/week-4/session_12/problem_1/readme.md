# Problem 1

Viết chương trình bằng ngôn ngữ C cho phép người nhập vào ma trận kề của một đồ thị vô hướng và in các cung của nó ra màn hình.

## Đầu vào

Dữ liệu đầu vào được đọc từ dòng nhập chuẩn (stdin, bàn phím) theo định dạng:

- Dòng đầu tiên chứa 1 số nguyên n mô tả số đỉnh của đồ thị
- n dòng tiếp theo mô tả ma trận kề của đồ thị. Mỗi dòng có n số nguyên, cách nhau 1 khoảng trắng.

## Đầu ra

- In các cung của đồ thị vừa nhập ra màn hình, mỗi cung trên 1 dòng theo mẫu: u v (u≤v).
- Nếu có 2 cung (u1, v1) và (u2, v2) thì cung nào có u nhỏ sẽ được in ra trước. Nếu u bằng nhau thì cung nào có v nhỏ sẽ được in ra trước.

---

## Solution

```c
#include <stdio.h>

#define MAX_M 100

typedef struct
{
    int n, m;
    int A[MAX_M][MAX_M];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            pG->A[i][j] = 0;
}

void add_edge(Graph *pG, int u, int v)
{
    pG->A[u][v]++;
    pG->m++;
}

Graph read_graph_from_keyboard()
{
    int n;
    scanf("%d", &n);

    Graph G;
    init_graph(&G, n);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            int edges;
            scanf("%d", &edges);
            for (int k = 0; k < edges; k++)
                add_edge(&G, i, j);
        }
    return G;
}

Graph read_graph_from_file(char *filepath)
{
    FILE *f = freopen(filepath, "r", stdin);
    Graph G = read_graph_from_keyboard();
    fclose(f);
    return G;
}

void print_edges(Graph *pG, int u)
{
    for (int i = u; i <= pG->n; i++)
        for (int j = 0; j < pG->A[u][i]; j++)
            printf("%d %d\n", u, i);
}

int main()
{
    // Graph G = read_graph_from_file((char *)"./graph.txt");
    Graph G = read_graph_from_keyboard();
    for (int i = 1; i <= G.n; i++)
        print_edges(&G, i);
    return 0;
}
```
