#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
   private:
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
    static const ll INF = 0x3F3F3F3F;

    struct Node {
        int l = INF, r = -INF;
        ll add_tag = 0LL;
        // pair<bool, ll> set_tag = {false, 0LL};
        ll sum = 0LL;
        // ll min = LINF;
        // ll max = -LINF;

        Node() {
        }

        Node(int _l, int _r, ll _val) {
            l = _l, r = _r;
            add_tag = 0LL;
            // set_tag = {false, 0LL};
            sum = _val;
            // min = _val;
            // max = _val;
        }

        string to_string() {
            return std::to_string(sum);
            string res = "";
            res += "[" + std::to_string(l) + ", " + std::to_string(r) + "] ";
            res += "sum = " + std::to_string(sum) + ", ";
            // res += "min = " + std::to_string(min) + ", ";
            // res += "max = " + std::to_string(max) + ", ";
            res = res.substr(0, std::max(0, (int)res.length() - 2));
            return res;
        }

        void Add(ll val) {
            add_tag += val;
            sum += 1LL * (r - l + 1) * val;
            // min += val;
            // max += val;
        }

        // void Set(ll val) {
        //     set_tag = {true, val};
        //     sum = 1LL * (r - l + 1) * val;
        //     min = val;
        //     max = val;
        // }

        void Merge(Node& lch_node, Node& rch_node) {
            l = std::min(lch_node.l, rch_node.l);
            r = std::max(lch_node.r, rch_node.r);
            sum = lch_node.sum + rch_node.sum;
            // min = std::min(lch_node.min, rch_node.min);
            // max = std::max(lch_node.max, rch_node.max);
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

    // ll Min(int L, int R) {
    //     return Query(L, R).min;
    // }

    // ll Max(int L, int R) {
    //     return Query(L, R).max;
    // }

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

} st;
