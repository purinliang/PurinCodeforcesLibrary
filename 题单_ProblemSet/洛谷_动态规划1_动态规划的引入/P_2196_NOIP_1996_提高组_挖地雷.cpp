#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 3e5 + 10;

int n;
int a[MAXN];
int dp[MAXN];
int from[MAXN];
vector<int> G[MAXN];

void output(int x) {
    if (x != 0) {
        cout << x << " ";
    }
    if (from[x] != 0) {
        output(from[x]);
    }
}

int main() {
    cin >> n;
    a[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int j = 1; j <= n; ++j) {
        G[0].push_back(j);
    }
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int w;
            cin >> w;
            if (w > 0) {
                G[i].push_back(j);
            }
        }
    }
    for (int i = n; i >= 0; --i) {
        dp[i] = a[i];
        for (int j : G[i]) {
            if (dp[j] + a[i] > dp[i]) {
                from[i] = j;
                dp[i] = dp[j] + a[i];
            }
        }
    }
    output(0);
    cout << endl;
    cout << dp[0] << endl;
    return 0;
}
