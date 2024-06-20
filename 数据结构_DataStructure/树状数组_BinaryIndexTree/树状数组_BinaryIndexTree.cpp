#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/** 单点加 */
struct BinaryIndexTreeAdd {
   private:
    int _n;
    vector<ll> _sum;

   public:
    void init(int n) {
        _n = n;
        _sum.clear(), _sum.resize(_n + 2);
    }

    void add(int idx, ll val) {
        for (int i = idx; i <= _n; i += i & (-i)) {
            _sum[i] += val;
        }
    }

    ll sum(int idx) {
        ll res = 0;
        for (int i = idx; i; i -= i & (-i)) {
            res += _sum[i];
        }
        return res;
    }

    ll sum(int lidx, int ridx) {
        return sum(ridx) - sum(lidx - 1);
    }

} bit_add;

/** 单点改 */
struct BinaryIndexTreeSet {
   private:
    int _n;
    vector<ll> _val, _sum;

    void add(int idx, ll dlt) {
        for (int i = idx; i <= _n; i += i & (-i)) {
            _sum[i] += dlt;
        }
    }

   public:
    void init(int n) {
        _n = n;
        _val.clear(), _val.resize(_n + 2);
        _sum.clear(), _sum.resize(_n + 2);
    }

    void set(int idx, ll val) {
        add(idx, val - _val[idx]);
        _val[idx] = val;
    }

    ll sum(int idx) {
        ll res = 0;
        for (int i = idx; i; i -= i & (-i)) {
            res += _sum[i];
        }
        return res;
    }

    ll sum(int lidx, int ridx) {
        return sum(ridx) - sum(lidx - 1);
    }

} bit_set;

/** 区间加 */
struct BinaryIndexTreeRangeAdd {
   private:
    int _n;
    vector<ll> _d1, _d2;

    void add(int idx, ll val) {
        for (int i = idx; i <= _n; i += i & (-i)) {
            _d1[i] += val, _d2[i] += 1LL * idx * val;
        }
    }

   public:
    void init(int n) {
        _n = n;
        _d1.clear(), _d1.resize(_n + 3);
        _d2.clear(), _d2.resize(_n + 3);
    }

    void add(int lidx, int ridx, int val) {
        add(lidx, val), add(ridx + 1, -val);
    }

    ll sum(int idx) {
        ll res = 0;
        for (int i = idx; i; i -= i & (-i)) {
            res += 1LL * (idx + 1) * _d1[i] - _d2[i];
        }
        return res;
    }

    ll sum(int lidx, int ridx) {
        return sum(ridx) - sum(lidx - 1);
    }

} bit_range_add;
