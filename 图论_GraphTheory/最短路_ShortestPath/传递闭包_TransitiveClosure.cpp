#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <int N>
struct FloydTransitiveClosure {
    int _n;
    bitset<N + 2> _reachable[N + 2];

    void init(int n) {
        _n = n;
        for (int i = 1; i <= _n; ++i) {
            _reachable[i] = bitset<N + 2>();
        }
    }

    void add_edge(int u, int v) { _reachable[u][v] = true; }

    void floyd() {
        for (int k = 1; k <= _n; ++k) {
            for (int i = 1; i <= _n; ++i) {
                if (_reachable[i][k]) {
                    _reachable[i] |= _reachable[k];
                }
            }
        }
    }

    void show_reachable() {
        for (int i = 1; i <= _n; ++i) {
            for (int j = 1; j <= _n; ++j) {
                cout << _reachable[i][j] << (" \n"[j == _n]);
            }
        }
    }
};

template <int N = 8>
void solve_floyd_transitive_closure(int n) {
    const int MAX_N = 2e3 + 10;
    if (n > N) {
        return solve_floyd_transitive_closure<min(2 * N, MAX_N)>(n);
    }
    FloydTransitiveClosure<N> graph;
    graph.init(n);

    // graph.add_edge(u, v);

    graph.floyd();
    graph.show_reachable();
}
