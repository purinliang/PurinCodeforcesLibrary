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

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 3e5 + 10;

void purin_init() {}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * PersistentNonRotatingTreap2
 *
 * The elements are automatically sorted (just like std::multi_set).
 *
 * This data-structure supports a small part of the interval operations, like
 * range_sum, range_max, range_min. Other interval operations, like range_add,
 * range_set and RANGE_REVERSE are not supported.
 */
struct PersistentNonRotatingTreap2 {
   public:
    static const int DEFAULT_CAPACITY = 3e5 + 10;
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

    struct Node {
        int lch = 0, rch = 0, rnd = 0;
        bool rev_tag = false;
        ll val = 0LL, siz = 0LL, sum = 0LL;

        Node() {}

        Node(ll _val) {
            rnd = rand();
            val = _val, siz = 1LL, sum = _val;
        }
    };

    vector<int> root;
    vector<Node> node;

    void PushUp(int u) {
        node[u].siz = node[node[u].lch].siz + 1 + node[node[u].rch].siz;
        node[u].sum =
            node[node[u].lch].sum + node[u].val + node[node[u].rch].sum;
    }

    int NewNode(ll _val) {
        int u = node.size();
        node.push_back(Node(_val));
        return u;
    }

    int CloneNode(int clone_from) {
        int u = node.size();
        Node nd = node[clone_from];
        node.push_back(nd);
        return u;
    }

    int GetNewVersion() {
        int new_ver = root.size();
        root.push_back(0);
        return new_ver;
    }

    void PushDown(int u) {
        if (node[u].rev_tag) {
            swap(node[u].lch, node[u].rch);
            if (node[u].lch) {
                node[u].lch = CloneNode(node[u].lch);
                node[node[u].lch].rev_tag ^= true;
            }
            if (node[u].rch) {
                node[u].rch = CloneNode(node[u].rch);
                node[node[u].rch].rev_tag ^= true;
            }
            node[u].rev_tag = false;
        }
    }

    void SplitRank(int u, int _rnk, int& x, int& y) {
        if (!u) {
            x = 0, y = 0;
            return;
        }
        PushDown(u);
        if (_rnk <= node[node[u].lch].siz) {
            y = CloneNode(u);
            SplitRank(node[u].lch, _rnk, x, node[y].lch);
            PushUp(y);
        } else {
            x = CloneNode(u);
            SplitRank(node[u].rch, _rnk - node[node[u].lch].siz - 1,
                      node[x].rch, y);
            PushUp(x);
        }
    }

    int Merge(int x, int y) {
        if (!x || !y) {
            return x | y;
        }
        PushDown(x), PushDown(y);
        if (node[x].rnd < node[y].rnd) {
            node[x].rch = Merge(node[x].rch, y);
            PushUp(x);
            return x;
        } else {
            node[y].lch = Merge(x, node[y].lch);
            PushUp(y);
            return y;
        }
    }

    int CountLessThan(int u, ll _val) {
        if (!u) {
            return 0;
        } else if (node[u].val >= _val) {
            return CountLessThan(node[u].lch, _val);
        } else {
            return node[node[u].lch].siz + 1 + CountLessThan(node[u].rch, _val);
        }
    }

    int CountGreaterThan(int u, ll _val) {
        if (!u) {
            return 0;
        } else if (node[u].val <= _val) {
            return CountGreaterThan(node[u].rch, _val);
        } else {
            return CountGreaterThan(node[u].lch, _val) + 1 +
                   node[node[u].rch].siz;
        }
    }

    tuple<int, int, int> Split3(int ver, int lrnk, int rrnk) {
        int lroot = 0, mroot = 0, rroot = 0;
        SplitRank(root[ver], lrnk - 1, lroot, rroot);
        SplitRank(rroot, rrnk - lrnk + 1, mroot, rroot);
        return {lroot, mroot, rroot};
    }

    void Merge3(int ver, int lroot, int mroot, int rroot) {
        root[ver] = Merge(Merge(lroot, mroot), rroot);
    }

