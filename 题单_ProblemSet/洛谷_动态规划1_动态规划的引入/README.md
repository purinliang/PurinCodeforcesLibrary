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

#### P1049 [NOIP2001 普及组] 装箱问题

简单的背包问题，只不过不再关心物品的价值，而是关心某个背包的重量是否能组合出来，这种题目的标准做法就是用个bool数组，然后状态转移方程改成 ```|=``` 运算。可以考虑用bitset进行加速，bitset加速大概是32~64倍速度，状态转移方程是 ```<<``` 、 ```>>``` 还有 ```|=``` 运算。

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

#### P1064 [NOIP2006 提高组] 金明的预算方案

这道题有点像简化版本的树形依赖背包，对于每组物品可以枚举如下决策：不购买任何物品、只购买主件、购买主件和附件A、购买主件和附件B、购买主件和附件AB。因为这个题目的附件数量不超过2，所以可以直接这样搞，否则要分 ```dp[i][0/1]``` 表示第i组物品不购买任何物品/购买主件的最优结果，在购买主件时从“当前行”的0转移到1，在购买附件是从“当前行”的1 **“逆序更新”** 转移到1。

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 3e5 + 10;
const int MAXM = 3e5 + 10;

int n, m;
int w[MAXN];
ll v[MAXN];
bool is_pa[MAXN];
vector<int> ch[MAXN];
ll dp[2][2][MAXM];

int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) {
        int pa;
        cin >> w[i] >> v[i] >> pa;
        v[i] *= w[i];
        if (pa != 0) {
            ch[pa].push_back(i);
        } else {
            is_pa[i] = true;
        }
    }

    for (int t = 0; t <= 1; ++t) {
        for (int j = 0; j <= m; ++j) {
            dp[t][0][j] = 0;
            dp[t][1][j] = -LINF;
        }
    }

    for (int i = 1; i <= n; ++i) {
        int t = i & 1;
        for (int j = 0; j <= m; ++j) {
            // 购买第i个主件，从购买/不购买第i-1个主件转移
            dp[t][0][j] = max(dp[1 - t][0][j], dp[1 - t][1][j]);
            dp[t][1][j] = -LINF;
        }
        if (!is_pa[i]) {
            continue;
        }
        for (int j = m; j >= w[i]; --j) {
            // 购买第i个主件，从不购买第i个主件转移，而不是只从不购买第i-1个主件转移
            dp[t][1][j] = max(dp[t][1][j], dp[t][0][j - w[i]] + v[i]);
        }
        for (int chi : ch[i]) {
            for (int j = m; j >= w[chi]; --j) {
                // 购买第chi个附件，从购买第i个主件转移
                dp[t][1][j] = max(dp[t][1][j], dp[t][1][j - w[chi]] + v[chi]);
            }
        }
    }
    ll ans = max(dp[n & 1][0][m], dp[n & 1][1][m]);
    cout << ans << endl;
    return 0;
}
```

#### P2392 kkksc03考前临时抱佛脚

这道题当时第一次看觉得很难，现在再重新看一次觉得又很水，其实这道题里面的四个科目是互相不影响的，只需要独立计算四次答案全部加起来就行。对于同一个科目，其实就是枚举一个最小的背包容量M，使得可以把这些科目分成两部分，两个部分都不超过M。这个当然可以二分去做，但是仔细一想，直接用背包计算出这个科目能组合出的背包的容量，记科目的总时长为 M ，那么从 ceil(M/2) 开始向上找第一个能组合出的背包的容量就是答案。

```cpp
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
```
