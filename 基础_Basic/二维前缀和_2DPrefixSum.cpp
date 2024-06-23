#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename T>
struct _2DPrefixSum {
   private:
    int _n, _m;
    vector<vector<ll>> _sum;

    ll prefix_sum(int d, int r) {
        if (d < 0 || r < 0) {
            return 0LL;
        }
        d = min(d, n), r = min(r, m);
        return _sum[d][r];
    }

   public:
    void init(int n, int m, vector<vector<T>> a) {
        _n = n, _m = m;
        _sum.clear(), _sum.resize(_n + 2);
        for (int i = 0; i <= n; ++i) {
            _sum[i] = vector<ll>(m);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                _sum[i] = a[i][j] + _sum[i][j - 1] + _sum[i - 1][j] - _sum[i - 1][j - 1];
            }
        }
    }

    ll range_sum(int u, int d, int l, int r) {
        if (u > d || l > r) {
            return 0LL;
        }
        ll res = prefix_sum(d, r) - prefix_sum(d, l - 1) - prefix_sum(u - 1, r) +
                 prefix_sum(u - 1, l - 1);
        return res;
    }

    ll row_sum(int i) { return range_sum(i, i, 1, _m); }

    ll column_sum(int j) { return range_sum(1, _n, j, j); }
};

_2DPrefixSum<ll> _2d_sum;
