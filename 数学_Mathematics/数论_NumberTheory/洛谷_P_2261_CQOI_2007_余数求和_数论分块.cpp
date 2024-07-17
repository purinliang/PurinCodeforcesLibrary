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

ll n, k;

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

ll calc(ll n, ll m) {
    // For all i in [1, m], calc f(n / i)
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

void purin_init() {}

void purin_solve() {
    RD(n, k);
    // ans = \sum_{i = 1} ^ {n} k \mod i
    // ans = \sum_{i = 1} ^ {n} k - i * \lfloor \frac{k}{i} \rfloor
    // ans = n * k - \sum_{i = 1} ^ {n} i * \lfloor \frac{k}{i} \rfloor
    ll res = n * k - calc(k, n);
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
