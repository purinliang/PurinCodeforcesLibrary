#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;

struct FasterInv {
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

    ll inv(ll x) { return qpow(x, MOD - 2); }

    vector<int> calc(int n, const vector<int>& a) {
        vector<int> res(n + 2), suf(n + 2);
        suf[n + 1] = 1;
        for (int i = n; i >= 1; --i) {
            suf[i] = 1LL * suf[i + 1] * a[i] % MOD;
        }
        ll inv_prod = inv(suf[1]), pre = 1;
        for (int i = 1; i <= n; ++i) {
            res[i] = 1LL * pre * suf[i + 1] % MOD * inv_prod % MOD;
            pre = pre * a[i] % MOD;
        }
        return res;
    }
} f_inv;
