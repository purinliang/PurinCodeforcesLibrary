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

void purin_init() {}

const int MAXN = 2e5 + 10;

int n, m;
int a[MAXN];

template <typename NodeInfo, typename NodeTag>
struct SegmentTree {
   private:
    int _n;
    vector<NodeInfo> _info;
    vector<NodeTag> _tag;

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

    void build(int u, int l, int r) {
        if (l == r) {
            _info[u] = NodeInfo(a[l]);
            _tag[u] = NodeTag();
            return;
        }
        build(lch(u), l, mid(l, r));
        build(rch(u), mid(l, r) + 1, r);
        pull_up(u, l, r);
    }

    void update(int u, int l, int r, int L, int R, const NodeTag& upd_tag) {
        if (L > R || L > r || R < l) {
            return;
        }
        if (L <= l && r <= R) {
            bool push_d_tag = _info[u].apply_tag(l, r, upd_tag);
            _tag[u].apply_tag(l, r, upd_tag);
            if (l < r && push_d_tag) {
                push_down(u, l, r);
                update(lch(u), l, mid(l, r), L, R, NodeTag());
                update(rch(u), mid(l, r) + 1, r, L, R, NodeTag());
                pull_up(u, l, r);
            }
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

    // string to_string(int u, int l, int r, int dep, const string& dir) {
    //     string m_prefix = string(dep * 4, ' ') + dir;
    //     string m_res = (l <= r) ? (_info[u].to_string() + "," + _tag[u].to_string() + "\n") : "";
    //     string l_res = (l < r) ? to_string(lch(u), l, mid(l, r), dep + 1, "/ ") : "";
    //     string r_res = (l < r) ? to_string(rch(u), mid(l, r) + 1, r, dep + 1, "\\ ") : "";
    //     return l_res + m_prefix + m_res + r_res;
    // }

    string to_string(int u, int l, int r, string prefix, bool is_lch) {
        if (l > r) {
            return "";
        }
        string m_prefix = prefix + (u != 1 ? ((is_lch ? "╭── " : "╰── ")) : "");
        string m_res = _info[u].to_string() + "," + _tag[u].to_string() + "\n";
        string l_res, r_res;
        if (l < r) {
            string l_prefix = prefix + ((u != 1) ? (is_lch ? "    " : "│   ") : "");
            string r_prefix = prefix + ((u != 1) ? (!is_lch ? "    " : "│   ") : "");
            l_res = to_string(lch(u), l, mid(l, r), l_prefix, true);
            r_res = to_string(rch(u), mid(l, r) + 1, r, r_prefix, false);
        }
        return l_res + m_prefix + m_res + r_res;
    }

   public:
    void build(int n) {
        _n = n;
        _info.clear(), _info.resize(4 * (_n + 2));
        _tag.clear(), _tag.resize(4 * (_n + 2));
        build(1, 1, _n);
    }

    void update(int L, int R, const NodeTag& upd_tag) { update(1, 1, _n, L, R, upd_tag); }

    NodeInfo query(int L, int R) { return query(1, 1, _n, L, R); }

    string to_string() { return "SegmentTree = [\n" + to_string(1, 1, _n, "", false) + "]"; }

    void show() {
#ifdef LOCAL
        cout << "[D] " << to_string() << endl;
#endif
    }
};

struct NodeTag {
    ll _add_tag = 0LL;
    NodeTag() {};
    static NodeTag add(ll val) {
        NodeTag tag;
        tag._add_tag = val;
        return tag;
    }
    void apply_tag(int l, int r, const NodeTag& tag) {
        if (tag._add_tag != 0LL) {
            _add_tag += tag._add_tag;
        }
    }
    string to_string() const { return std::to_string(_add_tag); }
};

struct NodeInfo {
    static const ll LINF = 0x3f3f3f3f3f3f3f3f;
    ll _sum = 0LL;
    ll _min = LINF;
    ll _cnt = 1LL;
    NodeInfo() {}
    NodeInfo(int x) {
        _sum = x;
        _cnt = 1;
        _min = x;
    }
    NodeInfo(int l, int r, const NodeInfo& lch, const NodeInfo& rch) {
        _sum = lch._sum + rch._sum;
        _cnt = lch._cnt + rch._cnt;
        _min = min({lch._min, rch._min});
    }
    bool apply_tag(int l, int r, const NodeTag& tag) {
        if (tag._add_tag != 0LL) {
            _sum += 1LL * _cnt * tag._add_tag;
            _min += 1LL * tag._add_tag;
        }
        if (_min <= 0LL) {
            if (l == r) {
                _sum = 0LL;
                _cnt = 0LL;
                _min = LINF;
                return false;
            }
            return true;
        }
        return false;
    }
    string to_string() const {
        return /*"_cnt=" + std::to_string(_cnt) +*/ "_min=" + std::to_string(_min);
    }
};

SegmentTree<NodeInfo, NodeTag> st;

void purin_solve() {
    RD(n, m);
    RDN(a, n);
    st.build(n);
    // WTN(a, n);
    // for (int i = 1; i <= n; ++i) {
    //     st.update(i, i, NodeTag::add(a[i]));
    //     ll res = st.query(1, n)._sum;
    //     // WT(res);
    // }
    st.show();
    while (m--) {
        int op, l, r;
        RD(op, l, r);
        if (op == 1) {
            int x;
            RD(x);
            st.update(l, r, NodeTag::add(x));
            st.show();
        } else {
            ll res = st.query(l, r)._sum;
            WT(res);
        }
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
