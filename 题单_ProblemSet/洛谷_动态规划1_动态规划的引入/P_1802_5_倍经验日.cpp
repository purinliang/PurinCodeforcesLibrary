#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 3e5 + 10;
const int MAXM = 3e5 + 10;

int n, m;

ll v[MAXN], w[MAXN];
ll dp[MAXM];

int main() {
    cin >> n >> m;
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        ll lose, win;
        cin >> lose >> win >> w[i];
        ans += lose;
        v[i] = win - lose;
    }
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= w[i]; --j) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    ans += dp[m];
    ans *= 5;
    cout << ans << endl;
    return 0;
}
