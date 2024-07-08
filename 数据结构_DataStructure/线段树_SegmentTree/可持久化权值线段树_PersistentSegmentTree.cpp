#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 可持久化线段树
 *
 * 以下是可持久化权值线段树（主席树）的写法。
 *
 * 权值线段树的含义是，线段树中叶节点 [l, l] 表示的是排名为 l 的值（即 _val[l]
 * ） 的出现次数。
 *
 * 通过对权值线段树进行可持久化，从左往右插入原数组的每一个元素，就可以得到以原
 * 数组的每个端点 i（从 0 到 n） 为的前缀区间 [1, i] 的一共 n + 1 棵权值线段树。
 * 当查询 [l, r] 区间的权值线段树时，可以用 [1, r] 的权值线段树减去 [1, l - 1]
 * 的权值线段树（每个对应节点做减法）得到，然后在所得的 [l, r] 区间的权值线段树
 * 上进行线段树二分，即可找到区间内的第k小值。也可以用整体二分做。
 *
 * 模板题：
 * https://www.luogu.com.cn/problem/P3834
 */
struct PersistentSegmentTree {
   private:
    int _len;
    vector<int> _val;
    vector<int> _root, _sum, _lch, _rch;

    int get_idx(const int& val) {  // 找到val应该放在哪个叶子
        return lower_bound(_val.begin() + 1, _val.begin() + 1 + _len, val) -
               _val.begin();
    }

    int get_new_u(int clone_from = -1) {
        int new_u = _sum.size();
        _sum.push_back(0), _lch.push_back(0), _rch.push_back(0);
        if (clone_from != -1) {
            _sum[new_u] = _sum[clone_from];
            _lch[new_u] = _lch[clone_from];
            _rch[new_u] = _rch[clone_from];
        }
        return new_u;
    }

    int build(int l, int r) {
        int u = get_new_u();
        if (l == r) {
            return u;
        }
        int mid = (l + r) >> 1;
        _lch[u] = build(l, mid);
        _rch[u] = build(mid + 1, r);
        return u;
    }

    int update(int l, int r, int pos, int old_u) {
        int new_u = get_new_u(old_u);
        ++_sum[new_u];
        if (l == r) {
            return new_u;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            _lch[new_u] = update(l, mid, pos, _lch[old_u]);
        } else {
            _rch[new_u] = update(mid + 1, r, pos, _rch[old_u]);
        }
        return new_u;
    }

    int query(int lu, int ru, int l, int r, int k) {
        if (l == r) {
            return l;
        }
        int left_sum = _sum[_lch[ru]] - _sum[_lch[lu]];
        int mid = (l + r) >> 1;
        if (k <= left_sum) {
            return query(_lch[lu], _lch[ru], l, mid, k);
        } else {
            return query(_rch[lu], _rch[ru], mid + 1, r, k - left_sum);
        }
    }

    void init_val(int n, int* a) {
        _val.clear(), _val.resize(n + 2);
        for (int i = 1; i <= n; ++i) {
            _val[i] = a[i];
        }
        sort(_val.begin() + 1, _val.begin() + 1 + n);
        _len =
            unique(_val.begin() + 1, _val.begin() + 1 + n) - (_val.begin() + 1);
    }

    void init_node(int n) {
        int upd_cnt = n;  // how many times public:update has been invoked
        int reserve_size = (4 * _len + upd_cnt * (log2(_len) + 1));
        _sum.clear(), _sum.reserve(reserve_size);
        _lch.clear(), _lch.reserve(reserve_size);
        _rch.clear(), _rch.reserve(reserve_size);
        int skipped_u = get_new_u();  // skip u == 0
    }

    void init_root(int n, int* a) {
        _root.clear(), _root.resize(n + 2);
        _root[0] = build(1, _len);
        for (int i = 1; i <= n; ++i) {
            _root[i] = update(1, _len, get_idx(a[i]), _root[i - 1]);
        }
    }

   public:
    void init(int n, int* a) {
        init_val(n, a);
        init_node(n);
        init_root(n, a);
    }

    int query(int l, int r, int k) {
        int pos = query(_root[l - 1], _root[r], 1, _len, k);
        return _val[pos];
    }

} pst;
