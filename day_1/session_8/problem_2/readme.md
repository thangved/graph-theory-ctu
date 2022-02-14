# Problem 1

Cho cấu trúc dữ liệu đồ thị Graph được cài đặt bằng phương pháp "Ma  trận kề" dùng để lưu trữ các đơn đồ thị có hướng.

```c
#define MAX_N 100
typedef struct {
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;
```

Viết hàm add_edge(Graph *pG, int u, int v) để thêm cung (u, v) vào đồ thị pG theo mẫu (prototype):

```c
void add_edge(Graph *pG, int u, int v) {
}
```

---

## Solution

```c
void add_edge(Graph *pG, int u, int v)
{
    pG->A[u][v] = 1;
    pG->m++;
}
```
