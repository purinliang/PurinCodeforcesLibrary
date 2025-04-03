#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * SparseTable can maintain range query of min/max values,
 * bitwise_and (&), logical_and (&&) and gcd (__gcd), are also min values
 * bitwise_or (|), logical_and (||) and lcm (__lcm), are also max values
 *
 * sum (+) and xor_sum (^) are not supported.
 *
 * TODO: There is an O(n) init - O(1) query version
 */
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
            _st[i][0].set_value(a[i]);
        }
        for (int j = 1; j <= _log2[_n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= _n; ++i) {
                _st[i][j] = NodeInfo(_st[i][j - 1], _st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    NodeInfo query(int l, int r) {
        l = max(l, 1), r = min(r, _n);
        if (l > r) {
            return NodeInfo();
        }
        int s = _log2[r - l + 1];
        return NodeInfo(_st[l][s], _st[r - (1 << s) + 1][s]);
    }
};

struct NodeInfoMinMax{
    using value_type = ll;
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
    ll _min = LINF;
    ll _max = -LINF;
    NodeInfoMinMax() {}
    void set_value(ll val) {
        _min = val;
        _max = val;
    }
    NodeInfoMinMax(const NodeInfoMinMax& lch, const NodeInfoMinMax& rch) {
        _min = std::min(lch._min, rch._min);
        _max = std::max(lch._max, rch._max);
    }
};

SparseTable<NodeInfoMinMax> st;
