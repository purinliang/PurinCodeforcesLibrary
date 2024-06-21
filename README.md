# PurinCodeforcesLibrary

布丁 Codeforces 库

## 洛谷模板

点此跳转：[洛谷模板目录](https://www.luogu.com.cn/problem/list?keyword=%E6%A8%A1%E6%9D%BF&type=AT%7CB%7CCF%7CP%7CSP%7CUVA&orderBy=difficulty&order=asc&page=1)

以下按照难度增序排列。标题中的数字表示其在 Codeforces 中的难度区间。

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
- [x] [线性筛素数](https://www.luogu.com.cn/problem/P3383)
    > 6月21日，已完成。
<br>
- [x] [堆](https://www.luogu.com.cn/problem/P3378)
    > 直接用 std::priority_queue 代替。跳过。
- [x] [排序](https://www.luogu.com.cn/problem/P1177)
    > 直接用 std::sort 代替。跳过。
- [ ] [字符串哈希]( https://www.luogu.com.cn/problem/P3370)
    > TODO
- [ ] [全源最短路 - 弗洛伊德Floyd算法](https://www.luogu.com.cn/problem/B3647)
    > TODO
- [ ] [拓扑排序](https://www.luogu.com.cn/problem/B3644)
    > TODO

### 普及/提高- (1200~1500) ![](https://img.shields.io/badge/%E6%99%AE%E5%8F%8A/%E6%8F%90%E9%AB%98---yellow)

预计用时2天，6月23日完成。

- [ ] 单调队列
- [ ] 乘法逆元
- [ ] 裴蜀定理
- [ ] 单调栈
- [ ] 三分
<br>
- [ ] 传递闭包
- [ ] 字典树
- [ ] 并查集
- [ ] 树状数组1
- [ ] 单源最短路（弱化版）
<br>
- [ ] 树状数组2
- [ ] 最近公共祖先
- [ ] 最小生成树
- [ ] ST表
- [ ] 负环
<br>
- [ ] 单源最短路（标准版）

### 普及+/提高 (1600~1900) ![](https://img.shields.io/badge/%E6%99%AE%E5%8F%8A+/%E6%8F%90%E9%AB%98-green)

预计用时3天，6月26日完成。

- [ ] 乘法逆元2
- [ ] 有理数取余
- [ ] 康托展开
- [ ] 差分约束
- [ ] 边双连通分量
<br>
- [ ] 线段树1
- [ ] 欧拉路
- [ ] KMP
- [ ] Nim游戏
- [ ] 缩点
<br>
- [ ] 全源最短路Johnson
- [ ] 线段树2
- [ ] 最长公共子序列
- [ ] 二分图最大匹配
- [ ] 割点
<br>
- [ ] 扩展欧几里得算法
- [ ] 矩阵快速幂
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
- [ ] 普通平衡树
- [ ] 左偏树/可并堆
- [ ] 最小表示法
- [ ] Prufer序列
- [ ] Stoer-Wagner最小割
<br>
- [ ] Manacher回文串
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
- [ ] 文艺平衡树
- [ ] 扩展欧拉定理
- [ ] 线性基
- [ ] 2-SAT
- [ ] 可持久化线段树1（可持久化数组）
<br>
- [ ] 普通平衡树（数据加强版）
- [ ] 狄利克雷前缀和
- [ ] AC自动机
- [ ] 树同构
- [ ] 可持久化线段树2
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
- [ ] 可持久化文艺平衡树
- [ ] 下降幂多项式乘法
- [ ] 回文自动机PAM
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
