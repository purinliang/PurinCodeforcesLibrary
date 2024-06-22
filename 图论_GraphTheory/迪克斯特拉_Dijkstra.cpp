#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Dijkstra {
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
        // _rev_edge.clear(), _rev_edge.resize(_n + 2);
    }

    void add_edge(int u, int v, ll w = 0LL) {
        _edge[u].push_back({v, w});
        // _rev_edge[v].push_back({u, w});
    }

    void dijkstra(int s) {
        _dis.clear(), _dis.resize(_n + 2);
        for (int i = 1; i <= _n; ++i) {
            _dis[i] = LINF;
        }
        vector<bool> vis(_n + 2);
        priority_queue<pair<ll, int>> pq;
        _dis[s] = 0;
        pq.push({-_dis[s], s});
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            for (const Edge& e : _edge[u]) {
                int v = e._v;
                ll w = e._w;
                if (_dis[v] <= _dis[u] + w) {
                    continue;
                }
                _dis[v] = _dis[u] + w;
                pq.push({-_dis[v], v});
            }
        }
    }

    void show_dis() {
        for (int i = 1; i <= _n; ++i) {
            cout << (_dis[i] == LINF ? "INF" : to_string(_dis[i])) << (" \n"[i == _n]);
        }
    }
};

Dijkstra graph;
