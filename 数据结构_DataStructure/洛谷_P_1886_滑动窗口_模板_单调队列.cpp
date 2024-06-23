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

const int MAXN = 1e6 + 10;
int n, k, a[MAXN];

/**
 * 其实可以用两个栈实现的队列来完全代替，不过单调队列理解起来比较简单
 * 如果队头是最大的，那就是greater，如果队头最小，那就是less
 */
template <typename T>
struct MonotonicQueue {
    deque<int> _que;
    function<bool(T, T)> _pred;

    MonotonicQueue(function<bool(T, T)> pred) { _pred = pred; }

    void push(int idx) {
        while (!_que.empty() && _pred(idx, _que.back())) {
            _que.pop_back();
        }
        _que.push_back(idx);
    }

    void pop() {
        if (!_que.empty()) {
            _que.pop_front();
        }
    }

    void pop_less_equal(int idx) {
        while (!_que.empty() && _que.front() <= idx) {
            _que.pop_front();
        }
    }

    void pop_greater_equal(int idx) {
        while (!_que.empty() && _que.front() >= idx) {
            _que.pop_front();
        }
    }

    int front() {
        if (!_que.empty()) {
            return _que.front();
        }
        return -1;
    }

    bool empty() { return _que.empty(); }

    int size() { return _que.size(); }
};

void purin_init() {}

int ans_mi[MAXN], ans_ma[MAXN];

void purin_solve() {
    RD(n, k);
    RDN(a, n);

    auto less = [&](int n, int o) { return a[n] < a[o]; };
    auto greater = [&](int n, int o) { return a[n] > a[o]; };
    MonotonicQueue<int> min_que(less);
    MonotonicQueue<int> max_que(greater);

    for (int i = 1; i <= k; ++i) {
        max_que.push(i);
        min_que.push(i);
        D(max_que.front());
        D(min_que.front());
    }

    int top = 0;
    for (int i = k; i <= n; ++i) {
        ++top;
        ans_mi[top] = a[min_que.front()];
        ans_ma[top] = a[max_que.front()];
        min_que.pop_less_equal(i - k + 1);
        max_que.pop_less_equal(i - k + 1);
        if (i + 1 <= n) {
            min_que.push(i + 1);
            max_que.push(i + 1);
        }
    }
    WTN(ans_mi, top);
    WTN(ans_ma, top);
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
