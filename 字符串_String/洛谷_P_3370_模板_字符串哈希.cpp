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

struct BaseHash {
   private:
    /**
     * 如果你需要比较字符串原串 S 和它的反串 rev(S) ，设置 USING_REV = true 并重新 init 。
     * If you need to compare the original string S and its reversed version rev(S),
     * set USING_REV = true, and init again.
     */
    static const bool USING_REV = false;

    int _b = 11, _p = 307, _mod = 998244353;
    vector<int> _h, _plen, _rev_h;

    inline int add_mod(const int& x, const int& y, const int& mod) const {
        return x + y >= _mod ? x + y - mod : x + y;
    }

    inline int sub_mod(const int& x, const int& y, const int& mod) const {
        return x - y < 0 ? x - y + mod : x - y;
    }

    inline int mul_mod(const int& x, const int& y, const int& mod) const {
        ll res = 1LL * x * y;
        if (res >= mod) {
            res %= mod;
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
            _h[i] = add_mod(mul_mod(_h[i - 1], _p, _mod), (s[i] + _b), _mod);
            _plen[i] = mul_mod(_plen[i - 1], _p, _mod);
        }
        if (USING_REV) {
            _rev_h.resize(len + 2), _rev_h[len + 1] = 0;
            for (int i = len; i >= 1; --i) {
                _rev_h[i] = add_mod(mul_mod(_rev_h[i + 1], _p, _mod), (s[i] + _b), _mod);
            }
        }
    }

    int code(const int& l, const int& r) const {
        if (l > r) {
            return 0;
        }
        int res = sub_mod(_h[r], mul_mod(_h[l - 1], _plen[r - l + 1], _mod), _mod);
        // cout << std::format("[l, r] = [{}, {}], hashcode = {}", l, r, res) << endl;
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
        int res = sub_mod(_rev_h[l], mul_mod(_rev_h[r + 1], _plen[r - l + 1], _mod), _mod);
        // cout << std::format("[l, r] = [{}, {}], rev_hashcode = {}", l, r, res) << endl;
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
        // cout << std::format("[l, r] = [{}, {}], hashcode = {}", l, r, res) << endl;
        return res;
    }

    ll rev_code(const int& l, const int& r) const {
        ll res = 0;
        for (int i = 0; i < CHECK_TIMES; ++i) {
            res = (res << 32) ^ (_bh[i].rev_code(l, r));
        }
        // cout << std::format("[l, r] = [{}, {}], rev_hashcode = {}", l, r, res) << endl;
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

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 3e5 + 10;

void purin_init() {}

int n;
char s[MAXN];

void purin_solve() {
    RD(n);
    BaseHash bh;
    set<int> S;
    while (n--) {
        RD(s);
        bh.init(s);
        int len = strlen(s + 1);
        int hcode = bh.code(1, len);
        S.insert(hcode);
    }
    WT(S.size());
}

int main() {
    const int IGNORE_TEST_CASE_COUNT = true;
#ifdef LOCAL
    purin_local_test(IGNORE_TEST_CASE_COUNT);
#else
    purin_online_test(IGNORE_TEST_CASE_COUNT);
#endif
    return 0;
}
