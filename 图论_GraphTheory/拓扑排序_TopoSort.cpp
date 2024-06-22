#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
