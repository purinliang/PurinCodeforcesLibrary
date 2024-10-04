题单地址：https://www.luogu.com.cn/training/211#problems

#### P1216 \[USACO1.5] \[IOI1994]数字三角形 Number Triangles

注意行和列的下标，不要画成题目描述里面那种斜的，要画成输入那样的方格的，容易看出下标的关系。注意负数的情况。

#### P1048 \[NOIP2005 普及组] 采药

经典01背包问题。01背包需要逆序枚举背包的重量。

```cpp
const int MAXN = 3e5 + 10;
const int MAXM = 3e5 + 10;

int n, m;
int w[MAXN], v[MAXN];  // w[i]：第i个物品的重量； v[i]：第i个物品的价值
ll dp[MAXM];  // dp[j]：所装物品的总重量不超过j的背包的最大价值

int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i] >> v[i];
    }
    for (int i = 1; i <= n; ++i) {
        // 这里并不需要考虑 dp[j] = dp[j - 1] 的情况，这个是背包问题的性质
        for (int j = m; j >= w[i]; --j) {
            // 01背包需要逆序枚举背包的重量。
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    cout << dp[m] << endl;
    return 0;
}
```
