# PurinCodeforcesLibrary

布丁 Codeforces 库

## 洛谷模板

以下按照难度增序排列。标题中的数字表示其在 Codeforces 中的难度区间。

### 普及- (900~1100) ![](https://img.shields.io/badge/%E6%99%AE%E5%8F%8A---orange)

预计6月21日完成。

- [x] [栈](https://www.luogu.com.cn/problem/B3614)
    > 虽然 std::stack 默认实现是效率低下的 std::deque, 但足以应对大多数场景，也可以用 std::vector 直接模拟。跳过。
- [x] [快速幂](https://www.luogu.com.cn/problem/P1226)
    > 最简单的数论入门问题。跳过。
- [x] [队列](https://www.luogu.com.cn/problem/B3616)
    > 虽然 std::queue 默认实现是效率低下的 std::deque, 但足以应对大多数场景，也可以用 std::vector 和双指针直接模拟。跳过。
- [x] [双端队列](https://www.luogu.com.cn/problem/B3656)
    > 虽然 std::deque 效率很低下，但是本题构造的 1e6 个 std:deque 的场景太过极端。可以用 std::vector 和双指针直接模拟。跳过。
- [ ] [线性筛素数](https://www.luogu.com.cn/problem/P3383)
    > TODO
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

预计6月23日完成。

- [ ] 单调队列

- [ ] 裴蜀定理
- [ ] 单调栈
- [ ] 三分
- [ ] 字典树
- [ ] 并查集
- [ ] 树状数组1
- [ ] 树状数组2
- [ ] 最近公共祖先
- [ ] 最小生成树
- [ ] ST表
- [ ] 负环
- [ ] 单源最短路（标准版）

### 普及+/提高 (1600~1900) ![](https://img.shields.io/badge/%E6%99%AE%E5%8F%8A+/%E6%8F%90%E9%AB%98-green)

预计6月26日完成。

- [ ] 乘法逆元2
- [ ] 有理数取余
- [ ] 康托展开
- [ ] 差分约束

- [ ] 边双连通分量
- [ ] AC自动机
- [ ] 卢卡斯定理

### 提高+/省选- (2000~2300) ![](https://img.shields.io/badge/%E6%8F%90%E9%AB%98+/%E7%9C%81%E9%80%89---blue)

计划每天完成4个。

- [ ] 拉格朗日插值
- [ ] 可持久化线段树2
- [ ] 点分治
- [ ] 失配树
- [ ] 


### 省选/NOI- (2400~2900) ![](https://img.shields.io/badge/%E7%9C%81%E9%80%89/NOI---purple)

计划每天完成2个。

- [ ] 动态DP
- [ ] 可持久化文艺平衡树
- [ ] 回滚莫队/不删除莫队
- [ ] 杜教筛
- [ ] 二次剩余
- [ ] 三维偏序
- [ ] 最大流 加强版 预流推进
- [ ] 后缀排序
- [ ] Pollard-Rho
- [ ] 多项式乘法 FFT
- [ ] 高精度乘法
- [ ] 最小斯坦纳树

### NOI/NOI+/CTSC (3000-3500) ![](https://img.shields.io/badge/NOI/NOI+/CTSC-black)

暂时没有计划。

- [ ] 常数齐次线性递推
- [ ] N次剩余
- [ ] 一般图最大权匹配
- [ ] 插头DP
