# Problem 3

Viết chương trình bằng ngôn ngữ C cho phép đọc dữ liệu của một đồ thị từ tập tin và in bậc của các đỉnh ra màn hình.

## Đầu vào

Dữ liệu đầu vào được đọc từ tập tin `dt.txt` (cùng thư mục với chương trình thực thi) theo định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m cách nhau một khoảng trắng, n: số đỉnh, m: số cung
- m dòng tiếp theo, mỗi dòng chứa 2 số nguyên u v cách nhau 1 khoảng trắng mô tả cung (u, v).

## Đầu ra

- In ra n dòng, dòng thứ i in bậc của đỉnh i, theo mẫu: deg(2) = 3

## Chú ý

- Giả sử dữ liệu đầu vào luôn hợp lệ, không cần phải kiểm tra
- Nộp toàn bộ chương trình
- Xem thêm định dạng đầu vào và đầu ra trong phần For example

## For example

| Input           | Result     |
|-----------------|------------|
| >dt.txt <<< EOD | deg(1) = 1 |
| 4 5             | deg(2) = 4 |
| 1 3             | deg(3) = 2 |
| 4 2             | deg(4) = 3 |
| 2 4             |            |
| 2 4             |            |
| 3 2             |            |
| EOD             |            |

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

Graph read_graph_from_file(char *filepath)
{
    FILE *f = freopen(filepath, "r", stdin);
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
    fclose(f);
    return G;
}

int main()
{
    Graph G = read_graph_from_file((char *)"./dt.txt");
    for (int i = 1; i <= G.n; i++)
        printf("deg(%d) = %d\n", i, degree(&G, i));

    return 0;
}
```
