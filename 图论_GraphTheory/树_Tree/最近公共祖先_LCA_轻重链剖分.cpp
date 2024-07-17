#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 计算最近公共祖先（LCA）的轻重链剖分算法
 * 比倍增算法快50%，空间复杂度为线性（不过辅助数组较多，空间节约60%）。
 */

const int MAXN = 3e5 + 10;

vector<int> G[MAXN];
int dep[MAXN];  // the amount of vertex from root to u
int prt[MAXN];  // the parent-vertex of u
int siz[MAXN];  // the amount of vertex of subtree of u
int mch[MAXN];  // the sub-vertex of u with biggest siz
int top[MAXN];  // 当前节点 u 所在重链的顶部节点
int tid[MAXN];  // 当前节点经过轻重链剖分之后的编号，同一个子树位于连续区间内
int cnt;        // 计算轻重链剖分过程中的辅助变量

void dfs1(int u, int p) {  // p = 当前节点 u 的父节点
    dep[u] = dep[p] + 1, prt[u] = p;
    siz[u] = 1, mch[u] = 0;
    for (auto& v : G[u]) {
        if (v == p) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (mch[u] == 0 || siz[v] > siz[mch[u]]) {
            mch[u] = v;  // mch[u] = 当前节点 u 的最大的子节点
        }
    }
}

void dfs2(int u, int t) {  // t = 当前节点 u 所在重链的顶部节点
    top[u] = t, tid[u] = ++cnt;
    if (mch[u] != 0) dfs2(mch[u], t);  // 先遍历重儿子
    for (auto& v : G[u]) {             // 再遍历轻儿子
        if (v == prt[u] || v == mch[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    for (int tu = top[u], tv = top[v]; tu != tv; u = prt[tu], tu = top[u]) {
        if (dep[tu] < dep[tv]) swap(u, v), swap(tu, tv);
    }
    return (dep[u] <= dep[v]) ? u : v;
}

void init(int root) {
    cnt = 0;
    dfs1(root, 0);
    dfs2(root, root);
}
