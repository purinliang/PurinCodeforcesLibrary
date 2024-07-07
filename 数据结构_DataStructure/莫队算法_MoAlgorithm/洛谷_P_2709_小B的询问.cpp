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

const int MAXN = 5e4 + 10;

int n, m, k;
int a[MAXN];

namespace MoAlgorithm {

    struct Query {
        int l, r, id;
        ll ans = 0LL;
        Query() {}
        Query(int _l, int _r, int _id) {
            l = _l, r = _r, id = _id;
        }
    };

    int n;
    vector<Query> q;

    void init(int _n) {
        n = _n;
        q.clear();
    }

    void add_query(int l, int r) {
        q.push_back(Query(l, r, q.size() + 1));
    }

    /* Calc Answer */

    int l, r;
    ll ans;
    vector<int> cnt;

    ll sq(ll x) {
        return x * x;
    }

    void extend_left() {
        ans -= sq(cnt[a[l]]);
        ++cnt[a[l]];
        ans += sq(cnt[a[l]]);
    }

    void extend_right() {
        ans -= sq(cnt[a[r]]);
        ++cnt[a[r]];
        ans += sq(cnt[a[r]]);
    }

    void shrink_left() {
        ans -= sq(cnt[a[l]]);
        --cnt[a[l]];
        ans += sq(cnt[a[l]]);
    }

    void shrink_right() {
        ans -= sq(cnt[a[r]]);
        --cnt[a[r]];
        ans += sq(cnt[a[r]]);
    }

    void calc_all_ans() {
        int sqrtn = ceil(sqrt(n));
        sort(q.begin(), q.end(), [&](Query& q1, Query& q2) {
            if (q1.l / sqrtn != q2.l / sqrtn) return q1.l < q2.l;
            return ((q1.l / sqrtn) & 1) ? (q1.r < q2.r) : (q1.r > q2.r);
        });

        l = 1, r = 0, ans = 0LL;
        cnt.clear(), cnt.resize(k + 2);
        for (auto& [ql, qr, qid, qans] : q) {
            while (ql < l) {
                --l;
                extend_left();
            }
            while (qr > r) {
                ++r;
                extend_right();
            }
            while (ql > l) {
                shrink_left();
                ++l;
            }
            while (qr < r) {
                shrink_right();
                --r;
            }
            qans = ans;
        }
    }

    void show_all_ans() {
        sort(q.begin(), q.end(),
             [&](Query& q1, Query& q2) { return q1.id < q2.id; });
        for (int i = 0; i < q.size(); ++i) {
            cout << q[i].ans << endl;
        }
    }

}  // namespace MoAlgorithm

void purin_init() {}

void purin_solve() {
    RD(n, m, k);
    RDN(a, n);
    MoAlgorithm::init(n);
    for (int i = 1; i <= m; ++i) {
        int l, r;
        RD(l, r);
        MoAlgorithm::add_query(l, r);
    }
    MoAlgorithm::calc_all_ans();
    MoAlgorithm::show_all_ans();
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
