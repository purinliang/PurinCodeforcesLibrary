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
 * NonRotatingTreap
 *
 * The elements are automatically sorted (just like std::multi_set).
 *
 * This data-structure supports a small part of the interval operations, like
 * range_sum, range_max, range_min. Other interval operations, like range_add,
 * range_set and RANGE_REVERSE are not supported.
 */
struct NonRotatingTreap2 {
   private:
    static const int DEFAULT_CAPACITY = 3e5 + 10;
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

    struct Node {
        int lch = 0, rch = 0, rnd = 0;
        ll val = 0LL, siz = 0LL, sum = 0LL;
        // ll min = LINF, max = -LINF;

        Node() {}

        Node(ll _val) {
            rnd = rand();
            val = _val, siz = 1LL, sum = _val;
            // min = _val, max = _val;
        }

        string to_string(int u) {
            return std::to_string(val);
            string res = "{";
            // res += "u = " + std::to_string(u) + ", ";
            res += "val = " + std::to_string(val) + ", ";
            res += "sum = " + std::to_string(sum) + ", ";
            // res += "min = " + std::to_string(min) + ", ";
            // res += "max = " + std::to_string(max) + ", ";
            res = res.substr(0, std::max(0, (int)res.length() - 2)) + "}";
            return res;
        }
    };

    int root;
    vector<Node> node;

    void PushUp(int u) {
        node[u].siz = node[node[u].lch].siz + 1 + node[node[u].rch].siz;
        node[u].sum =
            node[node[u].lch].sum + node[u].val + node[node[u].rch].sum;
        // node[u].min = std::min({node[node[u].lch].min, node[u].val,
        // node[node[u].rch].min}); node[u].max =
        // std::max({node[node[u].lch].max, node[u].val,
        // node[node[u].rch].max});
    }

    int NewNode(ll _val) {
        int u = node.size();
        node.push_back(Node(_val));
        return u;
    }

    void SplitRank(int u, int _rnk, int& x, int& y) {
        if (!u) {
            x = 0, y = 0;
            return;
        }
        if (_rnk <= node[node[u].lch].siz) {
            y = u;
            SplitRank(node[u].lch, _rnk, x, node[u].lch);
            PushUp(y);
        } else {
            x = u;
            SplitRank(node[u].rch, _rnk - node[node[u].lch].siz - 1,
                      node[u].rch, y);
            PushUp(x);
        }
    }

    int Merge(int x, int y) {
        if (!x || !y) {
            return x | y;
        }
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

    string compressed_to_string(int u) {
        if (!u) {
            return "";
        }
        string m_res = node[u].to_string(u);
        string l_res =
            node[u].lch ? (compressed_to_string(node[u].lch) + ", ") : "";
        string r_res =
            node[u].rch ? (", " + compressed_to_string(node[u].rch)) : "";
        return l_res + m_res + r_res;
    }

    string to_string(int u, int dep, string dir) {
        string m_prefix = string(dep * 4, ' ') + dir;
        string m_res = u ? (node[u].to_string(u) + "\n") : "";
        string l_res = node[u].lch ? to_string(node[u].lch, dep + 1, "/ ") : "";
        string r_res =
            node[u].rch ? to_string(node[u].rch, dep + 1, "\\ ") : "";
        return l_res + m_prefix + m_res + r_res;
    }

    void show(int lroot, int mroot, int rroot) {
#ifdef LOCAL
        string res = "NonRotatingTreap = [";
        res += compressed_to_string(lroot) + "]";
        res += ", [" + compressed_to_string(mroot) + "]";
        res += ", [" + compressed_to_string(rroot) + "]";
        cout << res << endl;
#endif
    }

   public:
    NonRotatingTreap2() {
        Init();
    }

    void Init(int capacity = DEFAULT_CAPACITY) {
        if (capacity + 2 > node.capacity()) {
            node.reserve(capacity + 2);
        }
        root = 0;
        node.clear();
        node.push_back(Node());
    }

    void Insert(int val) {
        if (node.size() == node.capacity()) {
            node.reserve(2 * node.capacity());
        }
        int rnk = Size() - CountGreaterThan(val) + 1;
        int L = 0, M = 0, R = 0;
        SplitRank(root, rnk - 1, L, R);
        M = NewNode(val);
        root = Merge(Merge(L, M), R);
    }

    void Remove(int val) {
        int count_less_than = CountLessThan(val);
        int count_greater_than = CountGreaterThan(val);
        int count_equal_to = Size() - count_less_than - count_greater_than;
        if (count_equal_to > 0) {
            int rnk = count_less_than + 1;
            int L = 0, M = 0, R = 0;
            SplitRank(root, rnk - 1, L, R);
            SplitRank(R, 1, M, R);
            // M is removed
            root = Merge(L, R);
        }
    }

    int CountLessThan(ll val) {
        return CountLessThan(root, val);
    }

    int CountGreaterThan(ll val) {
        return CountGreaterThan(root, val);
    }

    int Size() {
        return node[root].siz;
    }

    int Rank(ll val) {
        return CountLessThan(val) + 1;
    }

    ll Value(int rnk) {
        int L = 0, M = 0, R = 0;
        SplitRank(root, rnk - 1, L, R);
        SplitRank(R, 1, M, R);
        ll res = node[M].val;
        root = Merge(Merge(L, M), R);
        return res;
    }

    ll Prev(ll val) {
        int rnk = CountLessThan(val);
        if (rnk <= 0) {
            return -LINF;
        }
        return Value(rnk);
    }

    ll Next(ll val) {
        int rnk = Size() - CountGreaterThan(val) + 1;
        if (rnk > Size()) {
            return LINF;
        }
        return Value(rnk);
    }

    ll SumBetweenRank(int lrnk, int rrnk) {
        int L = 0, M = 0, R = 0;
        SplitRank(root, lrnk - 1, L, R);
        SplitRank(R, rrnk - lrnk + 1, M, R);
        show(L, M, R);
        ll res = node[M].sum;
        root = Merge(Merge(L, M), R);
        return res;
    }

    ll SumBetweenValue(ll lval, ll rval) {
        int lrnk = CountLessThan(lval) + 1;
        int rrnk = Size() - CountGreaterThan(rval) + 1;
        return SumBetweenRank(lrnk, rrnk);
    }

    string to_string(int u) {
        return "NonRotatingTreap = [\n" + to_string(u, 1, "") + "]";
    }

    void show() {
#ifdef LOCAL
        cout << to_string(root) << endl;
#endif
    }

} tree;

int n;

void purin_solve() {
    RD(n);
    tree.Init();
    while (n--) {
        int opt, x;
        RD(opt, x);
        if (opt == 1) {
            tree.Insert(x);
        } else if (opt == 2) {
            tree.Remove(x);
        } else if (opt == 3) {
            ll res = tree.Rank(x);
            WT(res);
        } else if (opt == 4) {
            ll res = tree.Value(x);
            WT(res);
        } else if (opt == 5) {
            ll res = tree.Prev(x);
            WT(res);
        } else if (opt == 6) {
            ll res = tree.Next(x);
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
