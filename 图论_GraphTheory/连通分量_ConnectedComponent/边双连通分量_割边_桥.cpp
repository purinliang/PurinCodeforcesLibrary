#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10;

namespace BiconnectedComponent {

    int n, m;
    vector<int> G[MAXN];

    void init() {
        for (int i = 1; i <= n; ++i) G[i].clear();
    }

    void add_edge(int u, int v) {
        // 注意是无向图，主函数要调用两次
        // add_edge(u, v);
        // add_edge(v, u);
        G[u].push_back(v);
    }

    int dfn[MAXN];
    int low[MAXN];
    int dfn_cnt;

    // 割边/桥一定是唯一的树边。若 cut_edge[v] == true，
    // 则无向边 (parent[v], v) 为割边/桥。也可以先算出
    // 割点，然后把他变成一棵树，树上的边就都是割边。
    bool cut_edge[MAXN];
    int parent[MAXN];

    void tarjan(int u, int p) {
        ++dfn_cnt, dfn[u] = dfn_cnt, low[u] = dfn_cnt;
        parent[u] = p;
        for (const auto& v : G[u]) {
            if (!dfn[v]) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) cut_edge[v] = true;
            }
            low[u] = min(low[u], dfn[v]);
        }
    }

    void calc_bridge() {
        fill(dfn + 1, dfn + 1 + n, 0);
        fill(low + 1, low + 1 + n, 0);
        dfn_cnt = 0;
        fill(cut_edge + 1, cut_edge + 1 + n, false);
        fill(parent + 1, parent + 1 + n, 0);
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) tarjan(i, i);
        }
    }

    // 如果某条是割边，那么去掉之后，连通块的数量会增加
    // 有个简单的办法，把割边堵住，然后每个块进行一次dfs
    // 就可以得到每一个边双连通分量的等价点（边双连通缩点）
    // 进行边双连通缩点之后得到森林。

}  // namespace BiconnectedComponent

using namespace BiconnectedComponent;
