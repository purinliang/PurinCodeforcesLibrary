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

struct SparseTable {
   private:
    static const int INF = 0x3F3F3F3F;
    static const ll LINF = 0x3F3F3F3F3F3F3F3F;

    int _n;
    vector<int> _log2;

    typedef int T;
    vector<vector<T>> _st1;
    function<T(T, T)> _op1 = [](T x, T y) -> T { return min(x, y); };
    T _op1_iden = INF;

    vector<vector<T>> _st2;
    function<T(T, T)> _op2 = [](T x, T y) -> T { return max(x, y); };
    T _op2_iden = -INF;

    void init_help(T* a, vector<vector<T>>& st, function<T(T, T)>& op) {
        st.clear(), st.resize(_n + 2);
        for (int i = 1; i <= _n; ++i) {
            st[i].resize(_log2[_n] + 1);
            st[i][0] = a[i];
        }
        for (int j = 1; j <= _log2[_n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= _n; ++i) {
                st[i][j] = op(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query_help(int l, int r, vector<vector<T>>& st, function<T(T, T)>& op, T op_iden) {
        l = max(l, 1), r = min(r, _n);
        if (l > r) {
            return op_iden;
        }
        int s = _log2[r - l + 1];
        return op(st[l][s], st[r - (1 << s) + 1][s]);
    }

   public:
    void init(int n, T* a) {
        _n = n;
        _log2.clear(), _log2.resize(_n + 2);
        for (int i = 2; i <= _n; ++i) {
            _log2[i] = _log2[i >> 1] + 1;
        }
        // init_help(a, _st1, _op1);
        init_help(a, _st2, _op2);
    }

    T query1(int l, int r) { return query_help(l, r, _st1, _op1, _op1_iden); }

    T query2(int l, int r) { return query_help(l, r, _st2, _op2, _op2_iden); }

} st;

void purin_init() {}

const int MAXN = 1e5 + 10;
int n, m;
int a[MAXN];

void purin_solve() {
    RD(n, m);
    RDN(a, n);
    st.init(n, a);
    while (m--) {
        int l, r;
        RD(l, r);
        WT(st.query2(l, r));
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
