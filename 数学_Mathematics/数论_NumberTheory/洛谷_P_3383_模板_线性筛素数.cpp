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

struct BaseSieve {
    vector<int> p;

    string to_string(int lim) {
        string res = "p = [";
        for (const auto& d : p) {
            if (d > lim) {
                break;
            }
            res += std::to_string(d) + ", ";
        }
        res = res.substr(0, max(0, (int)res.length() - 2)) + "]";
        return res;
    }

    void show() {
#ifdef LOCAL
        cout << "[D] " << to_string(20) << endl;
#endif
    }

    template <typename function>
    void calc_prime_divisor(ll x, bool skip_1, function f) {
        if (!skip_1) {
            f(1);
        }
        // Could be faster if preprocess minimal prime divisor of x
        for (const auto& d : p) {
            if (d * d > x) {
                break;
            }
            if (d == 1 || x % d != 0) {
                continue;
            }
            f(d);
            while (x % d == 0) {
                x /= d;
            }
        }
        if (x != 1) {
            f(x);
        }
    }

    template <typename function>
    void calc_any_divisor(ll x, bool skip_1, function f) {
        if (!skip_1) {
            f(1);
        }
        // Could be faster if preprocess all divisor of x
        for (ll d = 2; d * d <= x; ++d) {
            if (x % d != 0) {
                continue;
            }
            f(d);
            if (d * d != x) {
                f(x / d);
            }
        }
    }
};

// TODO 补充其他的数论函数
struct SieveOfEratosthenesNotPrime : public BaseSieve {
    vector<bool> not_p;

    void init(int n) {
        p.clear();
        not_p.clear(), not_p.resize(n + 2);
        for (int i = 1; i <= n; ++i) {
            if (not_p[i] == 0) {
                p.push_back(i);
                for (int j = 2 * i; j <= n; j += i) {
                    not_p[j] = true;
                }
            }
        }
        show();
    }
};

SieveOfEratosthenesNotPrime sieve;

void purin_init() {
    const int MAXN = 1e8;
    sieve.init(MAXN);
}

int n, q;

void purin_solve() {
    RD(n, q);
    D(n, q);
    while (q--) {
        int k;
        RD(k);
        WT(sieve.p[k]);
    }
}

int main() {
    const int IGNORE_TEST_CASE_COUNT = true;
#ifdef LOCAL
    purin_local_test(IGNORE_TEST_CASE_COUNT);
#else
    purin_online_test(IGNORE_TEST_CASE_COUNT);
#endif
    return 0;
}
