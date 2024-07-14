#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * Combinatorics
 * Verify problem: https://www.luogu.com.cn/problem/B3717
 * Verify submission: https://www.luogu.com.cn/record/166012826 July 14, 2024
 */
struct Combinatorics {
   private:
    /** MOD must be a very big prime (e.g. at least 1e6),
     * and bigger than max(n) */
    const int MOD = 998244353;
    vector<int> fac, inv_fac;

    ll qpow(ll x, ll n) {
        // assert(n >= 0);
        // assert(MOD > 1);
        ll res = 1LL;
        for (; n > 0LL; n >>= 1) {
            if (n & 1LL) res = res * x % MOD;
            x = x * x % MOD;
        }
        return res;
    }

    ll inv(ll x) {
        return qpow(x, MOD - 2);
    }

    // ll P_slow(ll n, ll m) {
    //     const int MAX_M = 1e6 + 10;
    //     assert(m <= MAX_M);
    //     ll res = 1LL;
    //     for (int i = 1; i <= m; ++i) {
    //         res = 1LL * res * (n + 1LL - i) % MOD;
    //     }
    //     return res;
    // }

    // ll C_slow(ll n, ll m) {
    //     m = min(n, n - m);
    //     const int MAX_M = 1e6 + 10;
    //     assert(m <= MAX_M);
    //     init(m);
    //     return 1LL * P_slow(n, m) * inv_fac[m] % MOD;
    // }

   public:
    void init(int n) {
        const int cur_max_n = (int)fac.size() - 1;
        if (n <= cur_max_n) return;
        n = max(n, 2 * cur_max_n);
        fac.resize(n + 1), inv_fac.resize(n + 1);
        for (int i = cur_max_n + 1; i <= n; ++i) {
            fac[i] = (i == 0) ? 1 : (1LL * fac[i - 1] * i % MOD);
        }
        for (int i = n; i >= cur_max_n + 1; --i) {
            inv_fac[i] =
                (i == n) ? inv(fac[n]) : (1LL * inv_fac[i + 1] * (i + 1) % MOD);
        }
    }

    /** Calc P(n, m) % MOD, this function will auto-init. */
    ll P(ll n, ll m) {
        if (n < 0LL || m < 0LL || n < m) return 0LL;
        init(n);
        return 1LL * fac[n] * inv_fac[n - m] % MOD;
    }

    /** Calc C(n, m) % MOD, this function will auto-init. */
    ll C(ll n, ll m) {
        if (n < 0LL || m < 0LL || n < m) return 0LL;
        init(n);
        return 1LL * P(n, m) * inv_fac[m] % MOD;
    }

    // // The following functions are less useful.

    // /** Distribute identitical balls into distinct boxes,
    //  * and boxes can be empty. */
    // ll balls_and_boxes_0(ll balls, ll boxes) {
    //     return C(balls + boxes - 1LL, balls);
    // }

    // /** Distribute identitical balls into distinct boxes,
    //  * and each box has at least one ball. */
    // ll balls_and_boxes_1(ll balls, ll boxes) {
    //     return C(balls - 1LL, boxes - 1LL);
    // }

    // ll stars_and_bars_0(ll stars, ll bars) {
    //     return balls_and_boxes_0(stars, bars + 1LL);
    // }

    // ll stars_and_bars_1(ll stars, ll bars) {
    //     return balls_and_boxes_1(stars, bars + 1LL);
    // }

    // ll H(ll n) {
    //     // Or H[n] = 1LL * (4LL * n - 2LL) * inv(n + 1LL) % MOD * H[n - 1LL]
    //     %
    //     // MOD;
    //     return C(2LL * n, n) - C(2LL * n, n - 1LL);
    // }

} comb;
