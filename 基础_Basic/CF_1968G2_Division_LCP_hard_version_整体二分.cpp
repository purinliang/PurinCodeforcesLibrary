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
int n, l, r;
char s[MAXN];

struct BaseHash {
   private:
    /**
     * 如果你需要比较字符串原串 S 和它的反串 rev(S) ，设置 USING_REV = true
     * 并重新 init 。 If you need to compare the original string S and its
     * reversed version rev(S), set USING_REV = true, and init again.
     */
    static const bool USING_REV = false;

    int _b = 11, _p = 307, _mod = 998244353;
    vector<int> _h, _plen, _rev_h;

    inline int add_mod(const int& x, const int& y) const {
        return x + y >= _mod ? x + y - _mod : x + y;
    }

    inline int sub_mod(const int& x, const int& y) const {
        return x - y < 0 ? x - y + _mod : x - y;
    }

    inline int mul_mod(const int& x, const int& y) const {
        ll res = 1LL * x * y;
        if (res >= _mod) {
            res %= _mod;
        }
        return res;
    }

   public:
    void set_const(int b, int p, int mod) { _b = b, _p = p, _mod = mod; }

    void init(char* s) {
        int len = strlen(s + 1);
        _h.resize(len + 2), _h[0] = 0;
        _plen.resize(len + 2), _plen[0] = 1;
        for (int i = 1; i <= len; ++i) {
            _h[i] = add_mod(mul_mod(_h[i - 1], _p), (s[i] + _b));
            _plen[i] = mul_mod(_plen[i - 1], _p);
        }
        if (USING_REV) {
            _rev_h.resize(len + 2), _rev_h[len + 1] = 0;
            for (int i = len; i >= 1; --i) {
                _rev_h[i] = add_mod(mul_mod(_rev_h[i + 1], _p), (s[i] + _b));
            }
        }
    }

    int code(const int& l, const int& r) const {
        if (l > r) {
            return 0;
        }
        int res = sub_mod(_h[r], mul_mod(_h[l - 1], _plen[r - l + 1]));
        // cout << format("[{}, {}], rev_hashcode = {}", l, r, res) << endl;
        return res;
    }

    int rev_code(const int& l, const int& r) const {
        if (l > r) {
            return 0;
        }
        if (!USING_REV) {
            cerr << "Error, using rev_code without init!" << endl;
            exit(-1);
        }
        int res = sub_mod(_rev_h[l], mul_mod(_rev_h[r + 1], _plen[r - l + 1]));
        // cout << format("[{}, {}], rev_hashcode = {}", l, r, res) << endl;
        return res;
    }
};

struct MultiHash {
   private:
    static const int MAX_CHECK_TIMES = 8;
    int _b[MAX_CHECK_TIMES] = {11, 13, 17, 19, 23, 29, 31, 37};
    int _p[MAX_CHECK_TIMES] = {307, 311, 313, 317, 331, 337, 347, 349};
    int _mod[MAX_CHECK_TIMES] = {998244353, 998244389, 998244391, 998244397,
                                 998244407, 998244431, 998244433, 998244473};

    static const int CHECK_TIMES = 2;
    BaseHash _bh[CHECK_TIMES];

    void anti_hack() {
        static bool anti_hack_enabled = true;
        if (!anti_hack_enabled) {
            return;
        }
        anti_hack_enabled = false;
        int rnd_seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 rnd(rnd_seed);
        shuffle(_b, _b + MAX_CHECK_TIMES, rnd);
        shuffle(_p, _p + MAX_CHECK_TIMES, rnd);
        shuffle(_mod, _mod + MAX_CHECK_TIMES, rnd);
    }

    void init_bh_const() {
        anti_hack();
        for (int i = 0; i < CHECK_TIMES; ++i) {
            _bh[i].set_const(_b[i], _p[i], _mod[i]);
        }
    }

   public:
    void init(char* s) {
        init_bh_const();
        for (int i = 0; i < CHECK_TIMES; ++i) {
            _bh[i].init(s);
        }
    }

    ll code(const int& l, const int& r) const {
        ll res = 0;
        for (int i = 0; i < CHECK_TIMES; ++i) {
            res = (res << 32) ^ (_bh[i].code(l, r));
        }
        // cout << format("[{}, {}], hashcode = {}", l, r, res) << endl;
        return res;
    }

