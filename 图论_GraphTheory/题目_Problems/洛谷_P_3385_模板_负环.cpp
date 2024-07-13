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

void purin_init() {}

struct BellmanFord {
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

   private:
    struct Edge {
        int _v;
        ll _w;
        Edge() {}
        Edge(int v, ll w = 0LL) {
            _v = v;
            _w = w;
        }
    };

    int _n;
    vector<vector<Edge>> _edge, _rev_edge;
    vector<ll> _dis;

   public:
    void init(int n) {
        _n = n;
        _edge.clear(), _edge.resize(_n + 2);
        _rev_edge.clear(), _rev_edge.resize(_n + 2);
    }

    void add_edge(int u, int v, ll w = 0LL) {
        _edge[u].push_back({v, w});
        _rev_edge[v].push_back({u, w});
    }

    bool bellman_ford(int s) {
        _dis.clear(), _dis.resize(_n + 2);
        for (int i = 1; i <= _n; ++i) {
            _dis[i] = LINF;
        }
        vector<bool> vis(_n + 2);
        vector<int> cnt(_n + 2);
        queue<int> que;
        _dis[s] = 0;
        vis[s] = true;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            vis[u] = false;
            if (++cnt[u] >= _n) {
                return true;
            }
            for (const Edge& e : _edge[u]) {
                int v = e._v;
                ll w = e._w;
                if (_dis[v] <= _dis[u] + w) {
                    continue;
                }
                _dis[v] = _dis[u] + w;
                if (vis[v] == false) {
                    vis[v] = true;
                    que.push(v);
                }
            }
        }
        return false;
    }
    void show_dis() {
        for (int i = 1; i <= _n; ++i) {
            cout << (_dis[i] == LINF ? "INF" : to_string(_dis[i])) << (" \n"[i == _n]);
        }
    }
};

BellmanFord graph;

void purin_solve() {
    int n, m;
    RD(n, m);
    graph.init(n);
    while (m--) {
        int u, v;
        ll w;
        RD(u, v, w);
        graph.add_edge(u, v, w);
        if (w >= 0) {
            graph.add_edge(v, u, w);
        }
    }

    bool neg_cycle = graph.bellman_ford(1);
    WTY(neg_cycle, true);
}

int main() {
    const bool ignore_test_case_count = false;
#ifdef LOCAL
    purin_local_test(ignore_test_case_count);
#else
    purin_online_test(ignore_test_case_count);
#endif
    return 0;
}
