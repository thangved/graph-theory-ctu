# Problem 1

Cho chương trình có hàm main() như bên dưới. Hãy viết thêm khai báo CTDL Graph (biểu diễn đồ thị bằng phương pháp danh sách cung) và cài đặt các hàm cần thiết vào chỗ ba chấm (...) để có được chương trình hoàn chỉnh, chạy được.

```c
#include <stdio.h>

/* Bổ sung khai báo CTDL Graph và cài đặt các hàm cần thiết */
...
/* Hết phần mã lệnh của bạn */

//Hàm main()
int main() {
    Graph G;
    int n = 4, u;

    //Khởi tạo đồ thị
    init_graph(&G, n);
    //Thêm cung vào đồ thị
    add_edge(&G, 1, 2);
    add_edge(&G, 1, 3);
    add_edge(&G, 1, 3);
    add_edge(&G, 3, 4);
    add_edge(&G, 1, 4);

    //In bậc của các đỉnh
    for (u = 1; u <= n; u++)
        printf("deg(%d) = %d\n", u, degree(&G, u));
    return 0;
}
```

## Chú ý

- Không nộp toàn bộ chương trình, chỉ nộp phần bạn viết.

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
```
