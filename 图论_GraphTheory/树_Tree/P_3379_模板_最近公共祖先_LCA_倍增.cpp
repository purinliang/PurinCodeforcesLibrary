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
const int MAXLOGN = 20 + 1;

int n, q, root;
vector<int> G[MAXN];
int dep[MAXN];  // the amount of vertex from root to u
int prt[MAXN][MAXLOGN];

void dfs_lca(int u, int p) {
    dep[u] = dep[p] + 1;
    prt[u][0] = p;
    for (int i = 1; i < MAXLOGN; ++i) {
        prt[u][i] = prt[prt[u][i - 1]][i - 1];
    }
    for (auto& v : G[u]) {
        if (v == p) continue;
        dfs_lca(v, u);
    }
}

int lift_to_depth(int x, int depth) {
    for (int i = MAXLOGN - 1; i >= 0; --i) {
        if (dep[prt[x][i]] >= depth) x = prt[x][i];
    }
    return x;
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);  // let dep[x] >= dep[y]
    for (int i = MAXLOGN - 1; i >= 0; --i) {
        if (dep[prt[x][i]] >= dep[y]) x = prt[x][i];
    }
    // now dep[x] == dep[y]
    if (x == y) return x;
    for (int i = MAXLOGN - 1; i >= 0; --i) {
        if (prt[x][i] != prt[y][i]) {
            x = prt[x][i];
            y = prt[y][i];
        }
    }
    return prt[x][0];
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
    dfs_lca(root, 0);
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
