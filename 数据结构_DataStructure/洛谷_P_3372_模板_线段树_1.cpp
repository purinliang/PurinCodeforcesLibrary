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
    cin >> (var + 1);
}

void RD() {
}

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

void WT() {
}

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
    // fflush(stdout);
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

void purin_init() {
}

struct SegmentTree {
    // #define USING_MIN_MAX
   private:
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
    static const ll INF = 0x3F3F3F3F;

    struct Node {
        int l = INF, r = -INF;
        ll add_tag = 0LL;
        // pair<bool, ll> set_tag = {false, 0LL};
        ll sum = 0LL;
#ifdef USING_MIN_MAX
        ll min = LINF;
        ll max = -LINF;
#endif

        Node() {
        }

        Node(int _l, int _r, ll _val) {
            l = _l, r = _r;
            add_tag = 0LL;
            // set_tag = {false, 0LL};
            sum = _val;
#ifdef USING_MIN_MAX
            min = _val;
            max = _val;
#endif
        }

        string to_string() {
            return std::to_string(sum);
            string res = "";
            res += "[" + std::to_string(l) + ", " + std::to_string(r) + "] ";
            res += "sum = " + std::to_string(sum) + ", ";
#ifdef USING_MIN_MAX
            res += "min = " + std::to_string(min) + ", ";
            res += "max = " + std::to_string(max) + ", ";
#endif
            res = res.substr(0, std::max(0, (int)res.length() - 2));
            return res;
        }

        void Add(ll val) {
            add_tag += val;
            sum += 1LL * (r - l + 1) * val;
#ifdef USING_MIN_MAX
            min += val;
            max += val;
#endif
        }

        //         void Set(ll val) {
        //             set_tag = {true, val};
        //             sum = 1LL * (r - l + 1) * val;
        // #ifdef USING_MIN_MAX
        //             min = val;
        //             max = val;
        // #endif
        //         }

        void Merge(Node& lch_node, Node& rch_node) {
            l = std::min(lch_node.l, rch_node.l);
            r = std::max(lch_node.r, rch_node.r);
            sum = lch_node.sum + rch_node.sum;
#ifdef USING_MIN_MAX
            min = std::min(lch_node.min, rch_node.min);
            max = std::max(lch_node.max, rch_node.max);
#endif
        }
    };

    int n;
    int* init_inta;
    ll* init_lla;
    vector<Node> node;

#define lch (u << 1)
#define rch (u << 1 | 1)
#define mid ((l + r) >> 1)

    void PushUp(int u) {
        node[u].Merge(node[lch], node[rch]);
    }

    void PushDown(int u) {
        if (node[u].add_tag != 0LL) {
            node[lch].Add(node[u].add_tag);
            node[rch].Add(node[u].add_tag);
            node[u].add_tag = 0LL;
        }
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            ll val = (init_inta ? init_inta[l] : (init_lla ? init_lla[l] : 0LL));
            node[u] = Node(l, r, val);
            return;
        }
        Build(lch, l, mid);
        Build(rch, mid + 1, r);
        PushUp(u);
    }

    void Add(int u, int l, int r, int L, int R, ll val) {
        if (L > R || L > r || R < l) {
            return;
        }
        if (L <= l && r <= R) {
            node[u].Add(val);
            return;
        }
        PushDown(u);
        Add(lch, l, mid, L, R, val);
        Add(rch, mid + 1, r, L, R, val);
        PushUp(u);
    }

    // void Set(int u, int l, int r, int L, int R, ll val) {
    //     if (L > R || L > r || R < l) {
    //         return;
    //     }
    //     if (L <= l && r <= R) {
    //         node[u].Set(val);
    //         return;
    //     }
    //     PushDown(u);
    //     Set(lch, l, mid, L, R, val);
    //     Set(rch, mid + 1, r, L, R, val);
    //     PushUp(u);
    // }

    Node Query(int u, int l, int r, int L, int R) {
        if (L > R || L > r || R < l) {
            return Node();
        }
        if (L <= l && r <= R) {
            return node[u];
        }
        PushDown(u);
        Node l_res = Query(lch, l, mid, L, R);
        Node r_res = Query(rch, mid + 1, r, L, R);
        Node res;
        res.Merge(l_res, r_res);
        return res;
    }

    string to_string(int u, int l, int r, int dep, int dir) {
        const int LEFT = 0, RIGHT = 1;
        string res = "";
        if (l < r) {
            res += to_string(lch, l, mid, dep + 1, LEFT);
        }
        string indent = "    ";
        for (int i = 1; i <= dep; ++i) {
            res += indent;
        }
        if (dir == LEFT) {
            res += "/ ";
        } else if (dir == RIGHT) {
            res += "\\ ";
        }
        res += node[u].to_string() + "\n";
        if (l < r) {
            res += to_string(rch, mid + 1, r, dep + 1, RIGHT);
        }
        return res;
    }

    void Init(int _n) {
        n = _n;
        node.clear();
        node.resize(4 * n);
        Build(1, 1, n);
    }

#undef lch
#undef rch
#undef mid

   public:
    void Build(int n) {
        init_inta = nullptr, init_lla = nullptr;
        Init(n);
    }
    void Build(int n, int* _init_inta) {
        init_inta = _init_inta, init_lla = nullptr;
        Init(n);
    }

    void Build(int _n, ll* _init_lla) {
        init_inta = nullptr, init_lla = _init_lla;
        Init(n);
    }

    void Add(int L, int R, ll val) {
        Add(1, 1, n, L, R, val);
    }

    // void Set(int L, int R, ll val) {
    //     Set(1, 1, n, L, R, val);
    // }

    Node Query(int L, int R) {
        return Query(1, 1, n, L, R);
    }

    ll Sum(int L, int R) {
        return Query(L, R).sum;
    }

#ifdef USING_MIN_MAX
    ll Min(int L, int R) {
        return Query(L, R).min;
    }

    ll Max(int L, int R) {
        return Query(L, R).max;
    }
#endif

    string to_string() {
        string res = "SegmentTree = [";
        res += "\n" + to_string(1, 1, n, 1, -1);
        res += "]";
        return res;
    }

    void show() {
#ifdef LOCAL
        cout << "[D] " << to_string() << endl;
#endif
    }

#undef USING_MIN_MAX

} st;

int n, m;
int a[MAXN];

void purin_solve() {
    RD(n, m);
    RDN(a, n);
    DN(a, n);
    st.Build(n, a);
    st.show();
    while (m--) {
        int opt;
        RD(opt);
        if (opt == 1) {
            int l, r, k;
            RD(l, r, k);
            st.Add(l, r, k);
            st.show();
        } else if (opt == 2) {
            int l, r;
            RD(l, r);
            ll res = st.Sum(l, r);
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
