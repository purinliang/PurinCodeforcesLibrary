#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 1e3 + 10;

int n, m;
int h[MAXN][MAXN];
int dp[MAXN][MAXN];

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int dfs(int x, int y) {
    if (dp[x][y] != 0) {
        return dp[x][y];
    }
    int res = 1;
    for (int i = 0; i < 4; ++i) {
        int vx = x + dx[i];
        int vy = y + dy[i];
        if (vx < 1 || vx > n || vy < 1 || vy > m) {
            continue;
        }
        if (h[x][y] <= h[vx][vy]) {
            continue;
        }
        res = max(res, dfs(vx, vy) + 1);
    }
    dp[x][y] = res;
    return res;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> h[i][j];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ans = max(ans, dfs(i, j));
        }
    }
    cout << ans << endl;
    return 0;
}
