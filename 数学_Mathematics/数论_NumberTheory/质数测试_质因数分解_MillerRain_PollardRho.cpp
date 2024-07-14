#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/** MillerRabinPollardRho
 * Verify problem: https://www.luogu.com.cn/problem/P4718
 * Verify submission: https://www.luogu.com.cn/record/166018366 July 15, 2024
 */
struct MillerRabinPollardRho {
   private:
    // https://github.com/CharlesLiu7/Miller-Rabin-Primality-Test

    // If n < 2,152,302,898,747 (2e9),
    // it is enough to test 2, 3, 5, 7, 11.
    // vector<int> base_prime = {2, 3, 5, 7, 11};

    // If n < 3,317,044,064,679,887,385,961,981 (3e18),
    // it is enough to test 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41.
    vector<int> base_prime = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

    // The only pseudo prime < 1e16 is 46856248255981LL,
    // when testing 2, 3, 7, 61, 24251
    // vector<int> base_prime = {2, 3, 7, 61, 24251};

    ll qmul(ll a, ll b, ll mod) {
        return (__int128)a * b % mod;
    }

    ll qpow(ll x, ll n, ll mod) {
        // assert(n >= 0);
        if (x >= mod) x %= mod;
        ll res = 1LL;
        for (; n > 0LL; n >>= 1) {
            if (n & 1LL) res = qmul(res, x, mod);
            x = qmul(x, x, mod);
        }
        if (res >= mod) res %= mod;
        return res;
    }

    bool miller_rabin(ll n, ll p) {
        if (n < p) return false;
        for (ll k = n - 1LL; k > 0LL; k >>= 1) {
            ll t = qpow(p, k, n);
            if (t != 1LL && t != n - 1LL) return false;  // definitely false
            if ((k & 1LL) == 1LL || t == n - 1LL) return true;  // probably true
        }
        return true;  // probably true
    }

    ll pollard_rho(ll n) {
        ll s = 0LL, t = 0LL, c = rand() % (n - 1LL) + 1LL;
        for (int i = 1;; i <<= 1, s = t) {
            ll p = 1LL;
            for (int j = 1; j <= i; ++j) {
                t = (qmul(t, t, n) + c) % n;
                p = qmul(p, abs(t - s), n);
                if (p == 0LL) return n;
                if (j % 127 == 0) {
                    ll d = __gcd(p, n);
                    if (d > 1LL) return d;
                }
            }
            ll d = __gcd(p, n);
            if (d > 1LL) return d;
        }
    }

   public:
    bool is_prime(ll n) {
        // assert(n >= 0LL);
        if (n <= 1LL) return false;        // definitely false
        if (n <= 3LL) return true;         // definitely true
        if (n % 2LL == 0LL) return false;  // definitely false
        if (n == 46856248255981LL) {
            // 46856248255981LL is the only strong pseudo prime < 1e16
            return false;  // definitely false
        }
        for (const auto& bp : base_prime) {
            if (n < bp) {
                continue;
            }
            if (n == bp) return true;                // definitely true
            if (!miller_rabin(n, bp)) return false;  // definitely false
        }

        return true;  // probably true
    }

    /** For primes, return itself. For composite, return one of its factors
     * except itself. */
    ll get_factor(ll n) {
        if (n <= 3LL) return n;  // For 0, 1, 2, 3, return themselves.
        if (n % 2LL == 0LL) return 2LL;
        if (is_prime(n)) return n;
        do {
            ll d = pollard_rho(n);
            if (d != n) return d;  // Return when find a factor
        } while (true);
    }

} mrpr;

ll get_max_prime_factor(ll x) {
    if (x <= 1LL || mrpr.is_prime(x)) {
        return x;
    }
    ll d = mrpr.get_factor(x);
    assert(d >= 2 && d != x);
    ll res = 0LL;
    if (mrpr.is_prime(d)) {
        res = max(res, d);
    }
    res = max(res, get_max_prime_factor(d));
    res = max(res, get_max_prime_factor(x / d));
    return res;
}
