#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <bool using_min, bool using_max>
struct NodeInfoPolicy {
    using value_type = ll;
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

    std::conditional_t<using_min, ll, std::monostate> _min;
    std::conditional_t<using_max, ll, std::monostate> _max;

    NodeInfoPolicy() {
        if constexpr (using_min) _min = LINF;
        if constexpr (using_max) _max = LINF;
    };

    NodeInfoPolicy(value_type val) {
        if constexpr (using_min) _min = val;
        if constexpr (using_max) _max = val;
    }

    void merge(const NodeInfoPolicy& lch, const NodeInfoPolicy& rch) {
        if constexpr (using_min) _min = std::min(lch._min, rch._min);
        if constexpr (using_max) _max = std::max(lch._max, rch._max);
    }
};

template <typename NodeInfo>
struct SparseTable {
   protected:
    int _n;
    vector<int> _log2;
    vector<vector<NodeInfo>> _st;

   public:
    void init(int n, typename NodeInfo::value_type* a) {
        _n = n;
        _log2.clear(), _log2.resize(_n + 2);
        for (int i = 2; i <= _n; ++i) {
            _log2[i] = _log2[i >> 1] + 1;
        }
        _st.clear(), _st.resize(_n + 2);
        for (int i = 1; i <= _n; ++i) {
            _st[i].resize(_log2[_n] + 1);
            _st[i][0] = NodeInfo(a[i]);
        }
        for (int j = 1; j <= _log2[_n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= _n; ++i) {
                _st[i][j].merge(_st[i][j - 1], _st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    NodeInfo query(int l, int r) {
        l = max(l, 1), r = min(r, _n);
        if (l > r) {
            return NodeInfo();
        }
        int s = _log2[r - l + 1];
        NodeInfo res;
        res.merge(_st[l][s], _st[r - (1 << s) + 1][s]);
        return res;
    }
};

using NodeInfoMinMax = NodeInfoPolicy<true, true>;

SparseTable<NodeInfoMinMax> st;