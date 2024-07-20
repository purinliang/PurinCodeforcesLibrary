#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10;

int n;        // 节点数量
int a[MAXN];  // 节点的信息

/**
 * StronglyConnectedComponent - KosarajuAlgorithm
 *
 * KosarajuAlgorithm and TopoSort require the TransposedGraph,
 * costing extra memory usage. To find a faster way to solve the
 * same problem, see TarjanAlgorithm and MemorizedSearch.
 *
 * problem: https://www.luogu.com.cn/problem/B3609
 * submission: https://www.luogu.com.cn/record/166846520 July 18, 2024
 *
 * problem: https://www.luogu.com.cn/problem/P3387
 * submission: https://www.luogu.com.cn/record/167312876 July 20, 2024
 */
namespace StronglyConnectedComponentKosarajuAlgorithm {

    vector<int> G[MAXN], GT[MAXN];  // Transposed Graph

    void init() {
        for (int i = 1; i <= n; ++i) G[i].clear(), GT[i].clear();
    }

    void add_edge(int u, int v) {
        G[u].push_back(v), GT[v].push_back(u);
    }

    int scc_cnt, scc[MAXN];  // scc[u] == id: 节点u属于第id个SCC

    void kosaraju() {
        vector<int> stk;
        vector<bool> vis(n + 2);
        auto dfs_1 = [&](auto& self, int u) -> void {
            if (vis[u]) return;
            vis[u] = true;
            for (const auto& v : G[u]) self(self, v);
            stk.push_back(u);
        };
        for (int u = 1; u <= n; ++u) dfs_1(dfs_1, u);

        scc_cnt = 0, fill(scc + 1, scc + 1 + n, 0);
        auto dfs_2 = [&](auto& self, int u, int scc_id) -> void {
            scc[u] = scc_id;
            for (const auto& v : GT[u]) {
                if (scc[v] == 0) self(self, v, scc_id);
            }
        };
        for (int i = stk.size() - 1; i >= 0; --i) {
            if (int u = stk[i]; scc[u] == 0) dfs_2(dfs_2, u, ++scc_cnt);
        }
    }

    vector<int> DAG[MAXN];  // 缩点后的DAG，节点为scc_u
    ll A[MAXN];             // 节点scc_u的压缩信息
    ll F[MAXN];             // 从节点scc_u的开始的路径的最优信息

    void build_dag() {  // 对缩点之后的图建立DAG
        fill(A + 1, A + 1 + scc_cnt, 0LL);
        for (int scc_u = 1; scc_u <= scc_cnt; ++scc_u) DAG[scc_u].clear();

        for (int u = 1; u <= n; ++u) {
            A[scc[u]] += a[u];  // 压缩节点信息
            for (const auto& v : G[u]) {
                if (scc[u] == scc[v]) continue;  // 去除自环，一般有必要
                DAG[scc[u]].push_back(scc[v]);
            }
        }

        // // 去除平行边，一般没有必要
        // for (int scc_u = 1; scc_u <= scc_cnt; ++scc_u) {
        //     auto& vec = DAG[scc_u];
        //     sort(vec.begin(), vec.end());
        //     vec.erase(unique(vec.begin(), vec.end()), vec.end());
        // }
    }

    ll calc_dag() {
        auto init_f_dag = [&]() {
            fill(F + 1, F + 1 + scc_cnt, -1LL);  // 以-1表示未访问
        };
        auto dfs_f_dag = [&](auto& self, int scc_u) {
            if (F[scc_u] != -1) return F[scc_u];
            ll res = 0LL;
            for (const auto& scc_v : DAG[scc_u]) {
                // 统计以节点scc_u为起点的路径的最优信息
                res = max(res, self(self, scc_v));
            }
            res += A[scc_u];  // 加上节点scc_u的压缩信息
            F[scc_u] = res;
            return res;
        };

        init_f_dag();
        ll ans = 0LL;
        for (int u = 1; u <= n; ++u) {
            ans = max(ans, dfs_f_dag(dfs_f_dag, scc[u]));
        }
        return ans;
    }

}  // namespace StronglyConnectedComponentKosarajuAlgorithm

using namespace StronglyConnectedComponentKosarajuAlgorithm;
