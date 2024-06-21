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
    cin >> (var + 1);
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

namespace EulerSieveNotPrime {

vector<int> p;
vector<bool> not_p;

string to_string(int lim) {
    string res = "p = [";
    for (int j = 1; j < p.size() && j <= lim; ++j) {
        res += std::to_string(p[j]) + ", ";
    }
    res = res.substr(0, max(0, (int)res.length() - 2)) + "]";
    return res;
}

void show() {
#ifdef LOCAL
    cout << "[D] " << to_string(20) << endl;
#endif
}

void euler_sieve(int n) {
    p.clear();
    not_p.clear(), not_p.resize(n + 2);
    for (int i = 1; i <= n; ++i) {
        if (not_p[i] == 0) {
            p.push_back(i);
        }
        for (int j = 1, t; j < p.size() && (t = i * p[j]) <= n; ++j) {
            not_p[t] = true;
            if (i % p[j] == 0) {
                break;
            }
        }
    }

    show();
}
}  // namespace EulerSieveNotPrime

void purin_init() {
    const int MAXN = 1e8;
    EulerSieveNotPrime::euler_sieve(MAXN);
}

int n, q;

void purin_solve() {
    RD(n, q);
    D(n, q);
    while (q--) {
        int k;
        RD(k);
        WT(EulerSieveNotPrime::p[k]);
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
