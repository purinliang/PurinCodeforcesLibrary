#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* --- Template Begin --- */

template <typename NodeInfo, typename NodeTag>
struct SegmentTree {
   private:
    int _n;
    vector<NodeInfo> _info;
    vector<NodeTag> _tag;

    inline int lch(int u) { return u * 2; }
    inline int rch(int u) { return u * 2 + 1; }
    inline int mid(int l, int r) { return (l + r) / 2; }

    void pull_up(int u, int l, int r) {
        _info[u] = NodeInfo(l, r, _info[lch(u)], _info[rch(u)]);
    }

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

   public:
    void build(int n) {
        _n = n;
        _info.clear(), _info.resize(4 * (_n + 2));
        _tag.clear(), _tag.resize(4 * (_n + 2));
        build(1, 1, _n);
    }

    void update(int L, int R, const NodeTag& upd_tag) {
        update(1, 1, _n, L, R, upd_tag);
    }

    NodeInfo query(int L, int R) { return query(1, 1, _n, L, R); }
};

struct NodeTag {
    NodeTag() {};
    void apply_tag(int l, int r, const NodeTag& tag) {}
};

struct NodeInfo {
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
    NodeInfo() {}
    NodeInfo(int l, int r, const NodeInfo& lch, const NodeInfo& rch) {}
    void apply_tag(int l, int r, const NodeTag& tag) {}
};

/* --- Template End --- */

/*
    This template is designed for most used in daily training, including:
        NodeTag: Add or Set
        NodeInfo: Sum or MinMax
    If you need your costomized template, please see SegmentTree2
*/

struct NodeTagAdd : NodeTag {
    ll _add_tag = 0LL;
    NodeTagAdd(ll val = 0LL) { _add_tag = val; }
    void apply_tag(int l, int r, const NodeTagAdd& tag) {
        if (tag._add_tag != 0LL) {
            _add_tag += tag._add_tag;
        }
    }
};

struct NodeTagSet : NodeTag {
    pair<bool, ll> _set_tag = {false, 0LL};
    NodeTagSet(ll val = 0LL, bool set = false) {
        if (set) {
            _set_tag = {true, val};
        }
    }
    void apply_tag(int l, int r, const NodeTagSet& tag) {
        if (tag._set_tag.first != false) {
            _set_tag = tag._set_tag;
        }
    }
};

struct NodeInfoSum : NodeInfo {
    ll _sum = 0LL;
    NodeInfoSum() {}
    NodeInfoSum(int l, int r, const NodeInfoSum& lch, const NodeInfoSum& rch) {
        _sum = lch._sum + rch._sum;
    }
    void apply_tag(int l, int r, const NodeTagAdd& tag) {
        if (tag._add_tag != 0LL) {
            _sum += 1LL * (r - l + 1) * tag._add_tag;
        }
    }
    void apply_tag(int l, int r, const NodeTagSet& tag) {
        if (tag._set_tag.first != false) {
            _sum = 1LL * (r - l + 1) * tag._set_tag.second;
        }
    }
};

struct NodeInfoMinMax : NodeInfo {
    ll _min = LINF, _max = -LINF;
    NodeInfoMinMax() {}
    NodeInfoMinMax(int l, int r, const NodeInfoMinMax& lch,
                   const NodeInfoMinMax& rch) {
        _min = std::min(lch._min, rch._min),
        _max = std::max(lch._max, rch._max);
    }
    void apply_tag(int l, int r, const NodeTagAdd& tag) {
        if (tag._add_tag != 0LL) {
            _min += tag._add_tag, _max += tag._add_tag;
        }
    }
    void apply_tag(int l, int r, const NodeTagSet& tag) {
        if (tag._set_tag.first != false) {
            _min = tag._set_tag.second, _max = tag._set_tag.second;
        }
    }
};

struct NodeInfoSumMinMax : NodeInfo {
    ll _sum = 0LL;
    ll _min = LINF, _max = -LINF;
    NodeInfoSumMinMax() {}
    NodeInfoSumMinMax(int l, int r, const NodeInfoSumMinMax& lch,
                      const NodeInfoSumMinMax& rch) {
        _sum = lch._sum + rch._sum;
        _min = std::min(lch._min, rch._min),
        _max = std::max(lch._max, rch._max);
    }
    void apply_tag(int l, int r, const NodeTagAdd& tag) {
        if (tag._add_tag != 0LL) {
            _sum += 1LL * (r - l + 1) * tag._add_tag;
            _min += tag._add_tag, _max += tag._add_tag;
        }
    }
    void apply_tag(int l, int r, const NodeTagSet& tag) {
        if (tag._set_tag.first != false) {
            _sum = 1LL * (r - l + 1) * tag._set_tag.second;
            _min = tag._set_tag.second, _max = tag._set_tag.second;
        }
    }
};

SegmentTree<NodeInfoSum, NodeTagAdd> st;
