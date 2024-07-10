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

const int MAXN = 2e5 + 10;
int n, a[MAXN];
vector<int> pos[MAXN];
int len, idx[MAXN];

/** 单点加 */
struct BinaryIndexTreeAdd {
   private:
    int _n;
    vector<ll> _sum;

   public:
    void init(int n) {
        _n = n;
        _sum.clear(), _sum.resize(_n + 2);
    }

    void add(int idx, ll val) {
        for (int i = idx; i <= _n; i += i & (-i)) {
            _sum[i] += val;
        }
    }

    ll sum(int idx) {
        ll res = 0;
        for (int i = idx; i; i -= i & (-i)) {
            res += _sum[i];
        }
        return res;
    }

    ll sum(int lidx, int ridx) {
        return sum(ridx) - sum(lidx - 1);
    }

} bit_add;

namespace MultiBinarySearch {
    struct Query {
        int id;
        int l, r, k;  // the parameter of the query
    };

    vector<Query> _vec_qry;
    vector<int> _ans;

    void init_query(int q_cnt = 0) {
        _vec_qry.clear();
        _vec_qry.reserve(q_cnt);
    }

    void add_query(int l, int r, int k) {
        Query qry;
        qry.id = _vec_qry.size();
        qry.l = l;
        qry.r = r;
        qry.k = k;
        _vec_qry.push_back(qry);
    }

    vector<int> sum;

    void calc_k(int M,
                int dir) {  // when answer is M, calc how many elements <= M
        for (int i = 1; i <= M; ++i) {
            for (auto& p : pos[i]) {
                bit_add.add(p, dir);
            }
        }
    }

    bool is_right_query(Query& qry) {
        int k_M = bit_add.sum(qry.r) - bit_add.sum(qry.l - 1);
        return qry.k > k_M;
    }

    void multi_bs(int L, int R, int ql, int qr) {
        if (L > R || ql > qr) {
            return;
        }
        if (L == R) {
            // Just like normal binary search, if there is always an answer
            // between the interval [L, R], then this solution is OK.
            // Otherwise, you should check whether there is a valid answer
            // when L == R.
            for (int i = ql; i <= qr; ++i) {
                Query& qry = _vec_qry[i];
                _ans[qry.id] = idx[L];
            }
            return;
        }
        int M = (L + R) >> 1;  // Just like normal binary search, the value
                               // of mid rely on how L and R move
        calc_k(M, 1);

        vector<Query> vec_qry_L, vec_qry_R;
        // In certain problem, the parameter of Query would change.
        int i = ql, j = qr;
        while (i < j) {
            while (i < j) {
                // there are k_M elements in [l, r] that <= M
                // k_M >= qry.k means that M may be too large, R = M
                // to left
                if (is_right_query(_vec_qry[i])) {
                    ++i;
                    continue;
                }
                break;
            }
            while (i < j) {
                // there are k_M elements in [l, r] that <= M
                // k_M < qry.k means that M must be too small, L = M + 1
                // to right
                if (!is_right_query(_vec_qry[i])) {
                    --j;
                    continue;
                }
                break;
            }
            if (i < j) {
                swap(_vec_qry[i], _vec_qry[j]);
                ++i;
                --j;
            }
        }
        int qm = i - (!is_right_query(_vec_qry[i]));
        calc_k(M, -1);
        multi_bs(L, M, ql, qm);
        multi_bs(M + 1, R, qm + 1, qr);
        return;
    }

    void calc_all_ans(int L, int R) {
        bit_add.init(R - L + 1);
        int cnt_q = _vec_qry.size();
        _ans.clear(), _ans.resize(cnt_q);
        multi_bs(L, R, 0, cnt_q - 1);
    }

    void show_all_ans() {
        for (int i = 0; i < _ans.size(); ++i) {
            cout << _ans[i] << endl;
        }
    }

};  // namespace MultiBinarySearch

using namespace MultiBinarySearch;

void purin_init() {}

void purin_solve() {
    int m;
    RD(n, m);
    RDN(a, n);
    for (int i = 1; i <= n; ++i) {
        idx[i] = a[i];
    }
    sort(idx + 1, idx + 1 + n);
    len = unique(idx + 1, idx + 1 + n) - (idx + 1);
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(idx + 1, idx + 1 + len, a[i]) - idx;
    }
    WTN(a, n);
    for (int i = 1; i <= len; ++i) {
        pos[i].clear();
    }
    for (int i = 1; i <= n; ++i) {
        pos[a[i]].push_back(i);
    }
    init_query(m);
    D(m);
    while (m--) {
        int l, r, k;
        RD(l, r, k);
        add_query(l, r, k);
    }
    calc_all_ans(1, len);
    show_all_ans();
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
