#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef LOCAL
#include "工具_Tools/比赛模板_CompetitionTemplate/标准本地调试_StandardLocalDebug.h"
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

void _WT(const char* var) { cout << (var + 1); }

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
const int MAXN = 3e5 + 10;

void purin_init() {}

struct NodeTagAdd {
    ll _add_tag = 0LL;
    NodeTagAdd(ll val = 0LL) { _add_tag = val; }
    void apply_tag(int l, int r, const NodeTagAdd& tag) {
        if (tag._add_tag != 0LL) _add_tag += tag._add_tag;
    }
};

struct NodeTagSet {
    pair<bool, ll> _set_tag = {false, 0LL};
    NodeTagSet(ll val = 0LL, bool set = false) {
        if (set) _set_tag = {true, val};
    }
    void apply_tag(int l, int r, const NodeTagSet& tag) {
        if (tag._set_tag.first != false) _set_tag = tag._set_tag;
    }
};

template <bool using_sum, bool using_min, bool using_max>
struct NodeInfoPolicy {
    using value_type = ll;
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

    struct Empty{};
    std::conditional_t<using_sum, ll, Empty> _sum{0LL};
    std::conditional_t<using_min, ll, Empty> _min{LINF};
    std::conditional_t<using_max, ll, Empty> _max{-LINF};

    NodeInfoPolicy() = default;
    NodeInfoPolicy(value_type val) {
        if constexpr (using_sum) _sum = val;
        if constexpr (using_min) _min = val;
        if constexpr (using_max) _max = val;
    }

    void merge(const NodeInfoPolicy& lch, const NodeInfoPolicy& rch) {
        if constexpr (using_sum) _sum = lch._sum + rch._sum;
        if constexpr (using_min) _min = std::min(lch._min, rch._min);
        if constexpr (using_max) _max = std::max(lch._max, rch._max);
    }

    void apply_tag(int l, int r, const NodeTagAdd& tag) {
        if (tag._add_tag != 0LL) {
            if constexpr (using_sum) _sum += 1LL * (r - l + 1) * tag._add_tag;
            if constexpr (using_min) _min += tag._add_tag;
            if constexpr (using_max) _max += tag._add_tag;
        }
    }

    void apply_tag(int l, int r, const NodeTagSet& tag) {
        if (tag._set_tag.first != false) {
            if constexpr (using_sum) _sum = 1LL * (r - l + 1) * tag._set_tag.second;
            if constexpr (using_min) _min = tag._set_tag.second;
            if constexpr (using_max) _max = tag._set_tag.second;
        }
    }
};

template <typename NodeTag, typename NodeInfo>
struct SegmentTree {
   private:
    int _n;
    vector<NodeTag> _tag;
    vector<NodeInfo> _info;

    inline int lch(int u) { return u * 2; }
    inline int rch(int u) { return u * 2 + 1; }
    inline int mid(int l, int r) { return (l + r) / 2; }

    void pull_up(int u, int l, int r) { _info[u] = NodeInfo(l, r, _info[lch(u)], _info[rch(u)]); }

    void push_down(int u, int l, int r) {
        _info[lch(u)].apply_tag(l, mid(l, r), _tag[u]);
        _info[rch(u)].apply_tag(mid(l, r) + 1, r, _tag[u]);
        _tag[lch(u)].apply_tag(l, mid(l, r), _tag[u]);
        _tag[rch(u)].apply_tag(mid(l, r) + 1, r, _tag[u]);
        _tag[u] = NodeTag();
    }

    void build(int u, int l, int r, typename NodeInfo::value_type* a) {
        if (l == r) {
            _info[u] = (a != nullptr) ? NodeInfo(a[l]) : NodeInfo();
            _tag[u] = NodeTag();
            return;
        }
        build(lch(u), l, mid(l, r), a);
        build(rch(u), mid(l, r) + 1, r, a);
        pull_up(u, l, r);
    }

    void update(int u, int l, int r, int L, int R, const NodeTag& upd_tag) {
        if (L > R || L > r || R < l) {
            return;
        }
        if (L <= l && r <= R) {
            _info[u].apply_tag(l, r, upd_tag);
            _tag[u].apply_tag(l, r, upd_tag);
            return;
        }
        push_down(u, l, r);
        update(lch(u), l, mid(l, r), L, R, upd_tag);
        update(rch(u), mid(l, r) + 1, r, L, R, upd_tag);
        pull_up(u, l, r);
    }

    NodeInfo query(int u, int l, int r, int L, int R) {
        if (L > R || L > r || R < l) {
            return NodeInfo();
        }
        if (L <= l && r <= R) {
            return _info[u];
        }
        push_down(u, l, r);
        NodeInfo lres = query(lch(u), l, mid(l, r), L, R);
        NodeInfo rres = query(rch(u), mid(l, r) + 1, r, L, R);
        NodeInfo res = NodeInfo(l, r, lres, rres);
        return res;
    }

   public:
    void build(int n, typename NodeInfo::value_type* a = nullptr) {
        _n = n;
        _info.clear(), _info.resize(4 * (_n + 2));
        _tag.clear(), _tag.resize(4 * (_n + 2));
        build(1, 1, _n, a);
    }

    void update(int L, int R, const NodeTag& upd_tag) { update(1, 1, _n, L, R, upd_tag); }

    NodeInfo query(int L, int R) { return query(1, 1, _n, L, R); }
};

using NodeInfoSum = NodeInfoPolicy<true, false, false>;
using NodeInfoSumMinMax = NodeInfoPolicy<true, true, true>;

SegmentTree<NodeTagAdd, NodeInfoSumMinMax> st;

int n, m;
ll a[MAXN];

void purin_solve() {
    RD(n, m);
    RDN(a, n);
    st.build(n);
    for (int i = 1; i <= n; ++i) {
        st.update(i, i, a[i]);
    }
    while (m--) {
        int opt;
        RD(opt);
        if (opt == 1) {
            int l, r;
            ll k;
            RD(l, r, k);
            st.update(l, r, k);
        } else if (opt == 2) {
            int l, r;
            RD(l, r);
            ll res = st.query(l, r)._sum;
            WT(res);
        }
    }
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
