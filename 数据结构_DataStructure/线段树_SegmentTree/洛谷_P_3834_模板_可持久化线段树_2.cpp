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

int n;
const int MAXN = 2e5 + 10;
int a[MAXN];

struct PersistentSegmentTree {
   private:
    int len;
    vector<int> _root;
    vector<int> _val;  // 每个叶子节点存的是哪个值
    vector<int> _sum, _lch,
        _rch;  // sum的维护比较特殊，因为每次只有1个新元素加入

    int cnt_node;

    int get_idx(const int& val) {  // 找到val应该放在哪个叶子
        return lower_bound(_val.begin() + 1, _val.begin() + 1 + len, val) -
               _val.begin();
    }

    int get_new_u() {
        int new_u = ++cnt_node;
        return new_u;
    }

    int build(int l, int r) {
        int u = get_new_u();
        if (l == r) {
            return u;
        }
        int mid = (l + r) >> 1;
        _lch[u] = build(l, mid);
        _rch[u] = build(mid + 1, r);
        return u;
    }

    int update(int l, int r, int pos, int old_u) {
        int new_u = get_new_u();
        _lch[new_u] = _lch[old_u], _rch[new_u] = _rch[old_u];
        _sum[new_u] = _sum[old_u] + 1;
        if (l == r) {
            return new_u;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            _lch[new_u] = update(l, mid, pos, _lch[old_u]);
        } else {
            _rch[new_u] = update(mid + 1, r, pos, _rch[old_u]);
        }
        return new_u;
    }

    /**
     * 查询[l, r]区间内的第k小
     */
    int query(int lu, int ru, int l, int r, int k) {
        if (l == r) {
            return l;
        }
        int left_sum = _sum[_lch[ru]] - _sum[_lch[lu]];
        int mid = (l + r) >> 1;
        if (k <= left_sum) {
            return query(_lch[lu], _lch[ru], l, mid, k);
        } else {
            return query(_rch[lu], _rch[ru], mid + 1, r, k - left_sum);
        }
    }

   public:
    void init(int n, int* a) {
        _val.clear(), _val.resize(n + 2);
        for (int i = 1; i <= n; ++i) {
            _val[i] = a[i];
        }
        sort(_val.begin() + 1, _val.begin() + 1 + n);
        len =
            unique(_val.begin() + 1, _val.begin() + 1 + n) - (_val.begin() + 1);
        _sum.clear(), _lch.clear(), _rch.clear();
        cnt_node = 0;
        int reserve_size = (4 * len + n * (log2(len) + 1));
        _sum.resize(reserve_size), _lch.resize(reserve_size),
            _rch.resize(reserve_size);
        _root.clear(), _root.resize(n + 2);
        _root[0] = build(1, len);
        for (int i = 1; i <= n; ++i) {
            _root[i] = update(1, len, get_idx(a[i]), _root[i - 1]);
        }
    }

    int query(int l, int r, int k) {
        int pos = query(_root[l - 1], _root[r], 1, len, k);
        return _val[pos];
    }
} pst;

void purin_init() {}

void purin_solve() {
    int m;
    RD(n, m);
    RDN(a, n);

    pst.init(n, a);
    while (m--) {
        int l, r, k;
        RD(l, r, k);
        int res = pst.query(l, r, k);
        WT(res);
    }
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
