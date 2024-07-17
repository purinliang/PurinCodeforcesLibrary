#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 3e5 + 10;
const int MAXLOGN = 20 + 1;

vector<int> G[MAXN];
int dep[MAXN];  // the amount of vertex from root to u
int prt[MAXN][MAXLOGN];

void dfs_lca(int u, int p) {
    dep[u] = dep[p] + 1;
    prt[u][0] = p;
    for (int i = 1; i < MAXLOGN; ++i) {
        prt[u][i] = prt[prt[u][i - 1]][i - 1];
    }
    for (auto& v : G[u]) {
        if (v == p) continue;
        dfs_lca(v, u);
    }
}

int lift_to_depth(int x, int depth) {
    for (int i = MAXLOGN - 1; i >= 0; --i) {
        if (dep[prt[x][i]] >= depth) x = prt[x][i];
    }
    return x;
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);  // let dep[x] >= dep[y]
    for (int i = MAXLOGN - 1; i >= 0; --i) {
        if (dep[prt[x][i]] >= dep[y]) x = prt[x][i];
    }
    // now dep[x] == dep[y]
    if (x == y) return x;
    for (int i = MAXLOGN - 1; i >= 0; --i) {
        if (prt[x][i] != prt[y][i]) {
            x = prt[x][i];
            y = prt[y][i];
        }
    }
    return prt[x][0];
}
