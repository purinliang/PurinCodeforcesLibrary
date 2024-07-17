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

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

const int MAXN = 5e5 + 10;

int n, q, root;

vector<int> G[MAXN];
int dep[MAXN];  // the amount of vertex from root to u
int prt[MAXN];  // the parent-vertex of u
int siz[MAXN];  // the amount of vertex of subtree of u
int mch[MAXN];  // the sub-vertex of u with biggest siz
int top[MAXN];  // 当前节点 u 所在重链的顶部节点
int tid[MAXN];  // 当前节点经过轻重链剖分之后的编号，同一个子树位于连续区间内
int cnt;        // 计算轻重链剖分过程中的辅助变量

void dfs1(int u, int p) {  // p = 当前节点 u 的父节点
    dep[u] = dep[p] + 1, prt[u] = p;
    siz[u] = 1, mch[u] = 0;
    for (auto& v : G[u]) {
        if (v == p) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (mch[u] == 0 || siz[v] > siz[mch[u]]) {
            mch[u] = v;  // mch[u] = 当前节点 u 的最大的子节点
        }
    }
}

void dfs2(int u, int t) {  // t = 当前节点 u 所在重链的顶部节点
    top[u] = t, tid[u] = ++cnt;
    if (mch[u] != 0) dfs2(mch[u], t);  // 先遍历重儿子
    for (auto& v : G[u]) {             // 再遍历轻儿子
        if (v == prt[u] || v == mch[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    for (int tu = top[u], tv = top[v]; tu != tv; u = prt[tu], tu = top[u]) {
        if (dep[tu] < dep[tv]) swap(u, v), swap(tu, tv);
    }
    return (dep[u] <= dep[v]) ? u : v;
}

void init(int root) {
    cnt = 0;
    dfs1(root, 0);
    dfs2(root, root);
}

void purin_init() {}

void purin_solve() {
    RD(n, q, root);
    for (int i = 1; i <= n; ++i) {
        G[i].clear();
    }
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        RD(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    init(root);
    while (q--) {
        int u, v;
        RD(u, v);
        int lca_u_v = lca(u, v);
        WT(lca_u_v);
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