    ll rev_code(const int& l, const int& r) const {
        ll res = 0;
        for (int i = 0; i < CHECK_TIMES; ++i) {
            res = (res << 32) ^ (_bh[i].rev_code(l, r));
        }
        // cout << format("[{}, {}], rev_hashcode = {}", l, r, res) << endl;
        return res;
    }

    bool same(int l1, int r1, int l2, int r2) {
        for (int i = 0; i < CHECK_TIMES; ++i) {
            if (_bh[i].code(l1, r1) != _bh[i].code(l2, r2)) {
                return false;
            }
        }
        return true;
    }

    bool rev_same(int l1, int r1, int l2, int r2) {
        for (int i = 0; i < CHECK_TIMES; ++i) {
            if (_bh[i].code(l1, r1) != _bh[i].rev_code(l2, r2)) {
                return false;
            }
        }
        return true;
    }

} mh;

namespace MultiBinarySearch {

    struct Query {
        int id;
        int cnt;  // the parameter of the query
    };

    vector<Query> _vec_qry;
    vector<int> _ans;

    void init_query() {
        _vec_qry.clear();
    }

    void add_query(int cnt) {
        Query qry;
        qry.id = _vec_qry.size();
        qry.cnt = cnt;
        _vec_qry.push_back(qry);
    }

    int calc_cnt(int M) {  // when answer is M, calc the maximum cnt
        // int cnt = 0;
        // implement it, ordinary, the complexity is O(n)
        int cnt = 1;
        int pre_ok = 1;
        int len = M;
        auto f = mh.code(1, len);
        for (int i = 2; i + len - 1 <= n; ++i) {
            i = max(i, pre_ok + len);
            if (i + len - 1 > n) {
                break;
            }
            if (i - pre_ok >= len) {
                auto h = mh.code(i, i + len - 1);
                if (f == h) {
                    ++cnt;
                    pre_ok = i;
                }
            }
        }
        return cnt;
    }

    void multi_bs(int L, int R, vector<Query>& vec_qry) {
        if (L > R || vec_qry.empty()) {
            return;
        }
        if (L == R) {
            // Just like normal binary search, if there is always an answer
            // between the interval [L, R], then this solution is OK.
            // Otherwise, you should check whether there is a valid answer
            // when L == R.
            for (Query& qry : vec_qry) {
                _ans[qry.id] = L;
            }
            return;
        }
        int M = (L + R + 1) >> 1;  // Just like normal binary search, the value
                                   // of mid rely on how L and R move
        int cnt_M = calc_cnt(M);   // when answer is M, calc the maximum cnt
        vector<Query> vec_qry_L, vec_qry_R;
        // In certain problem, the parameter of Query would change, an example
        // is the k-th element in certain interval [L, R], the parameter k
        // should substract the count in left interval.
        for (auto& qry : vec_qry) {
            if (cnt_M < qry.cnt) {
                // cannot meet the reqirement of qry, to left
                // that is, R = M - 1
                vec_qry_L.push_back(qry);
            } else {
                // can meet the reqirement of qry, to right
                // that is, L = M
                vec_qry_R.push_back(qry);
            }
        }
        multi_bs(L, M - 1, vec_qry_L);
        multi_bs(M, R, vec_qry_R);
        return;
    }

    void calc_all_ans() {
        _ans.clear(), _ans.resize(_vec_qry.size());
        multi_bs(0, n, _vec_qry);
    }

    void show_all_ans() {
        for (int i = 0; i < _ans.size(); ++i) {
            cout << _ans[i] << " ";
        }
        cout << endl;
    }

};  // namespace MultiBinarySearch

using namespace MultiBinarySearch;

void purin_init() {}

void purin_solve() {
    RD(n, l, r);
    RD(s);

    mh.init(s);

    init_query();
    int q = r - l + 1;
    for (int i = 1; i <= q; ++i) {
        add_query(i + (l - 1));
    }
    calc_all_ans();
    show_all_ans();
}

int main() {
    const bool ignore_test_case_count = false;
#ifdef LOCAL
    purin_local_test(ignore_test_case_count);
#else
    purin_online_test(ignore_test_case_count);
#endif
    return 0;
}
