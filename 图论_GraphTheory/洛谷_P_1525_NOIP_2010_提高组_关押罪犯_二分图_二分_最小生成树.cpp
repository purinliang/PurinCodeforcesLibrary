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

const int MAXN = 1e5 + 10;
int n, m;
array<int, 3> e[MAXN];

struct DisjointSetUnion {
    int _n;
    vector<int> _prt, _siz;

    void init(int n) {
        _n = n;
        _prt.clear(), _prt.resize(_n + 2);
        _siz.clear(), _siz.resize(_n + 2);
        for (int i = 1; i <= _n; i++) {
            _prt[i] = i, _siz[i] = 1;
        }
    }

    int find(int x) {
        int rt = x;
        while (_prt[rt] != rt) {
            rt = _prt[rt];
        }
        int prtx = _prt[x];
        while (prtx != rt) {
            _prt[x] = rt;
            x = prtx, prtx = _prt[x];
        }
        return rt;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) {
            return false;
        }
        if (_siz[rx] < _siz[ry]) {
            swap(rx, ry);
        }
        _prt[ry] = rx, _siz[rx] += _siz[ry];
        return true;
    }

} dsu;

void purin_init() {}

bool check(int M) {
    dsu.init(2 * n);
    for (int i = m; i >= 1; --i) {
        auto [w, u, v] = e[i];
        if (w > M) {
            dsu.merge(u + n, v);
            dsu.merge(v + n, u);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (dsu.same(i, i + n)) {
            return false;
        }
    }
    return true;
}

void purin_solve() {
    RD(n, m);
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        RD(u, v, w);
        e[i] = {w, u, v};
    }
    sort(e + 1, e + 1 + m);
    int L = 0, R = 1e9;
    while (L < R) {
        int M = (L + R) >> 1;
        if (check(M)) {
            R = M;
        } else {
            L = M + 1;
        }
    }
    WT(L);
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
