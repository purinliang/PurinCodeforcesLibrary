#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
    // #define USING_MIN_MAX
   private:
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
    static const ll INF = 0x3F3F3F3F;

    struct Node {
        int _lidx = INF, _ridx = -INF;
        ll _add_tag = 0LL;
        pair<bool, ll> _set_tag = {false, 0LL};
        ll _sum = 0LL;
#ifdef USING_MIN_MAX
        ll _min = LINF;
        ll _max = -LINF;
#endif

        Node() {}

        Node(int _l, int _r) { _lidx = _l, _ridx = _r; }

        string to_string() {
            return std::to_string(_sum);
            string res = "";
            res += "[" + std::to_string(_lidx) + ", " + std::to_string(_ridx) + "] ";
            res += "sum = " + std::to_string(_sum) + ", ";
#ifdef USING_MIN_MAX
            res += "min = " + std::to_string(_min) + ", ";
            res += "max = " + std::to_string(_max) + ", ";
#endif
            res = res.substr(0, std::max(0, (int)res.length() - 2));
            return res;
        }

        void add(ll val) {
            _add_tag += val;
            _sum += 1LL * (_ridx - _lidx + 1) * val;
#ifdef USING_MIN_MAX
            _min += val;
            _max += val;
#endif
        }

        void set(ll val) {
            _set_tag = {true, val};
            _sum = 1LL * (_ridx - _lidx + 1) * val;
#ifdef USING_MIN_MAX
            _min = val;
            _max = val;
#endif
        }

        void merge(Node& lch_node, Node& rch_node) {
            _lidx = std::min(lch_node._lidx, rch_node._lidx);
            _ridx = std::max(lch_node._ridx, rch_node._ridx);
            _sum = lch_node._sum + rch_node._sum;
#ifdef USING_MIN_MAX
            _min = std::min(lch_node._min, rch_node._min);
            _max = std::max(lch_node._max, rch_node._max);
#endif
        }
    };

    int _n;
    vector<Node> _node;

#define lch (u << 1)
#define rch (u << 1 | 1)
#define mid ((l + r) >> 1)

    void pull_up(int u) { _node[u].merge(_node[lch], _node[rch]); }

    void push_down(int u) {
        if (_node[u]._add_tag != 0LL) {
            _node[lch].add(_node[u]._add_tag);
            _node[rch].add(_node[u]._add_tag);
            _node[u]._add_tag = 0LL;
        }
    }

    void build(int u, int l, int r) {
        if (l == r) {
            _node[u] = Node(l, r);
            return;
        }
        build(lch, l, mid);
        build(rch, mid + 1, r);
        pull_up(u);
    }

    void add(int u, int l, int r, int L, int R, ll val) {
        if (L > R || L > r || R < l) {
            return;
        }
        if (L <= l && r <= R) {
            _node[u].add(val);
            return;
        }
        push_down(u);
        add(lch, l, mid, L, R, val);
        add(rch, mid + 1, r, L, R, val);
        pull_up(u);
    }

    // void set(int u, int l, int r, int L, int R, ll val) {
    //     if (L > R || L > r || R < l) {
    //         return;
    //     }
    //     if (L <= l && r <= R) {
    //         node[u].set(val);
    //         return;
    //     }
    //     push_down(u);
    //     set(lch, l, mid, L, R, val);
    //     set(rch, mid + 1, r, L, R, val);
    //     pull_up(u);
    // }

    Node query(int u, int l, int r, int L, int R) {
        if (L > R || L > r || R < l) {
            return Node();
        }
        if (L <= l && r <= R) {
            return _node[u];
        }
        push_down(u);
        Node l_res = query(lch, l, mid, L, R);
        Node r_res = query(rch, mid + 1, r, L, R);
        Node res;
        res.merge(l_res, r_res);
        return res;
    }

    string to_string(int u, int l, int r, string prefix, bool is_lch) {
        string m_prefix = (l <= r) ? (u != 1 ? (prefix + (is_lch ? "╭── " : "╰── ")) : "") : "";
        string m_res = (l <= r) ? (_node[u].to_string() + "\n") : "";
        string l_res = (l < r) ? to_string(lch, l, mid, prefix + "│   ", true) : "";
        string r_res = (l < r) ? to_string(rch, mid + 1, r, prefix + "│   ", false) : "";
        return l_res + m_prefix + m_res + r_res;
    }

#undef lch
#undef rch
#undef mid

   public:
    void build(int n) {
        _n = n;
        _node.clear();
        _node.resize(4 * _n);
        build(1, 1, _n);
    }

    void add(int L, int R, ll val) { add(1, 1, _n, L, R, val); }

    // void set(int L, int R, ll val) {
    //     set(1, 1, n, L, R, val);
    // }

    Node query(int L, int R) { return query(1, 1, _n, L, R); }

    ll sum(int L, int R) { return query(L, R)._sum; }

#ifdef USING_MIN_MAX
    ll min(int L, int R) { return query(L, R)._min; }

    ll max(int L, int R) { return query(L, R)._max; }
#endif

    string to_string() { return "SegmentTree = [\n" + to_string(1, 1, _n, "    ", false) + "]"; }

    void show() {
#ifdef LOCAL
        cout << "[D] " << to_string() << endl;
#endif
    }

#undef USING_MIN_MAX

} st;
