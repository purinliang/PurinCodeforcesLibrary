#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 2024/06/23 https://ac.nowcoder.com/acm/contest/85187/F
 */
struct _01BreadthFirstSearch {
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

   private:
    struct Edge {
        int _v;
        int _w;
        Edge() {}
        Edge(int v, int w = 0) {
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
        // _rev_edge.clear(), _rev_edge.resize(_n + 2);
    }

    void add_edge(int u, int v, int w = 0) {
        assert(w == 0 || w == 1);
        _edge[u].push_back({v, w});
        // _rev_edge[v].push_back({u, w});
    }

    void _01_bfs(int s) {
        _dis.clear(), _dis.resize(_n + 2);
        for (int i = 1; i <= _n; ++i) {
            _dis[i] = LINF;
        }
        vector<bool> vis(_n + 2);
        deque<int> dq;
        _dis[s] = 0;
        dq.push_front(s);
        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            for (const Edge& e : _edge[u]) {
                int v = e._v;
                int w = e._w;
                if (_dis[v] <= _dis[u] + w) {
                    continue;
                }
                _dis[v] = _dis[u] + w;
                if (w == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }

    ll dis(int u) { return (u <= 0 || u > _n) ? LINF : _dis[u]; }

    void show_dis() {
        for (int i = 1; i <= _n; ++i) {
            cout << (_dis[i] == LINF ? "INF" : to_string(_dis[i])) << (" \n"[i == _n]);
        }
    }
};

_01BreadthFirstSearch graph;
