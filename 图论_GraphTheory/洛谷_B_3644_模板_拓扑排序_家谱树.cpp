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

struct TopoSort {
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

   private:
    struct Edge {
        int _v;
        // ll _w;
        Edge() {}
        Edge(int v, ll w = 0LL) {
            _v = v;
            // _w = w;
        }
    };

    int _n;
    vector<vector<Edge>> _edge, _rev_edge;

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

    vector<int> topo_sort_out() {
        vector<int> que, out_deg(_n + 2);
        for (int i = 1; i <= _n; ++i) {
            out_deg[i] = _edge[i].size();
            if (out_deg[i] == 0) {
                que.push_back(i);
            }
        }
        for (int i = 0; i < que.size(); ++i) {
            int u = que[i];
            for (const Edge& e : _rev_edge[u]) {
                int v = e._v;
                --out_deg[v];
                if (out_deg[v] == 0) {
                    que.push_back(v);
                }
            }
        }
        return que;
    }

    vector<int> topo_sort_in() {
        vector<int> que, in_deg(_n + 2);
        for (int i = 1; i <= _n; ++i) {
            in_deg[i] = _rev_edge[i].size();
            if (in_deg[i] == 0) {
                que.push_back(i);
            }
        }
        for (int i = 0; i < que.size(); ++i) {
            int u = que[i];
            for (const Edge& e : _edge[u]) {
                int v = e._v;
                --in_deg[v];
                if (in_deg[v] == 0) {
                    que.push_back(v);
                }
            }
        }
        return que;
    }
};

TopoSort graph;

void purin_init() {}

void purin_solve() {
    int n;
    RD(n);
    graph.init(n);
    for (int i = 1; i <= n; ++i) {
        int v;
        RD(v);
        while (v != 0) {
            graph.add_edge(i, v);
            D(v);
            RD(v);
            D(v);
        }
    }
    auto res = graph.topo_sort_in();
    // reverse(res.begin(), res.end());
    for (auto i : res) {
        cout << i << " ";
    }
    cout << endl;
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
