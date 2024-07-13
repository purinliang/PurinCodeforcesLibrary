#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct CartesianTree {
   private:
    vector<int> stk;

    void dfs(int u) {
        if (!u) {
            return;
        }
        dfs(lc[u]), dfs(rc[u]);
        // 如果有左子树，那么把左子树能管的最左边管了，否则只能管自己
        mostL[u] = lc[u] ? mostL[lc[u]] : u;
        // 如果有右子树，那么把右子树能管的最右边管了，否则只能管自己
        mostR[u] = rc[u] ? mostR[rc[u]] : u;
    }

    bool cmp(const int& x, const int& y) {
        // 修改这个参数调整是大根堆还是小根堆
        const bool SMALL_TOP_HEAP = true;
        return SMALL_TOP_HEAP ? x < y : x > y;
    }

   public:
    int n;
    int rt;
    vector<int> lc;
    vector<int> rc;
    vector<int> mostL;
    vector<int> mostR;

    void build(int* a, int _n) {
        n = _n;
        lc.clear(), lc.resize(n + 2);
        rc.clear(), rc.resize(n + 2);
        stk.clear(), stk.resize(n + 2);
        for (int i = 1, top = 0; i <= n; i++) {
            int k = top;
            while (k >= 1 && cmp(a[i], a[stk[k]])) {
                k--;
            }
            if (k >= 1) {
                // 节点i的权值>=栈顶节点的权值，挂在栈顶节点的右子树下
                rc[stk[k]] = i;
            }
            if (k + 1 <= top) {
                // 栈顶节点原本的右子树权值>节点i的权值，改为挂在节点i的左子树下
                lc[i] = stk[k + 1];
            }
            stk[++k] = i;
            top = k;
        }
        rt = stk[1];  // 笛卡尔树的根
    }

    // 计算每个节点作为最值（由cmp定义），最左和最右能管辖到哪里
    void calc_most_L_and_R(int n) {
        for (int i = 1; i <= n; ++i) {
            mostL[i] = n + 1;  // 初始化
            mostR[i] = 0;
        }
        dfs(rt);
    }

} c_tree;
