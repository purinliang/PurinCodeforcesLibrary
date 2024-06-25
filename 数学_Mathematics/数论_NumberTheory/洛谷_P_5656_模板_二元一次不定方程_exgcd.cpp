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

void purin_init() {}

/**
 * ExGcd
 */
struct ExtendedEuclid {
   private:
    static ll ex_gcd(ll a, ll b, ll& x, ll& y) {
        if (b == 0) {
            x = 1, y = 0;
            return a;
        }
        ll d = ex_gcd(b, a % b, x, y), t;
        t = x, x = y, y = t - a / b * y;
        return d;
    }

   public:
    /**
     * solve ax + by == c
     *
     * if x0 < 0, there is not solution. otherwise, answer is the smallest x0 >= 0 and its
     * coressponding y0, all answers look like: x = x0 + k * dx, y = y0 + k * dy, dx > 0, dy > 0
     */
    static tuple<ll, ll, ll, ll> solve_ax_plus_by_equal_to_c(ll a, ll b, ll c) {
        ll x0 = 0, y0 = 0, dx = 0, dy = 0;
        ll d = ex_gcd(a, b, x0, y0), t = b / d;
        if (c % d != 0) {
            // no solution
            x0 = -1, y0 = -1, dx = -1, dy = -1;
            return {x0, y0, dx, dy};
        }
        // solution is: x = x + k * dx, y = y - k * dy
        x0 = ((x0 % t) * (c / d % t) % t + t) % t;
        y0 = (c - a * x0) / b, dx = t, dy = a / d;
        assert(dx > 0 && dy > 0);
        return {x0, y0, dx, dy};
    }

    /**
     * solve ax == r mod m, m may be not a prime.
     * ax == r mod m <==> ax + my == r
     *
     * if x0 < 0, there is not solution, otherwise, answer is the smallest x0 >= 0 and its
     * coressponding y0, all answers look like: x = x0 + k * dx, dx > 0
     */
    static tuple<ll, ll> solve_ax_equal_to_r_mod_m(ll a, ll r, ll m) {
        auto [x0, y0, dx, dy] = solve_ax_plus_by_equal_to_c(a, m, r);
        return {x0, dx};
    }

    /**
     * find inv of a, when mod is m, m may be not a prime
     * let x == inv(a), a * inv(a) == 1 mod m <==> ax == 1 mod m,
     *
     * if x0 < 0, there is not solution, otherwise, answer is the smallest x0 >= 0 and its
     * coressponding y0, all answers look like: x = x0 + k * dx, dx > 0
     */
    static tuple<ll, ll> inv(ll a, ll m) {
        auto [x0, dx] = solve_ax_equal_to_r_mod_m(a, 1, m);
        return {x0, dx};
    }
};

void purin_solve() {
    ll a, b, c;
    RD(a, b, c);
    auto [x0, y0, dx, dy] = ExtendedEuclid::solve_ax_plus_by_equal_to_c(a, b, c);
    if (x0 == -1) {
        WT(-1);
        return;
    }
    D(x0, y0, dx, dy);
    assert(dx > 0 && dy > 0);
    if (x0 == 0) {
        x0 += dx;
        y0 -= dy;
    }
    if (x0 > 0 && y0 > 0) {
        ll minx = x0, maxx = x0;
        ll miny = y0, maxy = y0;
        ll cnt = 1;
        for (int i = 30; i >= 0; --i) {
            ll k = 1LL << i;
            if (y0 - k * dy > 0) {
                y0 -= k * dy;
                x0 += k * dx;
                cnt += k;
            }
        }
        minx = min(minx, x0);
        maxx = max(maxx, x0);
        miny = min(miny, y0);
        maxy = max(maxy, y0);
        WT(cnt, minx, miny, maxx, maxy);
        return;
    } else {
        ll minx = x0;
        for (int i = 30; i >= 0; --i) {
            ll k = 1LL << i;
            if (y0 + k * dy <= 0) {
                y0 += k * dy;
                x0 -= k * dx;
            }
        }
        y0 += dy;
        x0 -= dx;
        ll miny = y0;
        WT(minx, miny);
    }
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
