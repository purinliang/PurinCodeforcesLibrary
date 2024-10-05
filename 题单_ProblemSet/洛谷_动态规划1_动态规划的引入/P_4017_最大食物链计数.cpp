#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 3e5 + 10;

const int MOD = 80112002;

int n, m;
vector<int> G[MAXN];
int indeg[MAXN];
ll dp[MAXN];

ll dfs(int u) {
    if (dp[u] != -1) {
        return dp[u];
    }
    if (G[u].size() == 0) {
        dp[u] = 1;
        return dp[u];
    }
    dp[u] = 0;
    for (int v : G[u]) {
        dp[u] += dfs(v);
    }
    dp[u] %= MOD;
    return dp[u];
}

int main() {
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> v >> u;
        G[u].push_back(v);
        ++indeg[v];
    }
    for (int i = 1; i <= n; ++i) {
        dp[i] = -1;
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (indeg[i] == 0) {
            ans += dfs(i);
        }
    }
    ans %= MOD;
    cout << ans << endl;
    return 0;
}
