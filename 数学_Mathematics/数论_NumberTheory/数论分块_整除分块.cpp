#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll s0(ll x) {  // s0(x) = 1 + 1 + 1 + ... 1 (the amount is x)
    return x;
}

ll s1(ll x) {  // s1(x) = 1 + 2 + 3 + ... x (may overflow)
    return 1LL * x * (x + 1LL) / 2LL;
}

ll s2(ll x) {  // s2(x) = 1^2 + 2^2 + 3^2 + ... x^2 (may overflow)
    return s1(x) * (2LL * x + 1LL) / 3LL;
}

ll f(ll x) {
    return x;
}

// calc \sum_{i = 1}^{m} i * f(n / i)
ll calc(ll n, ll m) {
    ll lim = min(n, m), ans = 0LL;
    for (ll l = 1LL, r; l <= lim; l = r + 1LL) {
        // For example n = 100, l = 26
        // n / l = 3, n / (n / l) = 33
        // if m = 30, lim = 30, r = min(lim, n / (n / l)) = 30
        r = min(lim, n / (n / l));
        // For all i in [l, r], n / i is constant.
        // So we can calc them at the same time
        ans += 1LL * (s1(r) - s1(l - 1)) * f(n / l);
    }
    return ans;
}
