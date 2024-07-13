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

const int MAXN = 1e7 + 10;
int n, a[MAXN];

struct CartesianTree {
   private:
    vector<int> stk;

    void dfs(int u) {
        if (!u) {
            return;
        }
        dfs(lc[u]), dfs(rc[u]);
        // 如果有左子树，那么把左子树能管的最左边管了，否则只能管自己
        mostL[u] = lc[u] ? mostL[lc[u]] : u;
        // 如果有右子树，那么把右子树能管的最右边管了，否则只能管自己
        mostR[u] = rc[u] ? mostR[rc[u]] : u;
    }

    bool cmp(const int& x, const int& y) {
        // 修改这个参数调整是大根堆还是小根堆
        const bool SMALL_TOP_HEAP = true;
        return SMALL_TOP_HEAP ? x < y : x > y;
    }

   public:
    int n;
    int rt;
    vector<int> lc;
    vector<int> rc;
    vector<int> mostL;
    vector<int> mostR;

    void build(int* a, int _n) {
        n = _n;
        lc.clear(), lc.resize(n + 2);
        rc.clear(), rc.resize(n + 2);
        stk.clear(), stk.resize(n + 2);
        for (int i = 1, top = 0; i <= n; i++) {
            int k = top;
            while (k >= 1 && cmp(a[i], a[stk[k]])) {
                k--;
            }
            if (k >= 1) {
                // 节点i的权值>=栈顶节点的权值，挂在栈顶节点的右子树下
                rc[stk[k]] = i;
            }
            if (k + 1 <= top) {
                // 栈顶节点原本的右子树权值>节点i的权值，改为挂在节点i的左子树下
                lc[i] = stk[k + 1];
            }
            stk[++k] = i;
            top = k;
        }
        rt = stk[1];  // 笛卡尔树的根
    }

    // 计算每个节点作为最值（由cmp定义），最左和最右能管辖到哪里
    void calc_most_L_and_R(int n) {
        for (int i = 1; i <= n; ++i) {
            mostL[i] = n + 1;  // 初始化
            mostR[i] = 0;
        }
        dfs(rt);
    }

} c_tree;

void purin_init() {}

void purin_solve() {
    RD(n);
    RDN(a, n);
    c_tree.build(a, n);
    ll ansL = 0LL, ansR = 0LL;
    for (int i = 1; i <= n; ++i) {
        ansL ^= 1LL * i * (c_tree.lc[i] + 1);
        ansR ^= 1LL * i * (c_tree.rc[i] + 1);
    }
    WT(ansL, ansR);
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
