# 布丁 Codeforces 库

<!-- 有一个好完整的博客可以参考：https://www.cnblogs.com/GXZlegend/post-categories -->

<!-- ChenPeng 学弟分享的模板：https://www.yuque.com/capps/ze6wk1/heb78p9y3xvyrpz9#9407a1e0 -->

<!-- 自动check板子的库 library checker https://judge.yosupo.jp/ -->

<!-- TODO： 代码源夏令营的整理 -->

这一套模板是为了方便在 CF / LC 等线上比赛中复制粘贴而存在的，所以和 OI / ICPC 等线下比赛中使用的模板有较大差异。主要体现在以下方面：

|                | OI / ICPC 等线下比赛                         | CF / LC 等线上比赛             |
| -------------- | -------------------------------------------- | ------------------------------ |
| C++ 标准       | C++ 14，较旧                                 | C++ 20，较新                   |
| 代码长度       | 短，易于记忆，易于修改                       | 长，使用模板，不需要修改源代码 |
| 第三方库兼容性 | 不一定可以使用                               | 测试后可以稳定使用             |
| 全局变量       | 大量使用，方便修改，全局数组还可以避免栈溢出 | 可以按需要使用                 |
| 名空间         | 不需要使用                                   | 容易有命名冲突，需要使用       |
| 递归           | 避免在深度递归导致，避免栈溢出               | 问题不明显                     |

## 模板设计规则

### 远古遗产模板

