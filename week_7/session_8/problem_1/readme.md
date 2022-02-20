# Week 7 - Session 8 - Problem 1

Viết chương trình đọc một đồ thị vô hướng từ bàn phím và đếm số bộ phận liên thông của đồ thị.

## Đầu vào (Input)

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.
- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v mô tả cung (u, v).

## Đầu ra (Output)

- In ra số bộ phận liên thông của đồ thị.

## Gợi ý

Xem tài liệu thực hành

### Hướng dẫn đọc dữ liệu và chạy thử chương trình

- Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
- Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
- Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:

```c
freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
Graph G;
int n, m, u, v, w, e;
scanf("%d%d", &n, &m);
init_graph(&G, n);

for (e = 0; e < m; e++) {
    scanf("%d%d", &u, &v);
    add_edge(&G, u, v);
}
```

## Solution

```c
#include <stdio.h>

#define MAX_NODE 100

typedef struct
{
    int n, m;
    int A[MAX_NODE][MAX_NODE];
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
    pG->A[v][u]++;
    pG->m++;
}

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

int marked[MAX_NODE];

int count_connected_node(Graph *pG, int x)
{
    if (marked[x])
        return 0;
    int count = 0;
    marked[x] = 1;
    count++;
    for (int i = 1; i <= pG->n; i++)
        if (pG->A[x][i])
            count += count_connected_node(pG, i);
    return count;
}

int main()
{
    // Graph G = read_graph_from_file((char *)"./graph.txt");
    Graph G = read_graph_from_keyboard();

    // Initial values
    for (int i = 1; i <= G.n; i++)
        marked[i] = 0;

    int count = 0;

    for (int i = 1; i <= G.n; i++)
    {
        if (marked[i])
            continue;
        count++;
        count_connected_node(&G, i);
    }

    printf("%d\n", count);

    return 0;
}
```
