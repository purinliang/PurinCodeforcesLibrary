#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
