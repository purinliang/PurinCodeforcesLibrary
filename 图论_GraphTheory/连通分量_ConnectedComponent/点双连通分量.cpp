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

    bool cut[MAXN];

    void tarjan(int u, int root) {
        ++dfn_cnt, dfn[u] = dfn_cnt, low[u] = dfn_cnt;
        int chd_cnt = 0;  // be used for check whether root is cut vertex
        for (const auto& v : G[u]) {
            if (!dfn[v]) {
                ++chd_cnt;
                tarjan(v, root);
                low[u] = min(low[u], low[v]);
                if (u != root && low[v] >= dfn[u]) cut[u] = true;
            }
            low[u] = min(low[u], dfn[v]);
        }
        if (u == root && chd_cnt >= 2) cut[root] = true;
    }

    void calc_cut() {
        fill(dfn + 1, dfn + 1 + n, 0);
        fill(low + 1, low + 1 + n, 0);
        dfn_cnt = 0;
        fill(cut + 1, cut + 1 + n, false);
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) tarjan(i, i);
        }
    }

}  // namespace BiconnectedComponent

using namespace BiconnectedComponent;
