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

const int MAXN = 3e6 + 10;
int n, a[MAXN];
int ans[MAXN];

void purin_init() {}

struct MonotonicStack {
    static const int INF = 0x3F3F3F3F;

    /**
     * vector<T> a and vector<int> res are both 1-index based.
     */
    template <typename T>
    static vector<int> find_leftmost(int n, vector<T> a, function<bool(int, int)> pred,
                                     int not_exist = INF) {
        assert(a.size() >= n + 1);
        vector<int> res(n + 2);
        stack<int> stk;
        for (int i = 1; i <= n; ++i) {
            while (!stk.empty() && pred(a[i], a[stk.top()])) {
                res[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }
        while (!stk.empty()) {
            res[stk.top()] = not_exist;
            stk.pop();
        }
        return res;
    }

    /**
     * vector<T> a and vector<int> res are both 1-index based.
     */
    template <typename T>
    static vector<int> find_rightmost(int n, vector<T> a, function<bool(int, int)> pred,
                                      int not_exist = -INF) {
        assert(a.size() >= n + 1);
        vector<int> res(n + 2);
        stack<int> stk;
        for (int i = n; i >= 1; ++i) {
            while (!stk.empty() && pred(a[i], a[stk.top()])) {
                res[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }
        while (!stk.empty()) {
            res[stk.top()] = not_exist;
            stk.pop();
        }
        return res;
    }
};

/**
 * Find the leftmost a[j] that j > i and a[j] greater than a[i], when not exist answer is n + 1
 * auto res = MonotonicStack::find_leftmost<int>(n, a, greater<int>(), n + 1);
 * Find the rightmost a[j] that j < i and a[j] greater than a[i], when not exist answer is 0
 * auto res = MonotonicStack::find_rightmost<int>(n, a, greater<int>(), 0);
 */

void purin_solve() {
    RD(n);
    RDN(a, n);
    vector<int> vec(n + 1);
    for (int i = 1; i <= n; ++i) {
        vec[i] = a[i];
    }
    auto res = MonotonicStack::find_leftmost<int>(n, vec, greater<int>(), 0);
    for (int i = 1; i <= n; ++i) {
        ans[i] = res[i];
    }
    WTN(ans, n);
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
