#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * NonRotatingTreap
 *
 * The elements are managed by index (just like std::vector).
 *
 * This data-structure supports almostly all kinds of of the interval operations, like range_sum,
 * range_max, range_min. range_add and range_set (just like SegmentTree), and what's more important,
 * the RANGE_REVERSE operation.
 */
struct NonRotatingTreap {
   private:
    static const int DEFAULT_CAPACITY = 3e5 + 10;
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

    struct Node {
        int lch = 0, rch = 0, rnd = 0;
        bool rev_tag = false;
        ll val = 0LL, siz = 0LL, sum = 0LL;
        // ll min = LINF, max = -LINF;

        Node() {
        }

        Node(ll _val) {
            rnd = rand();
            val = _val, siz = 1LL, sum = _val;
            // min = _val, max = _val;
        }

        string to_string(int u) {
            return std::to_string(val);
            string res = "{";
            // res += "u = " + std::to_string(u) + ", ";
            res += "val = " + std::to_string(val) + ", ";
            res += "sum = " + std::to_string(sum) + ", ";
            // res += "min = " + std::to_string(min) + ", ";
            // res += "max = " + std::to_string(max) + ", ";
            res = res.substr(0, std::max(0, (int)res.length() - 2)) + "}";
            return res;
        }
    };

    int root;
    vector<Node> node;

    void PushUp(int u) {
        node[u].siz = node[node[u].lch].siz + 1 + node[node[u].rch].siz;
        node[u].sum = node[node[u].lch].sum + node[u].val + node[node[u].rch].sum;
        // node[u].min = std::min({node[node[u].lch].min, node[u].val, node[node[u].rch].min});
        // node[u].max = std::max({node[node[u].lch].max, node[u].val, node[node[u].rch].max});
    }

    int NewNode(ll _val) {
        int u = node.size();
        node.push_back(Node(_val));
        return u;
    }

    void PushDown(int u) {
        if (node[u].rev_tag) {
            swap(node[u].lch, node[u].rch);
            node[node[u].lch].rev_tag ^= true;
            node[node[u].rch].rev_tag ^= true;
            node[u].rev_tag = false;
        }
    }

    void SplitRank(int u, int _rnk, int& x, int& y) {
        if (!u) {
            x = 0, y = 0;
            return;
        }
        PushDown(u);
        if (_rnk <= node[node[u].lch].siz) {
            y = u;
            SplitRank(node[u].lch, _rnk, x, node[u].lch);
            PushUp(y);
        } else {
            x = u;
            SplitRank(node[u].rch, _rnk - node[node[u].lch].siz - 1, node[u].rch, y);
            PushUp(x);
        }
    }

    int Merge(int x, int y) {
        if (!x || !y) {
            return x | y;
        }
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

    string compressed_to_string(int u) {
        const int LEFT = 0, RIGHT = 1;
        if (!u) {
            return "";
        }
        PushDown(u);
        string res = "";
        if (node[u].lch) {
            res += compressed_to_string(node[u].lch) + ", ";
        }
        res += node[u].to_string(u);
        if (node[u].rch) {
            res += ", " + compressed_to_string(node[u].rch);
        }
        return res;
    }

    string to_string(int u, int dep, int dir) {
        const int LEFT = 0, RIGHT = 1;
        if (!u) {
            return "";
        }
        PushDown(u);
        string res = "";
        res += to_string(node[u].lch, dep + 1, LEFT);
        string indent = "  ";
        for (int i = 1; i <= dep; ++i) {
            res += indent;
        }
        if (dir == LEFT) {
            res += "/ ";
        } else if (dir == RIGHT) {
            res += "\\ ";
        }
        res += node[u].to_string(u) + "\n";
        res += to_string(node[u].rch, dep + 1, RIGHT);
        return res;
    }

    tuple<int, int, int> Split3(int lrnk, int rrnk) {
        int lroot = 0, mroot = 0, rroot = 0;
        SplitRank(root, lrnk - 1, lroot, rroot);
        SplitRank(rroot, rrnk - lrnk + 1, mroot, rroot);
        // show(lroot, mroot, rroot);
        return {lroot, mroot, rroot};
    }

    void Merge3(int lroot, int mroot, int rroot) {
        root = Merge(Merge(lroot, mroot), rroot);
    }

    void show(int lroot, int mroot, int rroot) {
#ifdef LOCAL
        string res = "NonRotatingTreap = [";
        res += compressed_to_string(lroot);
        res += "], [";
        res += compressed_to_string(mroot);
        res += "], [";
        res += compressed_to_string(rroot);
        res += "]";
        cout << res << endl;
#endif
    }

   public:
    NonRotatingTreap() {
        Init();
    }

    void Init(int capacity = DEFAULT_CAPACITY) {
        if (capacity > node.capacity()) {
            node.reserve(capacity);
        }
        root = 0;
        node.clear();
        node.push_back(Node());
    }

    void Insert(int idx, int val) {
        if (node.size() == node.capacity()) {
            node.reserve(2 * node.capacity());
        }
        auto [L, M, R] = Split3(idx, idx - 1);
        M = NewNode(val);
        Merge3(L, M, R);
    }

    void Remove(int idx) {
        auto [L, M, R] = Split3(idx, idx);
        M = 0;  // M is removed
        Merge3(L, M, R);
    }

    int Size() {
        return node[root].siz;
    }

    ll Value(int idx) {
        auto [L, M, R] = Split3(idx, idx);
        ll res = node[M].val;
        Merge3(L, M, R);
        return res;
    }

    ll Sum(int l, int r) {
        auto [L, M, R] = Split3(l, r);
        ll res = node[M].sum;
        Merge3(L, M, R);
        return res;
    }

    void Reverse(int l, int r) {
        auto [L, M, R] = Split3(l, r);
        node[M].rev_tag ^= true;
        Merge3(L, M, R);
    }

    string to_string(int u) {
        string res = "NonRotatingTreap = [";
        if (u) {
            res += "\n" + to_string(u, 1, -1);
        }
        res += "]";
        return res;
    }

    void show() {
#ifdef LOCAL
        cout << to_string(root) << endl;
#endif
    }

} tree;
