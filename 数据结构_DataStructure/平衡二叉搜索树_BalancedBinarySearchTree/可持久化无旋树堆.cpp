#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * PersistentNonRotatingTreap
 *
 * The elements are managed by index (just like std::vector).
 *
 * This data-structure supports almostly all kinds of of the interval
 * operations, like range_sum, range_max, range_min. range_add and range_set
 * (just like SegmentTree), and what's more important, the RANGE_REVERSE
 * operation.
 */
struct PersistentNonRotatingTreap {
   private:
    static const int DEFAULT_CAPACITY = 3e5 + 10;
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

    struct Node {
        int lch = 0, rch = 0, rnd = 0;
        bool rev_tag = false;
        ll val = 0LL, siz = 0LL, sum = 0LL;

        Node() {}

        Node(ll _val) {
            rnd = rand();
            val = _val, siz = 1LL, sum = _val;
        }
    };

    vector<int> root;
    vector<Node> node;

    void PushUp(int u) {
        node[u].siz = node[node[u].lch].siz + 1 + node[node[u].rch].siz;
        node[u].sum =
            node[node[u].lch].sum + node[u].val + node[node[u].rch].sum;
    }

    int NewNode(ll _val) {
        int u = node.size();
        node.push_back(Node(_val));
        return u;
    }

    int CloneNode(int clone_from) {
        int u = node.size();
        Node nd = node[clone_from];
        node.push_back(nd);
        return u;
    }

    int GetNewVersion() {
        int new_ver = root.size();
        root.push_back(0);
        return new_ver;
    }

    void PushDown(int u) {
        // 如果存在 lazy_tag 则要先复制子节点再下推，因为一个子节点
        // 可能属于多个版本，直接下推会导致影响其他版本
        if (node[u].rev_tag) {
            swap(node[u].lch, node[u].rch);
            if (node[u].lch) {
                node[u].lch = CloneNode(node[u].lch);
                node[node[u].lch].rev_tag ^= true;
            }
            if (node[u].rch) {
                node[u].rch = CloneNode(node[u].rch);
                node[node[u].rch].rev_tag ^= true;
            }
            node[u].rev_tag = false;
        }
    }

    void SplitRank(int u, int _rnk, int& x, int& y) {
        if (!u) {
            x = 0, y = 0;
            return;
        }
        // 如果 PushDown 成功，则会复制两个子节点并把信息更新的新的子节点上。
        // 绝对不会影响其他版本。
        PushDown(u);
        if (_rnk <= node[node[u].lch].siz) {
            // 在 Split 之前复制可以保证不影响其他版本，在 Merge 时则无需复制
            y = CloneNode(u);
            SplitRank(node[u].lch, _rnk, x, node[y].lch);
            PushUp(y);
        } else {
            // 在 Split 之前复制可以保证不影响其他版本，在 Merge 时则无需复制
            x = CloneNode(u);
            SplitRank(node[u].rch, _rnk - node[node[u].lch].siz - 1,
                      node[x].rch, y);
            PushUp(x);
        }
    }

    int Merge(int x, int y) {
        // 在 Merge 时则无需复制，一个节点本身就属于多个父节点。
        // 只需要把当前的信息返回调用自己的父节点即可，其他版本不会受影响。
        if (!x || !y) {
            return x | y;
        }
        // 如果 PushDown 成功，则会复制两个子节点并把信息更新的新的子节点上。
        // 绝对不会影响其他版本。
        PushDown(x), PushDown(y);
        if (node[x].rnd < node[y].rnd) {
            node[x].rch = Merge(node[x].rch, y);
            PushUp(x);
            return x;
        } else {
            node[y].lch = Merge(x, node[y].lch);
            PushUp(y);
            return y;
        }
    }

    tuple<int, int, int> Split3(int ver, int lrnk, int rrnk) {
        int lroot = 0, mroot = 0, rroot = 0;
        SplitRank(root[ver], lrnk - 1, lroot, rroot);
        SplitRank(rroot, rrnk - lrnk + 1, mroot, rroot);
        return {lroot, mroot, rroot};
    }

    void Merge3(int ver, int lroot, int mroot, int rroot) {
        root[ver] = Merge(Merge(lroot, mroot), rroot);
    }

    void ReserveNodeVector() {
        const int SAFE_CAPACITY_MARGIN = 512;
        // 由于一次操作的 Split 和 Merge 在每一层都会导致 2 次复制，
        // 可以假设最坏情况下，rand 得不均匀，树有25层，每次操作 Split 两次，
        // Merge 两次，需要新增 200 个节点。
        int next_node_capacity = node.capacity();
        while (node.size() + SAFE_CAPACITY_MARGIN > next_node_capacity) {
            next_node_capacity *= 2;
        }
        if (next_node_capacity > node.capacity()) {
            node.reserve(next_node_capacity);
        }
    }

   public:
    PersistentNonRotatingTreap() {
        Init();
    }

    void Init(int capacity = DEFAULT_CAPACITY) {
        root.reserve(capacity);
        node.reserve(capacity);
        ReserveNodeVector();
        root.clear();
        int new_ver = GetNewVersion();  // new_ver == 0;
        root[new_ver] = 0;
        node.clear();
        node.push_back(Node());
    }

    void Insert(int ver, int idx, ll val) {
        ReserveNodeVector();
        auto [L, M, R] = Split3(ver, idx, idx - 1);
        M = NewNode(val);
        int new_ver = GetNewVersion();
        Merge3(new_ver, L, M, R);
    }

    void Remove(int ver, int idx) {
        ReserveNodeVector();
        auto [L, M, R] = Split3(ver, idx, idx);
        M = 0;  // M is removed
        int new_ver = GetNewVersion();
        Merge3(new_ver, L, M, R);
    }

    int Size(int ver) {
        return node[root[ver]].siz;
    }

    ll Value(int ver, int idx) {
        ReserveNodeVector();
        auto [L, M, R] = Split3(ver, idx, idx);
        ll res = node[M].val;
        int new_ver = GetNewVersion();
        Merge3(new_ver, L, M, R);
        return res;
    }

    ll Sum(int ver, int l, int r) {
        ReserveNodeVector();
        auto [L, M, R] = Split3(ver, l, r);
        ll res = node[M].sum;
        int new_ver = GetNewVersion();
        Merge3(new_ver, L, M, R);
        return res;
    }

    void Reverse(int ver, int l, int r) {
        ReserveNodeVector();
        auto [L, M, R] = Split3(ver, l, r);
        node[M].rev_tag ^= true;
        int new_ver = GetNewVersion();
        Merge3(new_ver, L, M, R);
    }

} tree;
