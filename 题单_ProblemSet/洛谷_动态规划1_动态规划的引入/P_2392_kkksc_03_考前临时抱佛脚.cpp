#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXM = 1200 + 10;

int slen = 4, s[5];

int main() {
    for (int si = 1; si <= slen; ++si) {
        cin >> s[si];
    }
    int ans = 0;
    for (int si = 1; si <= slen; ++si) {
        int n = s[si], m = 0;
        bitset<MAXM> dp;
        dp[0] = 1;
        // 也可以直接用字符串赋值 bitset<MAXN> dp("1");
        for (int i = 1; i <= n; ++i) {
            int w;
            cin >> w;
            m += w;
            dp |= dp << w;
        }
        for (int j = (m + 1) / 2; j <= m; ++j) {
            if (dp[j]) {
                ans += j;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
