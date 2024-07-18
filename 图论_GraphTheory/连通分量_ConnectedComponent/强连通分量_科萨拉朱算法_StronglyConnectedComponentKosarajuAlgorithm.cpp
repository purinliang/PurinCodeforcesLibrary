#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * StronglyConnectedComponent - KosarajuAlgorithm
 *
 * problem: https://www.luogu.com.cn/problem/B3609
 * submission: https://www.luogu.com.cn/record/166846520 July 18, 2024
 */
namespace StronglyConnectedComponentKosarajuAlgorithm {
    const int MAXN = 3e5 + 10;

    int n;
    vector<int> G[MAXN];
    vector<int> GT[MAXN];  // G的反向图

    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; ++i) {
            G[i].clear();
            GT[i].clear();
        }
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
        GT[v].push_back(u);
    }

    bool vis[MAXN];
    vector<int> stk;
    int scc_cnt;
    // scc[u] == id: 节点u属于第id个SCC
    int scc[MAXN];
    // scc_vertex[id] == {u1, u2, u3, ...}: 第id个SCC的所有节点
    vector<int> scc_vertex[MAXN];

    void dfs_1(int u) {
        if (vis[u]) return;
        vis[u] = true;
        for (const auto& v : G[u]) {
            dfs_1(v);
        }
        stk.push_back(u);
    }

    void dfs_2(int u) {
        scc[u] = scc_cnt, scc_vertex[scc_cnt].push_back(u);
        for (const auto& v : GT[u]) {
            if (scc[v] > 0) continue;
            dfs_2(v);
        }
    }

    void kosaraju() {
        fill(vis + 1, vis + 1 + n, false);
        stk.clear();
        for (int i = 1; i <= n; ++i) dfs_1(i);

        scc_cnt = 0;
        fill(scc + 1, scc + 1 + n, 0);
        for (int i = 1; i <= n; ++i) scc_vertex[i].clear();
        reverse(stk.begin(), stk.end());
        for (const auto& u : stk) {
            if (scc[u] > 0) continue;
            ++scc_cnt;
            dfs_2(u);
        }
        for (int scc_u = 1; scc_u <= scc_cnt; ++scc_u) {
            // 同一个强连通分量里面的点是完全等价的，sort一下
            sort(scc_vertex[scc_u].begin(), scc_vertex[scc_u].end());
        }
    }

    vector<int> DAG[MAXN];   // 缩点之后的DAG，节点为scc_u
    vector<int> DAGT[MAXN];  // DAG的反向图

    void build_dag() {  // 对缩点之后的图建立DAG
        for (int i = 1; i <= n; ++i) DAG[i].clear(), DAGT[i].clear();
        for (int u = 1; u <= n; ++u) {
            for (const auto& v : G[u]) {
                DAG[scc[u]].push_back(scc[v]);
                DAGT[scc[v]].push_back(scc[u]);
            }
        }
        // 现在DAG中包含平行边和自环
        // 去除平行边，不一定有必要
        auto sort_unique = [](vector<int>& vec) {
            sort(vec.begin(), vec.end());
            vec.erase(unique(vec.begin(), vec.end()), vec.end());
        };
        for (int scc_u = 1; scc_u <= scc_cnt; ++scc_u) {
            sort_unique(DAG[scc_u]);
            sort_unique(DAGT[scc_u]);
        }
        // 去除自环，不一定有必要
        auto remove_loop = [](vector<int>& vec, int u) {
            vector<int> tmp;
            for (const auto& v : vec) {
                if (v == u) continue;
                tmp.push_back(v);
            }
            vec = tmp;
        };
        for (int scc_u = 1; scc_u <= scc_cnt; ++scc_u) {
            remove_loop(DAG[scc_u], scc_u);
            remove_loop(DAGT[scc_u], scc_u);
        }
    }

    void topo_dag() {
        // 出度为0的先出队
        queue<int> que;
        vector<int> out_deg(scc_cnt + 2);
        for (int scc_u = 1; scc_u <= scc_cnt; ++scc_u) {
            out_deg[scc_u] = DAG[scc_u].size();
            if (out_deg[scc_u] == 0) que.push(scc_u);
        }
        while (!que.empty()) {
            int scc_u = que.front();
            que.pop();
            // 在这里处理第scc_u个强连通分量
            for (const auto& scc_v : DAGT[scc_u]) {
                --out_deg[scc_v];
                if (out_deg[scc_v] == 0) que.push(scc_v);
                // 在这里处理转移信息给第scc_v个强连通分量
            }
        }
    }

}  // namespace StronglyConnectedComponentKosarajuAlgorithm

using namespace StronglyConnectedComponentKosarajuAlgorithm;

/**
 * 下面的代码未验证
 */
namespace StronglyConnectedComponentDAG {
    vector<int> DAG[MAXN];   // 缩点之后的DAG，节点为scc_u
    vector<int> DAGT[MAXN];  // DAG的反向图

    void build_dag() {  // 对缩点之后的图建立DAG
        for (int i = 1; i <= n; ++i) DAG[i].clear(), DAGT[i].clear();
        for (int u = 1; u <= n; ++u) {
            for (const auto& v : G[u]) {
                DAG[scc[u]].push_back(scc[v]);
                DAGT[scc[v]].push_back(scc[u]);
            }
        }
        // 现在DAG中包含平行边和自环
        // 去除平行边，不一定有必要
        auto sort_unique = [](vector<int>& vec) {
            sort(vec.begin(), vec.end());
            vec.erase(unique(vec.begin(), vec.end()), vec.end());
        };
        for (int scc_u = 1; scc_u <= scc_cnt; ++scc_u) {
            sort_unique(DAG[scc_u]);
            sort_unique(DAGT[scc_u]);
        }
        // 去除自环，不一定有必要
        auto remove_loop = [](vector<int>& vec, int u) {
            vector<int> tmp;
            for (const auto& v : vec) {
                if (v == u) continue;
                tmp.push_back(v);
            }
            vec = tmp;
        };
        for (int scc_u = 1; scc_u <= scc_cnt; ++scc_u) {
            remove_loop(DAG[scc_u], scc_u);
            remove_loop(DAGT[scc_u], scc_u);
        }
    }

    void topo_dag() {
        // 出度为0的先出队
        queue<int> que;
        vector<int> out_deg(scc_cnt + 2);
        for (int scc_u = 1; scc_u <= scc_cnt; ++scc_u) {
            out_deg[scc_u] = DAG[scc_u].size();
            if (out_deg[scc_u] == 0) que.push(scc_u);
        }
        while (!que.empty()) {
            int scc_u = que.front();
            que.pop();
            // 在这里处理第scc_u个强连通分量
            for (const auto& scc_v : DAGT[scc_u]) {
                --out_deg[scc_v];
                if (out_deg[scc_v] == 0) que.push(scc_v);
                // 在这里处理转移信息给第scc_v个强连通分量
            }
        }
    }

}  // namespace StronglyConnectedComponentDAG

using namespace StronglyConnectedComponentDAG;
