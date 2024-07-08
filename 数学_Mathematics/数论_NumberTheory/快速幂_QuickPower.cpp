#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

// ll smul_safe(ll a, ll b, ll mod) {
//     if (a >= mod) {
//         a %= mod;
//     }
//     ll res = 0;
//     for (; b; b >>= 1) {
//         if (b & 1LL) {
//             res = (res + a) % mod;
//         }
//         a = (a + a) % mod;
//     }
//     return res;
// }

// ll qpow_safe(ll x, ll n, ll mod) {
//     if (x >= mod) {
//         x %= mod;
//     }
//     ll res = 1 % mod;
//     for (; n; n >>= 1) {
//         if (n & 1LL) {
//             res = res * x % mod;
//         }
//         x = x * x % mod;
//     }
//     return res;
// }
