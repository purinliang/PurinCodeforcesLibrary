#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 3e5 + 10;
const int MAXM = 3e5 + 10;

int n, m;
int w[MAXN];
ll v[MAXN];
bool is_pa[MAXN];
vector<int> ch[MAXN];
ll dp[2][2][MAXM];

int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) {
        int pa;
        cin >> w[i] >> v[i] >> pa;
        v[i] *= w[i];
        if (pa != 0) {
            ch[pa].push_back(i);
        } else {
            is_pa[i] = true;
        }
    }

    for (int t = 0; t <= 1; ++t) {
        for (int j = 0; j <= m; ++j) {
            dp[t][0][j] = 0;
            dp[t][1][j] = -LINF;
        }
    }

    for (int i = 1; i <= n; ++i) {
        int t = i & 1;
        for (int j = 0; j <= m; ++j) {
            dp[t][0][j] = max(dp[1 - t][0][j], dp[1 - t][1][j]);
            dp[t][1][j] = -LINF;
        }
        if (!is_pa[i]) {
            continue;
        }
        for (int j = m; j >= w[i]; --j) {
            dp[t][1][j] = max(dp[t][1][j], dp[t][0][j - w[i]] + v[i]);
        }
        for (int chi : ch[i]) {
            for (int j = m; j >= w[chi]; --j) {
                dp[t][1][j] = max(dp[t][1][j], dp[t][1][j - w[chi]] + v[chi]);
            }
        }
    }
    ll ans = max(dp[n & 1][0][m], dp[n & 1][1][m]);
    cout << ans << endl;
    return 0;
}
