# Problem 1

Viết chương trình bằng ngôn ngữ C cho phép người dùng nhập dữ liệu của một đồ thị vô hướng và in các đỉnh kề của các đỉnh ra màn hình.

Biểu diễn đồ thị bằng phương pháp "Danh sách cung".

## Đầu vào

Dữ liệu đầu vào được đọc từ dòng nhập chuẩn (stdin, bàn phím) theo định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m cách nhau một khoảng trắng, n: số đỉnh, m: số cung
- m dòng tiếp theo, mỗi dòng chứa 2 số nguyên u v cách nhau 1 khoảng trắng mô tả cung (u, v).

## Đầu ra

- In ra n dòng, dòng thứ i in các đỉnh kề của đỉnh i, cách nhau 1 khoảng trắng, theo thứ tự tăng dần (không lặp lại), ví dụ: neighbours(2) = 1 2 4

## Chú ý

- Giả sử dữ liệu đầu vào luôn hợp lệ, không cần phải kiểm tra
- Nộp toàn bộ chương trình
- Xem thêm định dạng đầu vào và đầu ra trong phần For example

## For example

| Input | Result              |
|-------|---------------------|
| 4 3   | neighbours(1) = 3 4 |
| 1 3   | neighbours(2) =     |
| 4 1   | neighbours(3) = 1 3 |
| 3 3   | neighbours(4) = 1   |

---

## Solution

```c
#define MAX_EDGES 100

typedef struct
{
    int u, v;
} Edge;

typedef struct
{
    int n, m;
    Edge edges[MAX_EDGES];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
}

void add_edge(Graph *pG, int u, int v)
{
    Edge edge = {u, v};
    pG->edges[pG->m] = edge;
    pG->m++;
}

int degree(Graph *pG, int u)
{
    int deg = 0;
    for (int i = 0; i < pG->m; i++)
    {
        deg += pG->edges[i].u == u;
        deg += pG->edges[i].v == u;
    }
    return deg;
}

#include <stdio.h>

Graph read_graph_from_keyboard()
{
    int n, m;
    scanf("%d%d", &n, &m);

    Graph G;
    init_graph(&G, n);

    for (; m != 0; m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
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

void print_neighbours(Graph *pG, int u)
{
    printf("neighbours(%d) = ", u);
    int neighbours[100];
    for (int i = 1; i <= pG->n; i++)
        neighbours[i] = 0;
    for (int i = 0; i < pG->m; i++)
    {
        neighbours[pG->edges[i].v] += pG->edges[i].u == u;
        neighbours[pG->edges[i].u] += pG->edges[i].v == u;
    }
    for (int i = 1; i <= pG->n; i++)
    {
        if (neighbours[i])
            printf("%d ", i);
    }
    printf("\n");
}

int main()
{
    // Graph G = read_graph_from_file((char *)"./graph.txt");
    Graph G = read_graph_from_keyboard();

    for (int i = 1; i <= G.n; i++)
        print_neighbours(&G, i);

    return 0;
}
```
