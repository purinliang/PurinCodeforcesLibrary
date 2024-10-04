#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1e3 + 10;
const int INF = 0x3F3F3F3F;

int n;
int a[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + a[i][j];
        }
    }
    int ans = -INF;
    for (int j = 1; j <= n; ++j) {
        ans = max(ans, dp[n][j]);
    }
    cout << ans << endl;
    return 0;
}
