#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef LOCAL
#include ".\标准本地调试_StandardLocalDebug.h"
#else
#define D(...)
#define DN(arr, n)
#define DF()
#define ASSERT(x)

template <typename T>
void _RD(T& var) {
    cin >> var;
}

void _RD(char* var) {
    string str;
    cin >> str;
    strcpy(var + 1, str.c_str());
}

void RD() {}

template <typename T, typename... U>
void RD(T& Head, U&... Tail) {
    _RD(Head);
    RD(Tail...);
}

template <typename T>
void RDN(T* arr, int n) {
    for (int i = 1; i <= n; ++i) {
        _RD(arr[i]);
    }
}

template <typename T>
void _WT(const T& var) {
    cout << var;
}

void _WT(const char* var) {
    cout << (var + 1);
}

void WT() {}

template <typename T, typename... U>
void WT(const T& Head, const U&... Tail) {
    _WT(Head);
    cout << (sizeof...(Tail) ? " " : "\n");
    WT(Tail...);
}

void WTY(bool var, bool capital = false) {
    if (capital) {
        cout << (var ? "YES" : "NO") << "\n";
    } else {
        cout << (var ? "Yes" : "No") << "\n";
    }
}

template <typename T>
void WTN(T* arr, int n) {
    for (int i = 1; i <= n; ++i) {
        _WT(arr[i]);
        cout << (i < n ? " " : "\n");
    }
}

#endif

void purin_ios() {
    cout << fixed << setprecision(12);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#define endl "\n"
#define fout fflush(stdout)
}

void purin_init();
void purin_solve();

void purin_online_test(bool ignore_test_case_count) {
    purin_ios();
    purin_init();
    if (!ignore_test_case_count) {
        int t = 1;
        cin >> t;
        for (int i = 1; i <= t; ++i) {
            purin_solve();
        }
    } else {
        auto cin_eof = [&]() -> bool {
            char ch;
            while (cin >> ch) {
                if (!isspace(ch)) {
                    cin.unget();
                    return false;
                }
            }
            return cin.eof();
        };
        while (!cin_eof()) {
            purin_solve();
        }
    }
}

/* MY CODE BEGIN */

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

    bool cut_vertex[MAXN];

    void tarjan(int u, int root) {
        ++dfn_cnt, dfn[u] = dfn_cnt, low[u] = dfn_cnt;
        int chd_cnt = 0;  // be used for check whether root is cut vertex
        for (const auto& v : G[u]) {
            if (!dfn[v]) {
                ++chd_cnt;
                tarjan(v, root);
                low[u] = min(low[u], low[v]);
                if (u != root && low[v] >= dfn[u]) cut_vertex[u] = true;
            }
            low[u] = min(low[u], dfn[v]);
        }
        if (u == root && chd_cnt >= 2) cut_vertex[u] = true;
    }

    void calc_cut() {
        fill(dfn + 1, dfn + 1 + n, 0);
        fill(low + 1, low + 1 + n, 0);
        dfn_cnt = 0;
        fill(cut_vertex + 1, cut_vertex + 1 + n, false);
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i]) tarjan(i, i);
        }
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

    int siz[MAXN];
    ll ans[MAXN];

    void dfs_tree(int bcc_u, int bcc_p) {
        siz[bcc_u] = bcc_vertex[bcc_u].size();
        for (const auto& bcc_v : TREE[bcc_u]) {
            if (bcc_v == bcc_p) continue;
            dfs_tree(bcc_v, bcc_u);
            siz[bcc_u] += siz[bcc_v];
        }
        int siz_node_bcc_u = bcc_vertex[bcc_u].size();
        ans[bcc_u] = 2LL * siz_node_bcc_u * (n - siz_node_bcc_u);
        for (const auto& bcc_v : TREE[bcc_u]) {
            if (bcc_v == bcc_p) continue;
            int siz_other_v = (n - siz_node_bcc_u - siz[bcc_v]);
            ans[bcc_u] += 1LL * siz_other_v * siz[bcc_v];
        }
        int siz_bcc_p = (n - siz[bcc_u]);
        ans[bcc_u] += 1LL * siz_bcc_p * (siz[bcc_u] - siz_node_bcc_u);
    }

}  // namespace BiconnectedComponent

using namespace BiconnectedComponent;

void purin_init() {}

void purin_solve() {
    RD(n, m);
    init();
    while (m--) {
        int u, v;
        RD(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }
    calc_cut();
    build_tree();
    dfs_tree(1, 0);  // 从第一个点双连通分量遍历即可
    for (int i = 1; i <= n; ++i) {
        if (bcc_vertex[bcc[i]].size() != 1) {
            cout << 2 * (n - 1) << endl;  // 因为本题是连通图
            continue;
        }
        cout << ans[bcc[i]] << endl;
    }
}

int main() {
    const bool ignore_test_case_count = true;
#ifdef LOCAL
    purin_local_test(ignore_test_case_count);
#else
    purin_online_test(ignore_test_case_count);
#endif
    return 0;
}
