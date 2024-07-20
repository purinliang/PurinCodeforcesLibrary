#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * StronglyConnectedComponent - KosarajuAlgorithm - LeetCodeVersion
 *
 * problem:
 * https://leetcode.cn/problems/count-visited-nodes-in-a-directed-graph/description/
 * submission:
 * https://leetcode.cn/problems/count-visited-nodes-in-a-directed-graph/submissions/548149138/
 */
struct StronglyConnectedComponentKosarajuAlgorithm {
    typedef long long ll;

    int n;
    vector<vector<int>> G, GT;  // Transposed Graph

    void init(int n) {
        this->n = n;
        G.resize(n + 2), GT.resize(n + 2);
        for (int i = 1; i <= n; ++i) G[i].clear(), GT[i].clear();
    }

    void add_edge(int u, int v) {
        G[u].push_back(v), GT[v].push_back(u);
    }

    int scc_cnt;
    vector<int> scc;  // scc[u] == id: 节点u属于第id个SCC

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

        scc_cnt = 0, scc.resize(n + 2);
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

    vector<vector<int>> DAG;  // 缩点后的DAG，节点为scc_u
    vector<int> A;            // 节点scc_u的压缩信息
    vector<int> F;            // 从节点scc_u的开始的路径的最优信息

    void build_dag() {  // 对缩点之后的图建立DAG
        A.resize(scc_cnt + 2), DAG.resize(scc_cnt + 2);

        for (int u = 1; u <= n; ++u) {
            A[scc[u]] += 1 /* a[u] */;  // 压缩节点信息
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

    vector<int> calc_dag() {
        auto init_f_dag = [&]() {
            F.resize(scc_cnt + 2);
            fill(F.begin(), F.end(), -1);  // 以-1表示未访问
        };
        auto dfs_f_dag = [&](auto& self, int scc_u) {
            if (F[scc_u] != -1) return F[scc_u];
            int res = 0;
            for (const auto& scc_v : DAG[scc_u]) {
                // 统计以节点scc_u为起点的路径的最优信息
                res = max(res, self(self, scc_v));
            }
            res += A[scc_u];  // 加上节点scc_u的压缩信息
            F[scc_u] = res;
            return res;
        };

        init_f_dag();
        vector<int> ans(n);
        for (int u = 1; u <= n; ++u) {
            ans[u - 1] = dfs_f_dag(dfs_f_dag, scc[u]);
        }
        return ans;
    }
};
