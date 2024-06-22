#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace Combinatorics {

// TODO: 复制模整数类进来，用这个类通过了的提交可以标上日期，贴在下面（不是贴题目）

// MOD must be a very big prime (e.g. at least 1e6) and bigger than max(n)
// static const int MOD = 998244353;

ll qpow(ll x, ll n) {
    ll res = 1;
    for (; n; n >>= 1) {
        if (n & 1LL) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
    }
    return res;
}

ll inv(ll x) {
    return qpow(x, MOD - 2);
}

vector<int> fac, inv_fac;

void _init(int n) {
    const int cur_max_n = (int)fac.size() - 1;
    if (n <= cur_max_n) {
        return;
    }
    n = max(n, 2 * cur_max_n);
    fac.resize(n + 1), inv_fac.resize(n + 1);
    for (int i = cur_max_n + 1; i <= n; ++i) {
        fac[i] = (i == 0) ? 1 : (1LL * fac[i - 1] * i % MOD);
    }
    for (int i = n; i >= cur_max_n + 1; --i) {
        inv_fac[i] = (i == n) ? inv(fac[n]) : (1LL * inv_fac[i + 1] * (i + 1) % MOD);
    }
}

ll A_slow(ll n, ll m) {
    const int MAX_M = 1e6 + 10;
    assert(m <= MAX_M);
    ll res = 1LL;
    for (int i = 1; i <= m; ++i) {
        res = 1LL * res * (n + 1 - i) % MOD;
    }
    return res;
}

ll C_slow(ll n, ll m) {
    m = min(n, n - m);
    const int MAX_M = 1e6 + 10;
    assert(m <= MAX_M);
    _init(m);
    return 1LL * A_slow(n, m) * inv_fac[m] % MOD;
}

ll A(ll n, ll m) {
    if (n < 0LL || m < 0LL || n < m) {
        return 0LL;
    }
    _init(n);
    return 1LL * fac[n] * inv_fac[n - m] % MOD;
}

ll C(ll n, ll m) {
    if (n < 0LL || m < 0LL || n < m) {
        return 0LL;
    }
    _init(n);
    return 1LL * A(n, m) * inv_fac[m] % MOD;
}

// Distribute identitical balls into distinct boxes, and boxes can be empty.
ll balls_and_boxes_0(ll balls, ll boxes) {
    return C(balls + boxes - 1, balls);
}

// Distribute identitical balls into distinct boxes, and each box has at least one ball.
ll balls_and_boxes_1(ll balls, ll boxes) {
    return C(balls - 1, boxes - 1);
}

ll stars_and_bars_0(ll stars, ll bars) {
    return balls_and_boxes_0(stars, bars + 1);
}

ll stars_and_bars_1(ll stars, ll bars) {
    return balls_and_boxes_1(stars, bars + 1);
}

ll H(ll n) {
    // Or H[n] = 1LL * (4 * n - 2) * inv(n + 1) % MOD * H[n - 1] % MOD;
    return C(2 * n, n) - C(2 * n, n - 1);
}

}  // namespace Combinatorics

using namespace Combinatorics;
