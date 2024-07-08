#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * When mod is a prime
 * 当模为质数
 */
ll qpow(ll x, ll n, ll mod) {
    ll res = 1;
    for (; n; n >>= 1) {
        if (n & 1LL) {
            res = res * x % mod;
        }
        x = x * x % mod;
    }
    return res;
}

ll inv(ll x, ll mod) {
    return qpow(x, mod - 2, mod);
}

/**
 * When mod is not a prime, see ExtendedEuclidean
 * 当模为非质数，见扩展欧几里得
 */
