题单地址：https://www.luogu.com.cn/training/211#problems

#### P1216 [USACO1.5] [IOI1994] 数字三角形 Number Triangles

注意行和列的下标，不要画成题目描述里面那种斜的，要画成输入那样的方格的，容易看出下标的关系。注意负数的情况。

#### P1048 [NOIP2005 普及组] 采药

经典01背包问题。01背包需要逆序枚举背包的重量。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

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

#### P2196 [NOIP1996 提高组] 挖地雷

这道题是要练习如何存储和输出DP的方案，存储方案目前想到的是用一个from数组表示当前点的最优决策，然后输出方案的方法是从最大的答案开始倒推，沿着from数组不断往前找，直到发现from数组为空，然后用递归把输出全部反向。

#### P1434 [SHOI2002] 滑雪

典型的DAG上DP，注意并不是最高的起点一定是最优的答案，很容易构造出一个反例：最高的起点被几个最低的点围起来，然后其他地方任意生成。

注意，**DAG上的DP最简单的写法应该是DFS实现记忆化搜索**，虽然上一道题“挖地雷”也是DAG上的DP，但是那道题的枚举顺序一定是从n到1枚举，所以直接写也没有问题。否则枚举顺序隐含的问题，最好直接写DFS实现记忆化搜索，不要试图通过排序然后枚举，也不要写拓扑排序。

#### P4017 最大食物链计数

这道题是DAG上的路径计数，需要记得取模。老规矩，DAG上的问题通通用记忆化搜索去做。

#### P1115 最大子段和

太水了，跳过。

#### P1802 5倍经验日

看起来像是一个01背包问题，先把失败的经验加上，然后抽象出01背包中的物品的价值为成功的经验和失败的经验的差值，01背包中物品的重量就是使用的属性药的数量。

注：确实就是个01背包问题，但是要吃个教训，就是 ```dp[0] = 0;``` 是必须的，如果给dp数组加入初始值，那么不能只在 ```dp[0]``` 中加入，要么就是全部加入，要么就是全部不加入最后特殊处理一下。这么严重的bug居然还能得90分？因为如果发生了一次成功的转移，这个bug就会被掩盖，只有当所有物品都无法转移时会出现问题。另外，**最好是要么就是全部加入初始值，要么就是全部不加入初始值**，这样可以**保持dp数组的含义明确**。

#### P1002 [NOIP2002 普及组] 过河卒

好无聊的题，就是把马和马的控制点ban掉，然后dp算一下路径数。

#### P3842 [TJOI2007] 线段

给一个很大的网格图，你从底部往上一行一行走，每次可以选择左右走或者向上走，但是不能向下走。图中有很多横着的一行一行的线段，你从(1, 1)开始走到(n, n)，图中要经过所有的线段。

推论：每次向上走的时候一定是在当前行有线段覆盖的部分的最左端点或者最右端点。

证明：首先，向上走的时候一定在有线段覆盖的部分，因为在每一行移动一格的代价是一样的，没有任何必要进行提前移动。同理，如果向上走的时候不在线段的最左或最右端点，那么一定当前行走了重复且无效的路。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3F3F3F3F;
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
```
