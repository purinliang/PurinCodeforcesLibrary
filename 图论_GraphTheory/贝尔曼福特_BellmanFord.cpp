#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
        // _rev_edge.clear(), _rev_edge.resize(_n + 2);
    }

    void add_edge(int u, int v, ll w = 0LL) {
        _edge[u].push_back({v, w});
        // _rev_edge[v].push_back({u, w});
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

    ll dis(int u) { return (u <= 0 || u > _n) ? LINF : _dis[u]; }

    void show_dis() {
        for (int i = 1; i <= _n; ++i) {
            cout << (_dis[i] == LINF ? "INF" : to_string(_dis[i])) << (" \n"[i == _n]);
        }
    }
};

BellmanFord graph;
