#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static const int MAXN = 500 + 10;
static const int INF = 0x3F3F3F3F;

int n;
int a[MAXN];
int sum[MAXN];
int dp[MAXN][MAXN];

void calc_dp() {
    for (int i = 0; i <= n + 1; ++i) {
        sum[i] = 0;
        for (int j = 0; j <= n + 1; ++j) {
            dp[i][j] = -INF;
        }
    }
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + a[i];
        dp[i][i] = a[i];
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            for (int k = i; k + 1 <= j; ++k) {
                dp[i][j] = max(dp[i][j], sum[j] - sum[i - 1] + dp[i][k] + dp[k + 1][j]);
            }
        }
    }
}
