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

/**
 * 可持久化权值线段树
 * 查询[l, r]区间内的第k小值
 *
 * 模板题：
 * https://www.luogu.com.cn/problem/P3834
 */
struct PersistentSegmentTree {
   private:
    int _len;
    vector<int> _val;
    vector<int> _root, _sum, _lch, _rch;

    int get_idx(const int& val) {  // 找到val应该放在哪个叶子
        return lower_bound(_val.begin() + 1, _val.begin() + 1 + _len, val) -
               _val.begin();
    }

    int get_new_u() {
        int new_u = _sum.size();
        _sum.push_back(0), _lch.push_back(0), _rch.push_back(0);
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

    void init_val(int n, int* a) {
        _val.clear(), _val.resize(n + 2);
        for (int i = 1; i <= n; ++i) {
            _val[i] = a[i];
        }
        sort(_val.begin() + 1, _val.begin() + 1 + n);
        _len =
            unique(_val.begin() + 1, _val.begin() + 1 + n) - (_val.begin() + 1);
    }

    void init_node(int n) {
        int reserve_size = (4 * _len + n * (log2(_len) + 1));
        _sum.clear(), _sum.reserve(reserve_size);
        _lch.clear(), _lch.reserve(reserve_size);
        _rch.clear(), _rch.reserve(reserve_size);
        int skipped_u = get_new_u();  // skip u == 0
    }

    void init_root(int n, int* a) {
        _root.clear(), _root.resize(n + 2);
        _root[0] = build(1, _len);
        for (int i = 1; i <= n; ++i) {
            _root[i] = update(1, _len, get_idx(a[i]), _root[i - 1]);
        }
    }

   public:
    void init(int n, int* a) {
        init_val(n, a);
        init_node(n);
        init_root(n, a);
    }

    int query(int l, int r, int k) {
        int pos = query(_root[l - 1], _root[r], 1, _len, k);
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
