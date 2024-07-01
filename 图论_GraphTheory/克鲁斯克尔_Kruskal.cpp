#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

    bool same(int x, int y) { return find(x) == find(y); }

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
};

struct KruskalMinimumSpanningTree {
   private:
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

    struct Edge {
        int _u;
        int _v;
        ll _w;
        Edge() {}
        Edge(int u, int v, ll w = 0LL) {
            _u = u;
            _v = v;
            _w = w;
        }
    };
    int _n;

    // TODO 全部改成普通前向星吧
    vector<vector<Edge>> _edge, _rev_edge;

   public:
    void init(int n) {
        _n = n;
        _edge.clear(), _edge.resize(_n + 2);
        // _rev_edge.clear(), _rev_edge.resize(_n + 2);
    }

    void add_edge(int u, int v, ll w = 0LL) {
        _edge[u].push_back({u, v, w});
        // _rev_edge[v].push_back({v, u, w});
    }

    ll kruskal() {
        vector<Edge> k_edge;
        for (int i = 1; i <= _n; ++i) {
            k_edge.insert(k_edge.end(), _edge[i].begin(), _edge[i].end());
        }
        sort(k_edge.begin(), k_edge.end(),
             [&](const Edge& e1, const Edge& e2) { return e1._w < e2._w; });

        DisjointSetUnion dsu;
        dsu.init(_n);
        ll sum_w = 0LL;
        int cnt_e = 0;
        for (const auto& e : k_edge) {
            if (!dsu.same(e._u, e._v)) {
                dsu.merge(e._u, e._v);
                sum_w += e._w;
                ++cnt_e;
            }
        }
        if (cnt_e != _n - 1) {
            sum_w = LINF;
        }
        return sum_w;
    }
};

KruskalMinimumSpanningTree graph;
