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

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

namespace Combinatorics {

// MOD must be a very big prime (e.g. at least 1e6) and bigger than max(n)
static const int MOD = 998244353;

ll qpow(ll x, ll n) {
    ll res = 1;
    for (; n; n >>= 1) {
        if (n & 1) {
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

ll A(ll n, ll m) {
    if (n < 0 || m < 0 || n < m) {
        return 0;
    }
    _init(n);
    return 1LL * fac[n] * inv_fac[n - m] % MOD;
}

ll C(ll n, ll m) {
    if (n < 0 || m < 0 || n < m) {
        return 0;
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

void purin_init() {}

int res = 0;

void purin_solve() {
    int t, maxn;
    RD(t, maxn);
    res = 0;
    while (t--) {
        int n, m;
        RD(n, m);
        int x = C(n, m);
        D(n, m, x);
        res ^= x;
    }
    WT(res);
}

int main() {
    const bool ignore_test_case_count = true;
#ifdef LOCAL
    purin_local_test(ignore_test_case_count);
#else
    purin_online_test(ignore_test_case_count);
#endif
    return 0;
}
