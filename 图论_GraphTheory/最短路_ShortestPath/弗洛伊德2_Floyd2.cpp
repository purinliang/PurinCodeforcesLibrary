#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Floyd2 {
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
    vector<vector<ll>> _dis;

   public:
    void init(int n) {
        _n = n;
        _edge.clear(), _edge.resize(_n + 2);
        // _rev_edge.clear(), _rev_edge.resize(_n + 2);
    }

    void add_edge(int u, int v, ll w = 0LL) {
        _edge[u].push_back({v, w});
        // _rev_edge[v].push_back({u, w});
    }

    void floyd() {
        _dis.clear(), _dis.resize(_n + 2);
        for (int i = 1; i <= _n; ++i) {
            _dis[i].resize(_n + 2);
            for (int j = 1; j <= _n; ++j) {
                _dis[i][j] = LINF;
            }
            _dis[i][i] = 0;
        }
        for (int i = 1; i <= _n; ++i) {
            for (const Edge& e : _edge[i]) {
                int v = e._v;
                ll w = e._w;
                _dis[i][v] = min(_dis[i][v], w);
            }
        }
        for (int k = 1; k <= _n; ++k) {
            for (int i = 1; i <= _n; ++i) {
                for (int j = 1; j <= _n; ++j) {
                    _dis[i][j] = min(_dis[i][j], _dis[i][k] + _dis[k][j]);
                }
            }
        }
    }

    ll dis(int u, int v) { return (u <= 0 || u > _n || v <= 0 || v > _n) ? LINF : _dis[u][v]; }

    void show_dis() {
        for (int i = 1; i <= _n; ++i) {
            for (int j = 1; j <= _n; ++j) {
                cout << (_dis[i][j] == LINF ? "INF" : to_string(_dis[i][j])) << (" \n"[j == _n]);
            }
        }
    }
};

Floyd2 graph;