    void ReserveNodeVector() {
        const int SAFE_CAPACITY_MARGIN = 128;
        while (node.size() + SAFE_CAPACITY_MARGIN > node.capacity()) {
            node.reserve(4 * node.capacity());
        }
    }

   public:
    PersistentNonRotatingTreap2() { Init(); }

    void Init(int capacity = DEFAULT_CAPACITY) {
        root.reserve(capacity);
        node.reserve(capacity);
        ReserveNodeVector();
        root.clear();
        int new_ver = GetNewVersion();  // new_ver == 0;
        root[new_ver] = 0;
        node.clear();
        node.push_back(Node());
    }

    void Insert(int ver, ll val) {
        ReserveNodeVector();
        int idx = Size(ver) - CountGreaterThan(root[ver], val) + 1;
        auto [L, M, R] = Split3(ver, idx, idx - 1);
        M = NewNode(val);
        int new_ver = GetNewVersion();
        Merge3(new_ver, L, M, R);
    }

    void Remove(int ver, ll val) {
        int count_less_than = CountLessThan(root[ver], val);
        int count_greater_than = CountGreaterThan(root[ver], val);
        int count_equal_to = Size(ver) - count_less_than - count_greater_than;
        if (count_equal_to > 0) {
            int idx = count_less_than + 1;
            ReserveNodeVector();
            auto [L, M, R] = Split3(ver, idx, idx);
            M = 0;  // M is removed
            int new_ver = GetNewVersion();
            Merge3(new_ver, L, M, R);
        } else {
            int new_ver = GetNewVersion();
            root[new_ver] = root[ver];  // be careful
        }
    }

    int Size(int ver) { return node[root[ver]].siz; }

    ll Value(int ver, int idx) {
        ReserveNodeVector();
        auto [L, M, R] = Split3(ver, idx, idx);
        ll res = node[M].val;
        int new_ver = GetNewVersion();
        Merge3(new_ver, L, M, R);
        return res;
    }

    ll Prev(int ver, ll val) {
        int rnk = CountLessThan(root[ver], val);
        if (rnk <= 0) {
            int new_ver = GetNewVersion();
            root[new_ver] = root[ver];  // be careful
            return -(1LL << 31) + 1LL;
        }
        return Value(ver, rnk);
    }

    ll Next(int ver, ll val) {
        int rnk = Size(ver) - CountGreaterThan(root[ver], val) + 1;
        if (rnk > Size(ver)) {
            int new_ver = GetNewVersion();
            root[new_ver] = root[ver];  // be careful
            return (1LL << 31) - 1LL;
        }
        return Value(ver, rnk);
    }

    ll Rank(int ver, ll val) {
        int new_ver = GetNewVersion();
        root[new_ver] = root[ver];  // be careful
        return CountLessThan(root[ver], val) + 1;
    }

    ll SumBetweenRank(int ver, int lrnk, int rrnk) {
        ReserveNodeVector();
        auto [L, M, R] = Split3(ver, lrnk, rrnk);
        ll res = node[M].sum;
        int new_ver = GetNewVersion();
        Merge3(new_ver, L, M, R);
        return res;
    }

    ll SumBetweenValue(int ver, ll lval, ll rval) {
        int lrnk = CountLessThan(root[ver], lval) + 1;
        int rrnk = Size(ver) - CountGreaterThan(root[ver], rval) + 1;
        return SumBetweenRank(ver, lrnk, rrnk);
    }

} tree;

int n;

void purin_solve() {
    RD(n);
    tree.Init();
    int i = 0;
    while (n--) {
        ++i;
        int ver, opt, x;
        RD(ver, opt, x);
        if (opt == 1) {
            tree.Insert(ver, x);
        } else if (opt == 2) {
            tree.Remove(ver, x);
        } else if (opt == 3) {
            ll res = tree.Rank(ver, x);
            WT(res);
        } else if (opt == 4) {
            ll res = tree.Value(ver, x);
            WT(res);
        } else if (opt == 5) {
            ll res = tree.Prev(ver, x);
            WT(res);
        } else if (opt == 6) {
            ll res = tree.Next(ver, x);
            WT(res);
        } else {
            continue;
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
