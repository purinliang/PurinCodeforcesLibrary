# 布丁 Codeforces 库

<!-- 有一个好完整的博客可以参考：https://www.cnblogs.com/GXZlegend/post-categories -->

这一套模板是为了方便在 CF/LC 等线上比赛中复制粘贴而存在的，所以和 OI/ICPC 等线下比赛中使用的模板有较大差异。主要体现在以下方面：

|                | OI/ICPC 等线下比赛                           | CF/LC 等线上比赛               |
| -------------- | -------------------------------------------- | ------------------------------ |
| C++ 标准       | C++14，较旧                                  | C++20，较新                    |
| 代码长度       | 短，易于记忆，易于修改                       | 长，使用模板，不需要修改源代码 |
| 第三方库兼容性 | 不一定可以使用                               | 测试后可以稳定使用             |
| 全局变量       | 大量使用，方便修改，全局数组还可以避免栈溢出 | 可以按需要使用                 |
| 名空间         | 不需要使用                                   | 容易有命名冲突，需要使用       |
| 递归           | 避免在深度递归导致，避免栈溢出               | 问题不明显                     |

## 洛谷模板

点此跳转：[洛谷模板目录](https://www.luogu.com.cn/problem/list?keyword=%E6%A8%A1%E6%9D%BF&type=AT%7CB%7CCF%7CP%7CSP%7CUVA&orderBy=difficulty&order=asc&page=1)

以下按照难度增序排列。标题中的数字表示其在 Codeforces 中的难度区间。

TODO: 认真阅读每一篇的题解，有时候有新的发现，比如单源最短路BellmanFord和传递闭包bitset。

### 普及- (900~1100) ![](https://img.shields.io/badge/%E6%99%AE%E5%8F%8A---orange)

预计用时1天，6月21日完成。

- [x] [栈](https://www.luogu.com.cn/problem/B3614)
    > 虽然 std::stack 默认实现是效率低下的 std::deque, 但足以应对大多数场景，也可以用 std::vector 直接模拟。跳过。
- [x] [快速幂](https://www.luogu.com.cn/problem/P1226)
    > 最简单的数论入门问题。跳过。
- [x] [队列](https://www.luogu.com.cn/problem/B3616)
    > 虽然 std::queue 默认实现是效率低下的 std::deque, 但足以应对大多数场景，也可以用 std::vector 和双指针直接模拟。跳过。
- [x] [双端队列](https://www.luogu.com.cn/problem/B3656)
    > 虽然 std::deque 效率很低下，但是本题构造的 1e6 个 std:deque 的场景太过极端。可以用 std::vector 和双指针直接模拟。跳过。
- [x] [线性筛质数](https://www.luogu.com.cn/problem/P3383)
    > 6月21日，已完成。可以补充一个 bitset 版本的埃氏筛，速度更快。

<br>

- [x] [堆](https://www.luogu.com.cn/problem/P3378)
    > 直接用 std::priority_queue 代替。跳过。
- [x] [排序](https://www.luogu.com.cn/problem/P1177)
    > 直接用 std::sort 代替。跳过。
- [x] [字符串哈希]( https://www.luogu.com.cn/problem/P3370)
    > 这道题不是字符串哈希的真正用途，字符串哈希最大的用途是用于比较子串，可以用 Manacher 来验证。6月22日，已完成。
- [x] [弗洛伊德 Floyd - 全源最短路](https://www.luogu.com.cn/problem/B3647)
    > 6月22日，已完成。
- [x] [拓扑排序](https://www.luogu.com.cn/problem/B3644)
    > 6月22日，已完成。

补充部分：

- [x] [二维前缀和]
    > 6月23日，已完成。

### 普及/提高- (1200~1500) ![](https://img.shields.io/badge/%E6%99%AE%E5%8F%8A/%E6%8F%90%E9%AB%98---yellow)

预计用时2天，6月23日完成。

- [x] [单调队列](https://www.luogu.com.cn/problem/P1886)
    > 6月23日，已完成。双指针之间的最值，滑动窗口的最值。
- [x] [乘法逆元](https://www.luogu.com.cn/problem/P3811)
    > 费马小定理。跳过。
- [x] [贝祖 Bezout 定理](https://www.luogu.com.cn/problem/P4549)
    > n 个正负整数的线性组合能构成的最小正整数，全部求 gcd ，学会欧几里得算法就可以了。跳过。
- [x] [单调栈](https://www.luogu.com.cn/problem/P5788)
    > 6月23日，已完成。可以试试看笛卡尔树。
- [x] [三分搜索](https://www.luogu.com.cn/problem/P1883)
    > 6月23日，已完成。

<br>

- [x] [传递闭包](https://www.luogu.com.cn/problem/B3611)
    > 可以用 Floyd 去做，记得去掉 Floyd 默认的自环。也可以去用 bitset 去做。
- [ ] [字典树 - Trie](https://www.luogu.com.cn/problem/P8306)
    > 另外还需要一个衍生版本的 01 Trie 支持维护区间异或操作，二分操作，求最值操作。
- [x] [并查集](https://www.luogu.com.cn/problem/P3367)
    > 已有。跳过。
- [x] [树状数组 - 单点加值区间求和](https://www.luogu.com.cn/problem/P3374)
    > 单点加值，区间求和。已有。跳过。
- [x] [贝尔曼福特 BellmanFord - 单源最短路](https://www.luogu.com.cn/problem/P3371)
    > 6月22日，已完成。

<br>

- [x] [树状数组 - 区间加值单点求和](https://www.luogu.com.cn/problem/P3368)
    > 区间加值，单点求和。简单维护一下差分数组，已有。跳过。
- [ ] 最近公共祖先
    > 倍增算法， Tarjan 算法，树链剖分算法
- [ ] 最小生成树
    > Kruskal 算法， Prim 算法
- [x] [稀疏表 ST表](https://www.luogu.com.cn/problem/P3865)
    > 7月6日，已完成。其他替代品：线段树，笛卡尔树
- [x] [贝尔曼福特 BellmanFord - 负环](https://www.luogu.com.cn/problem/P3385)
    > 6月22日，已完成。最好再弄一个经典版本的 BellmanFord ，我记得还有一个题叫做“汇率兑换”的。

<br>

- [x] [迪克斯特拉 Dijkstra - 单源最短路](https://www.luogu.com.cn/problem/P4779)
    > 6月22日，已完成。

补充部分：

- [ ] 模整数
- [x] [组合数学](https://www.luogu.com.cn/problem/B3717)
    > 6月22日，已完成。
- [x] [01广度优先搜索 01BFS - 单源最短路](https://ac.nowcoder.com/acm/contest/85187/F)
    > 6月23日，已完成。

### 普及+/提高 (1600~1900) ![](https://img.shields.io/badge/%E6%99%AE%E5%8F%8A+/%E6%8F%90%E9%AB%98-green)

预计用时3天，6月26日完成。

- [x] [快速乘法逆元](https://www.luogu.com.cn/problem/P5431)
    > 毒瘤卡常题，强制使用C语言，跳过。
- [ ] [欧拉 Euler 定理](https://www.luogu.com.cn/problem/P2613)
- [ ] 康托展开
- [ ] 差分约束
- [ ] 边双连通分量

<br>

- [x] [线段树 - 区间修改](https://www.luogu.com.cn/problem/P3372)
    > 已有，跳过。
- [ ] [欧拉路径 Eulerian Path / 欧拉回路 Eulerian Cycle]
    > 6月24日
- [ ] KMP
    > 6月24日
- [x] [SG函数 - Nim游戏](https://www.luogu.com.cn/problem/P2197)
    > 6月24日，已完成。
- [ ] 缩点

<br>

- [ ] 全源最短路Johnson
- [x] [线段树 - 多种区间修改](https://www.luogu.com.cn/problem/P3373)
    > 6月24日，已完成，终于搞明白为什么不能先处理加法标记再处理乘法标记了，因为没有乘法逆元。
- [ ] 最长公共子序列
- [ ] 二分图最大匹配
- [ ] 割点

<br>

- [x] [扩展欧几里得 ExtendedEuclid 算法 - 二元一次不定方程](https://www.luogu.com.cn/problem/P5656)
    > 6月25日，完成，注意 dx 和 dy 都是大于0的，并且他们会同步变化。
- [ ] [矩阵快速幂](https://www.luogu.com.cn/problem/P3390)
- [ ] 点双连通分量
- [ ] 卢卡斯定理

### 提高+/省选- (2000~2300) ![](https://img.shields.io/badge/%E6%8F%90%E9%AB%98+/%E7%9C%81%E9%80%89---blue)

一共36题，计划每天完成4题。预计用时9天，7月5日完成。

- [ ] 拉格朗日插值
- [ ] 树上K级祖先
- [ ] 笛卡尔树
- [ ] 原根
- [ ] 最小费用最大流

<br>

- [x] 普通平衡树
    > 7月1日，已有
- [ ] 左偏树/可并堆
- [ ] 最小表示法
- [ ] Prufer序列
- [ ] Stoer-Wagner最小割

<br>

- [x] [Manacher - 回文串](https://www.luogu.com.cn/problem/P3805)
    > 7月11日，已完成。以 i 为对称中心的最长回文子串。
- [ ] 扫描线
- [ ] 中国剩余定理
- [ ] 二维凸包
- [ ] BSGS

<br>

- [ ] 子序列自动机
- [ ] 矩阵求逆
- [ ] 高斯消元法
- [ ] 最大流
- [ ] 重链剖分/树链剖分

<br>

- [x] 文艺平衡树
    > 7月1日，已有
- [ ] 扩展欧拉定理
- [ ] 线性基
- [ ] 2-SAT
- [x] 可持久化数组
    > 7月8日，已有

<br>

- [x] 普通平衡树（数据加强版）
    > 7月1日，已有
- [ ] 狄利克雷前缀和
- [ ] AC自动机 - 多模式串字符串匹配
  
- [ ] 树同构
- [x] 可持久化权值线段树
    > 7月8日，已有

<br>

- [ ] 线段树分治
- [ ] 行列式求值
- [ ] 自适应辛普森法1
- [ ] 点分治1
- [ ] 扩展KMP/Z函数

<br>

- [ ] 失配树

### 省选/NOI- (2400~2900) ![](https://img.shields.io/badge/%E7%9C%81%E9%80%89/NOI---purple)

一共63题，计划每天完成2题。预计用时32天，8月6日完成。

- [ ] 动态DP
- [x] 可持久化文艺平衡树
    > 7月10日，已完成
- [ ] 下降幂多项式乘法
- [x] [回文树 / 回文自动机 - 回文串](https://www.luogu.com.cn/problem/P5496)
    > 7月11日，已完成。以 i 为右端点的回文子串的数量。
- [ ] 回滚莫队/不删除莫队

<br>

- [ ] 树分块
- [ ] 线段树分裂
- [ ] Lyndon分解
- [ ] 静态仙人掌
- [ ] 旋转卡壳

<br>

- [ ] 杜教筛
- [ ] 二次剩余
- [ ] 广义后缀自动机 广义SAM
- [ ] 点分树
- [ ] BEST定理 欧拉回路计数

<br>

- [ ] 自适应辛普森法2
- [ ] 最小树形图
- [ ] 多项式对数函数
- [ ] 舞蹈链
- [ ] 后缀自动机SAM

<br>

- [ ] 三维偏序（CDQ分治、KDTree、bitset）
- [ ] 一般图最大匹配
- [ ] 扩展中国剩余定理
- [ ] 可持久化平衡树
- [ ] 扩展BSGS

<br>

- [ ] 后缀平衡树
- [ ] 矩阵树定理生成树计数
- [ ] 线段树3区间最值区间历史最值（吉司机线段树）
- [ ] 分治FFT
- [ ] 扩展卢卡斯定理

<br>

- [ ] 动态DP加强版
- [ ] 动态树LCT
- [ ] 李超线段树
- [ ] 最小斯坦纳树
- [ ] 最大流 加强版 预流推进

<br>

- [ ] 树套树
- [ ] 任意模多项式乘法
- [ ] 多项式乘法逆
- [ ] 后缀排序 后缀数组
- [ ] 多项式快速幂

<br>

- [ ] 有负环的费用流
- [ ] Pfaffian（线性代数的？）
- [ ] 最小割树
- [ ] 快速莫比乌斯变换，快速沃尔什变换
- [ ] PollardRho

<br>

- [ ] 威佐夫博弈
- [ ] LGV引理
- [ ] Meissel-Lehmer n以内质数的个数
- [ ] 特征多项式
- [ ] 组合数学 Polya定理

<br>

- [ ] 多项式除法
- [ ] 多项式开根（加强版）
- [ ] 子集卷积（枚举集合子集和按顺序枚举子集在oiwiki有）
- [ ] 多项式开根
- [ ] 线段树合并

<br>

- [ ] 多项式指数函数
- [ ] 莫队二次离线
- [ ] 多项式幂函数（加强版）
- [ ] Chirp Z-Transform 多项式求值？
- [ ] 二分图最大权完美匹配

<br>

- [ ] 多项式乘法FFT
- [ ] 类欧几里得算法
- [ ] 高精度乘法

### NOI/NOI+/CTSC (3000-3500) ![](https://img.shields.io/badge/NOI/NOI+/CTSC-black)

一共18题，暂时没有计划。

- [ ] 三维凸包
- [ ] 支配树
- [ ] 常数齐次线性递推
- [ ] k短路（可以用多路归并的方法做）
- [ ] 快速阶乘算法

<br>

- [ ] 多项式复合逆
- [ ] min_25筛
- [ ] 多项式多点求值
- [ ] 动态图连通性
- [ ] 多项式复合函数

<br>

- [ ] 常系数非齐次线性递推
- [ ] Berlekamp–Massey 算法 线性递推BM算法
- [ ] 多项式快速插值
- [ ] N次剩余
- [ ] Runs

<br>

- [ ] 一般图最大权匹配
- [ ] 插头DP
- [ ] 多项式复合函数（加强版）
- [ ] 整式递推

以下收录已经被本次笔记整理确认过的模板，并按主题分类。
