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

struct Floyd {
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

    int _n;
    vector<vector<ll>> _dis;

    void init(int n) {
        _n = n;
        _dis.clear(), _dis.resize(_n + 2);
        for (int i = 1; i <= _n; ++i) {
            _dis[i].resize(_n + 2);
            for (int j = 1; j <= n; ++j) {
                _dis[i][j] = LINF;
            }
            _dis[i][i] = 0;
        }
    }

    void add_edge(int u, int v, ll w) { _dis[u][v] = min(_dis[u][v], w); }

    void floyd() {
        for (int k = 1; k <= _n; ++k) {
            for (int i = 1; i <= _n; ++i) {
                for (int j = 1; j <= _n; ++j) {
                    _dis[i][j] = min(_dis[i][j], _dis[i][k] + _dis[k][j]);
                }
            }
        }
    }

    void show_dis() {
        for (int i = 1; i <= _n; ++i) {
            for (int j = 1; j <= _n; ++j) {
                cout << (_dis[i][j] == LINF ? "INF" : to_string(_dis[i][j])) << (" \n"[j == _n]);
            }
        }
    }
};

Floyd graph;

void purin_init() {}

void purin_solve() {
    int n, m;
    RD(n, m);
    D(n, m);
    graph.init(n);
    // graph.show_dis();
    while (m--) {
        int u, v, w;
        RD(u, v, w);
        D(u, v, w);
        graph.add_edge(u, v, w);
        graph.add_edge(v, u, w);
        // graph.show_dis();
    }
    graph.floyd();
    graph.show_dis();
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
