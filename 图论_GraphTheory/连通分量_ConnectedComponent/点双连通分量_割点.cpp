#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10;

int n;  // 节点数量

/**
 * BiconnectedComponent - TarjanAlgorithm
 *
 * problem: https://www.luogu.com.cn/problem/P3388
 * submission: https://www.luogu.com.cn/record/167339410
 */
namespace BiconnectedComponent {

    vector<vector<int>> G;

    void init() {
        G.resize(n + 2);
        for (int i = 1; i <= n; ++i) G[i].clear();
    }

    void add_undirected_edge(int u, int v) {
        G[u].push_back(v), G[v].push_back(u);
    }

    vector<bool> cut_vertex;

    void calc_cut_vertex() {
        cut_vertex.clear(), cut_vertex.resize(n + 2);

        int dfn_cnt = 0;
        vector<int> dfn(n + 2), low(n + 2);
        auto tarjan = [&](auto& self, int u, int root) -> void {
            ++dfn_cnt, dfn[u] = dfn_cnt, low[u] = dfn_cnt;
            int chd_cnt = 0;  // be used for check whether root is cut vertex
            for (const auto& v : G[u]) {
                if (!dfn[v]) {
                    ++chd_cnt;
                    self(self, v, root);
                    low[u] = min(low[u], low[v]);
                    if (u != root && low[v] >= dfn[u]) cut_vertex[u] = true;
                }
                low[u] = min(low[u], dfn[v]);
            }
            if (u == root && chd_cnt >= 2) cut_vertex[u] = true;
        };

        for (int i = 1; i <= n; ++i)
            if (!dfn[i]) tarjan(tarjan, i, i);
    }

    // 如果某个点是割点，那么去掉之后，连通块的数量会增加
    // 有个简单的办法，把割点堵住，然后每个块进行一次dfs
    // 就可以得到每一个点双连通分量的等价点（点双连通缩点）
    // 进行点双连通缩点之后得到森林。
    // https://www.luogu.com.cn/problem/P3469

    int bcc_cnt;
    // bcc[u] == id: 节点u属于第id个BCC
    int bcc[MAXN];
    // bcc_vertex[id] == {u1, u2, u3, ...}: 第id个BCC的所有节点
    vector<int> bcc_vertex[MAXN];
    vector<int> TREE[MAXN];

    void find_bcc(int u, int bcc_id) {
        bcc[u] = bcc_id, bcc_vertex[bcc_id].push_back(u);
        for (const auto& v : G[u]) {
            if (bcc[v] > 0) continue;
            find_bcc(v, bcc_id);
        }
    }

    // 点双连通分量缩点成森林，如果某个缩点后的位置siz超过1，那么就是一个去除割点
    // 之后的点双连通分量（计算的时候视情况要把周围的割点加回来）
    // 割点可以相邻，但是点双连通分量缩点之后并不会相邻，然后会变成树形DP问题
    void build_tree() {
        bcc_cnt = 0;
        fill(bcc + 1, bcc + 1 + n, 0);
        for (int i = 1; i <= n; ++i) bcc_vertex[i].clear();

        for (int i = 1; i <= n; ++i) {
            if (cut_vertex[i]) {
                ++bcc_cnt;
                bcc[i] = bcc_cnt;
                bcc_vertex[bcc_cnt].push_back(i);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (bcc[i] > 0) continue;
            find_bcc(i, ++bcc_cnt);
        }
        for (int bcc_u = 1; bcc_u <= bcc_cnt; ++bcc_u) {
            // 同一个点双连通分量里面的点是完全等价的，sort一下
            sort(bcc_vertex[bcc_u].begin(), bcc_vertex[bcc_u].end());
        }

        for (int i = 1; i <= n; ++i) TREE[i].clear();
        for (int u = 1; u <= n; ++u) {
            for (const auto& v : G[u]) {
                if (bcc[u] == bcc[v]) continue;  // 去除自环，不一定有必要
                TREE[bcc[u]].push_back(bcc[v]);
            }
        }
        // 去除平行边，不一定有必要
        auto sort_unique = [](vector<int>& vec) {
            sort(vec.begin(), vec.end());
            vec.erase(unique(vec.begin(), vec.end()), vec.end());
        };
        for (int bcc_u = 1; bcc_u <= bcc_cnt; ++bcc_u) {
            sort_unique(TREE[bcc_u]);
        }
    }

    // int siz[MAXN];
    // ll ans[MAXN];

    void dfs_tree(int bcc_u, int bcc_p) {
        // siz[bcc_u] = bcc_vertex[bcc_u].size();
        for (const auto& bcc_v : TREE[bcc_u]) {
            if (bcc_v == bcc_p) continue;
            dfs_tree(bcc_v, bcc_u);
            // siz[bcc_u] += siz[bcc_v];
        }
        // int siz_node_bcc_u = bcc_vertex[bcc_u].size();
        // ans[bcc_u] = 2LL * siz_node_bcc_u * (n - siz_node_bcc_u);
        // for (const auto& bcc_v : TREE[bcc_u]) {
        //     if (bcc_v == bcc_p) continue;
        //     int siz_other_v = (n - siz_node_bcc_u - siz[bcc_v]);
        //     ans[bcc_u] += 1LL * siz_other_v * siz[bcc_v];
        // }
        // int siz_bcc_p = (n - siz[bcc_u]);
        // ans[bcc_u] += 1LL * siz_bcc_p * (siz[bcc_u] - siz_node_bcc_u);
    }

}  // namespace BiconnectedComponent

using namespace BiconnectedComponent;
