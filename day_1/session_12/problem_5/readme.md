# Problem 6

Viết chương trình bằng ngôn ngữ C cho phép người nhập vào danh sách kề của các đỉnh trong một đồ thị vô hướng và in ma trận kề của nó màn hình.

## Đầu vào

Dữ liệu đầu vào được đọc từ dòng nhập chuẩn (stdin, bàn phím) theo định dạng:

- Dòng đầu tiên chứa 1 số nguyên n mô tả số đỉnh của đồ thị
- n dòng tiếp, mỗi dòng mô tả một danh sách kề. Dòng i chứa danh sách các đỉnh kề của đỉnh i. Các phần tử cách nhau một khoảng trắng. Mỗi dòng đều kết thúc bằng số 0.

## Đầu ra

- In ra ma trận kề của đồ thị gồm n dòng, mỗi dòng chứa n phần tử, cách nhau 1 một khoảng trắng.

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

void print_matrix(Graph *pG)
{
    for (int i = 1; i <= pG->n; i++)
    {
        for (int j = 1; j <= pG->n; j++)
            printf("%d ", pG->A[i][j]);
        printf("\n");
    }
}

Graph read_graph_from_keyboard()
{
    int n;
    scanf("%d", &n);

    Graph G;
    init_graph(&G, n);

    for (int i = 1; i <= n; i++)
    {
        int v;
        do
        {
            scanf("%d", &v);
            add_edge(&G, i, v);
        } while (v);
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

int main()
{
    // Graph G = read_graph_from_file((char *)"./graph.txt");
    Graph G = read_graph_from_keyboard();
    print_matrix(&G);
    return 0;
}
```
