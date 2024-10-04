#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 3e5 + 10;

int n;
int L[MAXN], R[MAXN];
ll dp[MAXN][2];

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> L[i] >> R[i];
    }
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = LINF, dp[i][1] = LINF;
    }
    dp[1][0] = (R[1] - 1) + (R[1] - L[1]), dp[1][1] = R[1] - 1;
    for (int i = 2; i <= n; ++i) {
        // 枚举下一层从左/右端点向上走，以及左右端点位置
        vector<pair<int, int>> up = {{0, L[i - 1]}, {1, R[i - 1]}};
        for (auto [up_tp, up_pos] : up) {
            if (L[i] <= up_pos) {
                dp[i][0] = min(dp[i][0], dp[i - 1][up_tp] + 1 +
                                             2 * max(0, R[i] - up_pos) +
                                             (up_pos - L[i]));
            } else {
                dp[i][0] = min(dp[i][0], dp[i - 1][up_tp] + 1 +
                                             (R[i] - up_pos) + (R[i] - L[i]));
            }
            if (R[i] >= up_pos) {
                dp[i][1] = min(dp[i][1], dp[i - 1][up_tp] + 1 +
                                             2 * max(0, up_pos - L[i]) +
                                             (R[i] - up_pos));
            } else {
                dp[i][1] = min(dp[i][1], dp[i - 1][up_tp] + 1 +
                                             (up_pos - L[i]) + (R[i] - L[i]));
            }
        }
    }
    ll ans = min(dp[n][0] + (n - L[n]), dp[n][1] + (n - R[n]));
    cout << ans << endl;
    return 0;
}
