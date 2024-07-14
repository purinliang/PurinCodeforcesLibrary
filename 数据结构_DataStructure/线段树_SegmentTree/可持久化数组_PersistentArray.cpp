#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 可持久化数组
 *
 * 用可持久化线段树来实现的可持久化数组，由于没有线段树的各种特征，也没有权值线段树
 * 的各种特征，故被分类为可持久化数组。
 *
 * 可以支持查询某个历史版本中，某个位置的值。
 *
 * 模板题：
 * https://www.luogu.com.cn/problem/P3919
 */
struct PersistentArray {
   private:
    int _len;
    vector<int> _root, _val, _lch, _rch;

    int get_new_u(int clone_from = -1) {
        int new_u = _val.size();
        _val.push_back(0), _lch.push_back(0), _rch.push_back(0);
        if (clone_from != -1) {
            _val[new_u] = _val[clone_from];
            _lch[new_u] = _lch[clone_from];
            _rch[new_u] = _rch[clone_from];
        }
        return new_u;
    }

    int build(int l, int r, int* a) {
        int u = get_new_u();
        if (l == r) {
            _val[u] = a[l];
            return u;
        }
        int mid = (l + r) >> 1;
        _lch[u] = build(l, mid, a);
        _rch[u] = build(mid + 1, r, a);
        return u;
    }

    int update(int l, int r, int pos, int val, int old_u) {
        int new_u = get_new_u(old_u);
        if (l == r) {
            _val[new_u] = val;
            return new_u;
        }
        // 如果存在 lazy_tag 则要先复制子节点再下推，因为一个子节点
        // 可能属于多个版本，直接下推会导致影响其他版本
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            _lch[new_u] = update(l, mid, pos, val, _lch[old_u]);
        } else {
            _rch[new_u] = update(mid + 1, r, pos, val, _rch[old_u]);
        }
        return new_u;
    }

    int query(int u, int l, int r, int pos) {
        if (l == r) {
            return _val[u];
        }
        // 如果存在 lazy_tag 则要先复制子节点再下推，因为一个子节点
        // 可能属于多个版本，直接下推会导致影响其他版本
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            return query(_lch[u], l, mid, pos);
        } else {
            return query(_rch[u], mid + 1, r, pos);
        }
    }

    void init_node(int n) {
        int upd_cnt = n;  // how many times public:update has been invoked
        int reserve_size = (4 * n + upd_cnt * (log2(n) + 1));
        _val.clear(), _val.reserve(reserve_size);
        _lch.clear(), _lch.reserve(reserve_size);
        _rch.clear(), _rch.reserve(reserve_size);
        int skipped_u = get_new_u();  // skip u == 0
    }

    int new_version() {
        int new_ver = _root.size();
        _root.push_back(0);
        return new_ver;
    }

    void init_root(int n, int* a) {
        _root.clear();
        int new_ver = new_version();  // new_ver == 0
        _root[new_ver] = build(1, n, a);
    }

   public:
    void init(int n, int* a) {
        _len = n;
        init_node(n);
        init_root(n, a);
    }

    void update(int ver, int pos, int val) {
        int new_ver = new_version();
        _root[new_ver] = update(1, _len, pos, val, _root[ver]);
    }

    int query(int ver, int pos) {
        int new_ver = new_version();
        _root[new_ver] = _root[ver];
        int res = query(_root[ver], 1, _len, pos);
        return res;
    }

} pa;
