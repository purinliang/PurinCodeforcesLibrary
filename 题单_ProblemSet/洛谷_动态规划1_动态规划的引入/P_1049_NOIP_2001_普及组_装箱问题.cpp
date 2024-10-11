#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 2e4 + 10;

int m, n;
bitset<MAXN> dp;

int main() {
    cin >> m >> n;
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        int w;
        cin >> w;
        dp |= dp << w;
    }
    for (int j = m; j >= 0; --j) {
        if (dp[j]) {
            cout << m - j << endl;
            break;
        }
    }
    return 0;
}
