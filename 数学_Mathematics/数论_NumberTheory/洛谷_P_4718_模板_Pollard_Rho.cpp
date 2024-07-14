#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef LOCAL
#include ".\标准本地调试_StandardLocalDebug.h"
#else
#define D(...)
#define DN(arr, n)
#define DF()
#define ASSERT(x)

template <typename T>
void _RD(T& var) {
    cin >> var;
}

void _RD(char* var) {
    string str;
    cin >> str;
    strcpy(var + 1, str.c_str());
}

void RD() {}

template <typename T, typename... U>
void RD(T& Head, U&... Tail) {
    _RD(Head);
    RD(Tail...);
}

template <typename T>
void RDN(T* arr, int n) {
    for (int i = 1; i <= n; ++i) {
        _RD(arr[i]);
    }
}

template <typename T>
void _WT(const T& var) {
    cout << var;
}

void _WT(const char* var) {
    cout << (var + 1);
}

void WT() {}

template <typename T, typename... U>
void WT(const T& Head, const U&... Tail) {
    _WT(Head);
    cout << (sizeof...(Tail) ? " " : "\n");
    WT(Tail...);
}

void WTY(bool var, bool capital = false) {
    if (capital) {
        cout << (var ? "YES" : "NO") << "\n";
    } else {
        cout << (var ? "Yes" : "No") << "\n";
    }
}

template <typename T>
void WTN(T* arr, int n) {
    for (int i = 1; i <= n; ++i) {
        _WT(arr[i]);
        cout << (i < n ? " " : "\n");
    }
}

#endif

void purin_ios() {
    cout << fixed << setprecision(12);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#define endl "\n"
#define fout fflush(stdout)
}

void purin_init();
void purin_solve();

void purin_online_test(bool ignore_test_case_count) {
    purin_ios();
    purin_init();
    if (!ignore_test_case_count) {
        int t = 1;
        cin >> t;
        for (int i = 1; i <= t; ++i) {
            purin_solve();
        }
    } else {
        auto cin_eof = [&]() -> bool {
            char ch;
            while (cin >> ch) {
                if (!isspace(ch)) {
                    cin.unget();
                    return false;
                }
            }
            return cin.eof();
        };
        while (!cin_eof()) {
            purin_solve();
        }
    }
}

/* MY CODE BEGIN */

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
        for (ll k = n - 1LL; k; k >>= 1) {
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
        if (n == 46856248255981LL) {  // 46856248255981 is a strong pseudo prime
            return false;             // definitely false
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

void purin_init() {}

void purin_solve() {
    ll n;
    RD(n);
    assert(n >= 2LL);
    ll max_prime_factor = get_max_prime_factor(n);
    if (max_prime_factor == n) {
        cout << "Prime" << endl;
        return;
    }
    WT(max_prime_factor);
}

int main() {
    const bool ignore_test_case_count = false;
#ifdef LOCAL
    purin_local_test(ignore_test_case_count);
#else
    purin_online_test(ignore_test_case_count);
#endif
    return 0;
}
