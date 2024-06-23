#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

/**
 * auto less = [&](int n, int o) { return a[n] < a[o]; };
 * auto greater = [&](int n, int o) { return a[n] > a[o]; };
 * MonotonicQueue<int> min_que(less);
 * MonotonicQueue<int> max_que(greater);
 *
 * ans_min[i] = a[min_que.front()];
 * ans_max[i] = a[max_que.front()];
 */
