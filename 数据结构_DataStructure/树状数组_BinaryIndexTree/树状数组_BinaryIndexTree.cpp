#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/** 单点加 */
struct BinaryIndexTreeAdd {
   private:
    int n;
    vector<ll> sum;

   public:
    void Init(int _n) {
        n = _n;
        sum.clear();
        sum.resize(n + 2);
    }

    void Add(int idx, ll val) {
        for (int i = idx; i <= n; i += i & (-i)) {
            sum[i] += val;
        }
    }

    ll Sum(int idx) {
        ll res = 0;
        for (int i = idx; i; i -= i & (-i)) {
            res += sum[i];
        }
        return res;
    }

    ll RangeSum(int l, int r) {
        return Sum(r) - Sum(l - 1);
    }

} bit_add;

/** 单点改 */
struct BinaryIndexTreeSet {
   private:
    int n;
    vector<ll> val, sum;

    void Add(int idx, ll dlt) {
        for (int i = idx; i <= n; i += i & (-i)) {
            sum[i] += dlt;
        }
    }

   public:
    void Init(int _n) {
        n = _n;
        val.clear();
        val.resize(n + 2);
        sum.clear();
        sum.resize(n + 2);
    }

    void Set(int idx, ll _val) {
        ll dlt = _val - val[idx];
        Add(idx, dlt);
        val[idx] = _val;
    }

    ll Sum(int idx) {
        ll res = 0;
        for (int i = idx; i; i -= i & (-i)) {
            res += sum[i];
        }
        return res;
    }

    ll RangeSum(int l, int r) {
        return Sum(r) - Sum(l - 1);
    }

} bit_set;

/** 区间加 */
struct BinaryIndexTreeRangeAdd {
   private:
    int n;
    vector<ll> d1, d2;

    void Add(int idx, ll val) {
        for (int i = idx; i <= n; i += i & (-i)) {
            d1[i] += val, d2[i] += 1LL * idx * val;
        }
    }

   public:
    void Init(int _n) {
        n = _n;
        d1.clear();
        d1.resize(n + 2);
        d2.clear();
        d2.resize(n + 2);
    }

    void RangeAdd(int l, int r, int val) {
        Add(l, val), Add(r + 1, -val);
    }

    ll Sum(int idx) {
        ll res = 0;
        for (int i = idx; i; i -= i & (-i)) {
            res += 1LL * (idx + 1) * d1[i] - d2[i];
        }
        return res;
    }

    ll RangeSum(int l, int r) {
        return Sum(r) - Sum(l - 1);
    }

} bit_range_add;
