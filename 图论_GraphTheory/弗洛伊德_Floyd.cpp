#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