我大学参加 XCPC 期间维护的远古遗物模板（收录于 cnblogs 的 [purinliang - 博客园](https://www.cnblogs.com/purinliang) ）充斥着大量 OI 风格和 C 语言风格的写法，例如各种全局变量、静态数组，虽然有 `struct` 或者 `namespace` 改进了全局变量被复制粘贴后遇到的名空间冲突的问题，但是还是不太方便：

1. 首先，静态数组的长度需要手动修改。对于很多数据结构与算法，比如线段树或者后缀自动机，其包含的节点个数并不完全等于数据规模（线段树为4倍，后缀自动机为2倍），虽然有常量辅助修改，但是经常容易忘记修改导致不必要的 dirt。对于可持久化数据结构，其内存使用量很容易算错。
2. 其次，是大量代码可读性极差的写法。如 `!p` 和 各种 magic number 的使用，导致代码非常不容易理解。还有很多代码缺乏必要的注释，我希望将此类问题尽可能消除掉。当时觉得很酷的很多奇怪的变量命名方法（比如把 `link` 记作 `lnk` 这样比较 less common 的做法。
3. 第三，代码的扩展性极差。比如线段树，我明知道他可以用来维护很多问题，但是因为之前的代码把线段树的组织管理部分和数据维护部分高度耦合，在修改时经常会出现问题，有时候还因为漏改 `int` 为 `ll` 导致不必要的 dirt。
4. 最严重的是，部分代码还有非常严重的 bug！比如没有验证到多组数据清空的问题导致异常（普通平衡树）。如果改为使用 `vector` 则可以很方便清空。

所以，我打算对远古遗物模板，进行一次全面的重新开发和验证，修订版称为第一代模板。

### 第一代模板

第一代模板的代码设计应遵循如下规则：

- **数组下标**：所有的数组，无论是 C 语言的数组，还是 C++ 语言的 `vector`，都必须是**以 1 作为**第一个真实元素的**下标**。包括各类自动机等存在特殊节点的数据结构。使用从 1 开始的下标有利于我的惯性思维的理解。
- **区间**：所有的区间都是**闭区间**，包括二分、三分、线段树，或者其他。使用闭区间有利于我的惯性思维的理解。
- **空间消耗**：所有的模板如果有空间消耗，都应该是动态申请空间的（也就是说模板内部不会存在和数据规模相关的 C 语言的数组），对于 `vector`，会多初始化（无论是 `reserve` 还是 `resize`） 2 个元素。由于 `vector` 在扩容的时候会使得引用失效，所以在进行可能导致新增元素的操作之前要 `reserve` 足够的空间。传引用的写法挺不好的，增加了这部分的复杂度（或者本身就应该用 `list` 而不是 `vector`？）。注意可持久化数据结构一次操作会新增多个元素。避免使用函数内可见的静态成员变量，静态成员变量会在复制多个方法时造成混淆。
- **初始化和清空**：所有的变量都应该有默认初始化的值，所有的自定义类都要通过构造函数来进行构造（不能随便定义也不能使用大括号）。在使用前统一进行 `clear` 和 `resize` 进行初始化，在使用后要视情况进行清空（尤其是对于查询操作而言，要对信息进行复原，或提供一个快速复原的方法）。
- **全局变量**：不要在模板中使用全局变量，在 `struct` 和 `class` 中要规定好哪些是私有成员哪些是公有成员。使用 `namespace` 的写法极不方便，建议后续**统一修改为 `struct` 的非静态成员**。
- **函数与方法**：对于有相对独立且意义较为明确的方法要抽出来，具体是用普通的私有方法实现还是用 lambda 表达式实现尚不明确，目前倾向于使用前者。对于部分特别简短的函数才可以使用后者。
- **全功能**：应包含所有常用的函数。应包含所有必要的安全性检查。如线段树或者 ST 表中的区间询问的左右端点的越界关系。如是否已经按使用说明进行了初始化（或者像组合数学那样进行自动初始化）。
- **宏定义**：允许使用宏定义对代码进行适当简化。
- **标准输入输出模板**：维持现状，为 C 语言的各种数据类型以及他们的 C 语言数组提供快速输入输出的方法。

PS：数据结构、数学、字符串、复杂的图论（例如双连通分量、强连通分量、网络流等）应该在这一代进行封装，简单的图论（如树的直径、最近公共祖先等）不应该在这一代进行封装。

### 第二代模板

在将远古遗物模板逐步改成第一代模板中使用 `vector` 的版本之后，原本表示节点数量、元素数量、栈顶等的 `cnt` 和 `top` 变量变得多余了，因为可以通过 `vector.size()` 方法取出，但是由于第一代模板为了某些历史原因下标统一是从 1 开始的，导致获取元素数量的方法总是需要另外减 1，非常不方便，而且对于 LeetCode 来说，从 0 开始并且前闭后开的区间，由于和各类编程语言的习惯一致，在简化代码的方面尤其优越。故希望开发第二代模板。

第二代模板的代码设计，在第一代模板的代码设计的基础上，应遵循如下改动后的规则：

- **数组下标**：所有的数组，无论是 C 语言的数组，还是 C++ 语言的 vector，都必须是**以 0 作为**第一个真实元素的**下标**。包括各类自动机等存在特殊节点的数据结构。使用从 0 开始的下标有利于简化代码长度以及和 C++ STL 形成统一风格。
- **区间**：所有的区间都是**前闭后开区间**，包括二分、三分、线段树，或者其他。使用闭区间有利于有利于简化代码长度以及和 C++ STL 形成统一风格。
- **空间消耗**：所有的模板如果有空间消耗，都应该是动态申请空间的（也就是说模板内部不会存在和数据规模相关的 C 语言的数组），对于 `vector`，不会多初始化任何元素。避免使用对 `vector` 使用引用。
- **在线算法**：应使用在线方法实现在线算法，例如不应该使用包含 `reserve` 的方法，可以提供包含 `reserve` 的额外初始化的函数。
- **标准输入输出模板**：应为所有的常用 STL 如各种类型的 `vector`，和 string 提供快速输入输出的方法。默认使用 `cin` / `cout` 作为输入方式，但是应该能一键重定向到 C 语言的输入输出方式。初步定义为 `pin` / `pout`。 
- **最小功能**：对于 ST表 或者倍增 LCA 等算法，将不同的元素定义到一起会方便维护，但是每次却要注释掉不需要使用的部分，线段树尤其是其中的重灾区。暂时不清楚这样的功能是否是必要的。
- **效率**：不包含输入输出的情况，应达到第一代模板 90% 的效率。 

第二代模板的开发与验证工作，目前并不着急进行。更换模板时需要一整套模板都进行更换（或者至少更换掉大部分常用的部分），否则会出现兼容问题。

PS：全部都应该在这一代进行封装，图论可以统一一个`vector`套`vector`的接口。可以参考下：https://github.com/goodstudyqaq/library2/blob/a95010727d019a2fd1d1486085dcee7130d0dbcc/graph/graph-template.hpp

## 模板目录

### 分类目录

以下收录已经被本次笔记整理确认过的模板，并按主题分类。

#### 数学

[组合数学_Combinatorics ver.2](https://github.com/purinliang/PurinCodeforcesLibrary/blob/main/%E6%95%B0%E5%AD%A6_Mathematics/%E7%BB%84%E5%90%88%E6%95%B0%E5%AD%A6/%E7%BB%84%E5%90%88%E6%95%B0%E5%AD%A6_Combinatorics.cpp)


### 洛谷难度分级目录

点此跳转：[洛谷模板目录](https://www.luogu.com.cn/problem/list?keyword=%E6%A8%A1%E6%9D%BF&type=AT%7CB%7CCF%7CP%7CSP%7CUVA&orderBy=difficulty&order=asc&page=1)

以下按照难度增序排列。标题中的数字表示其在 Codeforces 中的难度区间。

**TODO**: 认真阅读每一篇的题解，有时候有新的发现，比如单源最短路BellmanFord和传递闭包bitset。

#### 普及- (900~1100) ![](https://img.shields.io/badge/%E6%99%AE%E5%8F%8A---orange)

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
    > 6月22日，已完成。另外有同名的 Floyd 双指针判圈算法。
- [x] [拓扑排序](https://www.luogu.com.cn/problem/B3644)
    > 6月22日，已完成。

补充部分：

- [x] [二维前缀和]
    > 6月23日，已完成。

#### 普及/提高- (1200~1500) ![](https://img.shields.io/badge/%E6%99%AE%E5%8F%8A/%E6%8F%90%E9%AB%98---yellow)

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
- [x] [最近公共祖先 - LCA](https://www.luogu.com.cn/problem/P3379)
    > 7月17日，已完成：倍增算法、轻重链剖分算法。TODO： Tarjan 算法
- [ ] 最小生成树
    > Kruskal 算法， Prim 算法
- [x] [稀疏表 ST表](https://www.luogu.com.cn/problem/P3865)
    > 7月6日，已完成。其他替代品：线段树，笛卡尔树
- [x] [贝尔曼福特 BellmanFord - 负圈](https://www.luogu.com.cn/problem/P3385)
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

#### 普及+/提高 (1600~1900) ![](https://img.shields.io/badge/%E6%99%AE%E5%8F%8A+/%E6%8F%90%E9%AB%98-green)

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
- [x] [强连通分量 - 缩点](https://www.luogu.com.cn/problem/P3387)
    > 7月18日，已完成，目前只有 Kosaraju 算法。反正用起来差不多。

<br>

- [ ] 全源最短路Johnson
- [x] [线段树 - 多种区间修改](https://www.luogu.com.cn/problem/P3373)
    > 6月24日，已完成，终于搞明白为什么不能先处理加法标记再处理乘法标记了，因为没有乘法逆元。
- [ ] 最长公共子序列
- [ ] 二分图最大匹配
- [x] [点双连通分量 - 割点](https://www.luogu.com.cn/problem/P3388)
    > 7月18日，已完成。顺带实现了一个很奇怪的点双连通分量缩点算法。

<br>

- [x] [扩展欧几里得 ExtendedEuclid 算法 - 二元一次不定方程](https://www.luogu.com.cn/problem/P5656)
    > 6月25日，完成，注意 dx 和 dy 都是大于0的，并且他们会同步变化。
- [ ] [矩阵快速幂](https://www.luogu.com.cn/problem/P3390)
- [ ] 点双连通分量
- [ ] 卢卡斯定理

#### 提高+/省选- (2000~2300) ![](https://img.shields.io/badge/%E6%8F%90%E9%AB%98+/%E7%9C%81%E9%80%89---blue)

一共36题，计划每天完成4题。预计用时9天，7月5日完成。

- [ ] 拉格朗日插值
- [ ] 树上K级祖先
- [x] [笛卡尔树](https://www.luogu.com.cn/problem/P5854)
    > 7月13日，完成
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
- [x] [AC自动机 - 多模式串字符串匹配](https://www.luogu.com.cn/problem/P5357)
    > 7月11日，已完成
  
- [ ] 树同构
- [x] 可持久化权值线段树
    > 7月8日，已有

<br>

- [ ] 线段树分治 
    有一个线段树优化建图（对区间连边）
- [ ] 行列式求值
- [ ] 自适应辛普森法1
- [ ] 点分治1
- [ ] 扩展KMP/Z函数

<br>

- [ ] 失配树

#### 省选/NOI- (2400~2900) ![](https://img.shields.io/badge/%E7%9C%81%E9%80%89/NOI---purple)

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
- [x] [后缀自动机](https://www.luogu.com.cn/problem/P3804)
    > 7月12日，已完成。

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
- [x] [后缀数组](https://www.luogu.com.cn/problem/P3809)
    > 7月12日，已完成。TODO：height数组，lcp，还有其他常用方法。
- [ ] 多项式快速幂

<br>

- [ ] 有负环的费用流
- [ ] Pfaffian（线性代数的？）
- [ ] 最小割树
- [ ] 快速莫比乌斯变换，快速沃尔什变换
- [x] [PollardRho](https://www.luogu.com.cn/problem/P4718)
    > 7月15日，已完成。这个是质因数分解的 PollardRho 算法，另外有求离散对数的同名算法。

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

补充部分：

- [ ] [MillerRabin](https://www.luogu.com.cn/problem/P4718)
    >  7月15日，已完成。

#### NOI/NOI+/CTSC (3000-3500) ![](https://img.shields.io/badge/NOI/NOI+/CTSC-black)

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

---

TODO：

查看编译器优化的网站：https://gcc.godbolt.org/
计算几何的网站
生成树和图的网站

代码源2024夏令营的收集
洛谷题单广场上的题目
