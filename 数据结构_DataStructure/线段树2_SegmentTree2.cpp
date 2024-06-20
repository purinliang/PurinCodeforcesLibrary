#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename NodeInfo, typename NodeTag>
struct SegmentTree {
   private:
    int _n;
    vector<NodeInfo> _info;
    vector<NodeTag> _tag;

    inline int lch(int u) { return u * 2; }
    inline int rch(int u) { return u * 2 + 1; }
    inline int mid(int l, int r) { return (l + r) / 2; }

    void pull_up(int u, int l, int r) { _info[u] = NodeInfo(l, r, _info[lch(u)], _info[rch(u)]); }

    void push_down(int u, int l, int r) {
        _info[lch(u)].apply_tag(l, mid(l, r), _tag[u]);
        _info[rch(u)].apply_tag(mid(l, r) + 1, r, _tag[u]);
        _tag[lch(u)].apply_tag(l, mid(l, r), _tag[u]);
        _tag[rch(u)].apply_tag(mid(l, r) + 1, r, _tag[u]);
        _tag[u] = NodeTag();
    }

    void build(int u, int l, int r) {
        if (l == r) {
            _info[u] = NodeInfo();
            _tag[u] = NodeTag();
            return;
        }
        build(lch(u), l, mid(l, r));
        build(rch(u), mid(l, r) + 1, r);
        pull_up(u, l, r);
    }

    void update(int u, int l, int r, int L, int R, const NodeTag& upd_tag) {
        if (L > R || L > r || R < l) {
            return;
        }
        if (L <= l && r <= R) {
            _info[u].apply_tag(l, r, upd_tag);
            _tag[u].apply_tag(l, r, upd_tag);
            return;
        }
        push_down(u, l, r);
        update(lch(u), l, mid(l, r), L, R, upd_tag);
        update(rch(u), mid(l, r) + 1, r, L, R, upd_tag);
        pull_up(u, l, r);
    }

    NodeInfo query(int u, int l, int r, int L, int R) {
        if (L > R || L > r || R < l) {
            return NodeInfo();
        }
        if (L <= l && r <= R) {
            return _info[u];
        }
        push_down(u, l, r);
        NodeInfo lres = query(lch(u), l, mid(l, r), L, R);
        NodeInfo rres = query(rch(u), mid(l, r) + 1, r, L, R);
        NodeInfo res = NodeInfo(l, r, lres, rres);
        return res;
    }

    string to_string(int u, int l, int r, int dep, const string& dir) {
        string m_prefix = string(dep * 4, ' ') + dir;
        string m_res = (l <= r) ? (_info[u].to_string() + "," + _tag[u].to_string() + "\n") : "";
        string l_res = (l < r) ? to_string(lch(u), l, mid(l, r), dep + 1, "/ ") : "";
        string r_res = (l < r) ? to_string(rch(u), mid(l, r) + 1, r, dep + 1, "\\ ") : "";
        return l_res + m_prefix + m_res + r_res;
    }

   public:
    void build(int n) {
        _n = n;
        _info.clear(), _info.resize(4 * (_n + 2));
        _tag.clear(), _tag.resize(4 * (_n + 2));
        build(1, 1, _n);
    }

    void update(int L, int R, const NodeTag& upd_tag) { update(1, 1, _n, L, R, upd_tag); }

    NodeInfo query(int L, int R) { return query(1, 1, _n, L, R); }

    string to_string() { return "SegmentTree = [\n" + to_string(1, 1, _n, 1, "") + "]"; }

    void show() {
#ifdef LOCAL
        cout << "[D] " << to_string() << endl;
#endif
    }
};

struct NodeTag {
    ll _add_tag = 0LL;
    // pair<bool, ll> _set_tag = {false, 0LL};
    NodeTag() {};
    static NodeTag add(ll val) {
        NodeTag tag;
        tag._add_tag = val;
        return tag;
    }
    // static NodeTag set(ll val) {
    //     NodeTag tag;
    //     tag._set_tag = {true, val};
    //     return tag;
    // }
    void apply_tag(int l, int r, const NodeTag& tag) {
        if (tag._add_tag != 0LL) {
            _add_tag += tag._add_tag;
        }
        // if (tag._set_tag.first != false) {
        //     _set_tag = tag._set_tag;
        // }
    }
    string to_string() const { return std::to_string(_add_tag); }
};

struct NodeInfo {
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
    ll _sum = 0LL;
    // ll _min = LINF, _max = -LINF;
    NodeInfo() {}
    NodeInfo(int l, int r, const NodeInfo& lch, const NodeInfo& rch) {
        _sum = lch._sum + rch._sum;
        // _min = std::min(lch._min, rch._min), _max = std::max(lch._max, rch._max);
    }
    void apply_tag(int l, int r, const NodeTag& tag) {
        if (tag._add_tag != 0LL) {
            _sum += 1LL * (r - l + 1) * tag._add_tag;
            // _min += tag._add_tag, _max += tag._add_tag;
        }
        // if (tag._set_tag.first != false) {
        //     _sum = 1LL * (r - l + 1) * tag._set_tag.second;
        //     // _min = tag._set_tag.second, _max = tag._set_tag.second;
        // }
    }
    string to_string() const { return std::to_string(_sum); }
};

SegmentTree<NodeInfo, NodeTag> st;
