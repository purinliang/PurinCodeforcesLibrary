#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 20 + 5;

int n = 20;
int tx, ty, mx, my;
bool used[MAXN][MAXN];
ll dp[MAXN][MAXN];

bool valid(int x, int y) {
    if (x < 0 || x > tx || y < 0 || y > ty) {
        return false;
    }
    return true;
}

int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

int main() {
    cin >> tx >> ty >> mx >> my;
    used[mx][my] = true;
    for (int i = 0; i < 8; ++i) {
        int vx = mx + dx[i];
        int vy = my + dy[i];
        if (valid(vx, vy)) {
            used[vx][vy] = true;
        }
    }
    for (int i = 0; i <= tx; ++i) {
        for (int j = 0; j <= ty; ++j) {
            if (used[i][j]) {
                dp[i][j] = 0;
            } else {
                if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                }
                if (valid(i - 1, j) && !used[i - 1][j]) {
                    dp[i][j] += dp[i - 1][j];
                }
                if (valid(i, j - 1) && !used[i][j - 1]) {
                    dp[i][j] += dp[i][j - 1];
                }
            }
        }
    }
    cout << dp[tx][ty] << endl;
    return 0;
}
