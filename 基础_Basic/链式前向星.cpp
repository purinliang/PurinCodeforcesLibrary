#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;  // 图的顶点的最大值
const int MAXM = 3e5 + 10;  // 图的边的最大值（注意无向边一次会存储相反方向的一对）

int head[MAXN];  // 邻接链表的顶点数组，表示每个顶点的出边的下标，-1表示链表的尾部

struct Edge {
    int from;    // 边的起点（通常可以省略）
    int to;      // 边的终点
    int weight;  // 边的权值（部分算法会用到）
    int next;    // 同属于边的起点的下一条边的下标，-1表示链表尾部
} edge[MAXM];    // 邻接链表的所有边

int n, m;

void init() {
    for (int i = 1; i <= n; ++i) {
        head[i] = -1;  // 每个顶点的出边链表都是空的
    }
    m = 0;  // 邻接链表的所有边的计数，也是空的
}

void add_edge(int u, int v, int w) {
    // 顶点u向顶点v，加入一条权值为w的边
    ++m;  // 边数+1
    edge[m].from = u;
    edge[m].to = v;
    edge[m].weight = w;
    edge[m].next = head[u];  // 并不是在链表的尾部插入，而是在链表的头部之前插入
    head[u] = m;             // u节点的出边链表当前的头，设为最新的第m条边
}

bool vis[MAXN];
void dfs(int u) {
    if (vis[u]) {
        return;
    }
    vis[u] = 1;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        assert(edge[i].from == u);
        int v = edge[i].to;
        int w = edge[i].weight;
        dfs(v);
    }
}
