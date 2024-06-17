#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* Treap */
struct Treap {
   public:
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
    static const int DEFAULT_NODE_CAPACITY = 2e5 + 10;

    struct Node {
        int ch[2] = {}, rnd = 0;
        ll val = 0LL, cnt = 0LL, siz = 0LL;
        ll sum = 0LL;
        ll min = LINF;
        ll max = -LINF;

        Node () {
        }

        Node (ll _val, ll _cnt) {
            rnd = rand ();
            val = _val, cnt = _cnt, siz = _cnt;
            sum = 1LL * _val * _cnt;
            min = _val;
            max = _val;
        }

        void Show (int u = -1) {
            const char INTENT[] = "  ";
            printf ("%s", INTENT);
            printf ("{");
            // printf ("u = %d, ", u);
            printf ("val = %lld, ", val);
            // printf ("lch = %d, rch = %d\n", ch[0], ch[1]);
            // printf ("cnt = %lld, siz = %lld, ", cnt, siz);
            printf ("sum = %lld, ", sum);
            // printf ("min = %lld, max = %lld, ", min, max);
            printf ("\b\b}\n");
        }
    };

   private:
    int root;
    vector<Node> node;

#define lch node[u].ch[0]
#define rch node[u].ch[1]
#define dch node[u].ch[d]
#define tch node[u].ch[d ^ 1]

    void PushUp (int u) {
        node[u].siz = node[lch].siz + node[u].cnt + node[rch].siz;
        node[u].sum = node[lch].sum + (1LL * node[u].val * node[u].cnt) + node[rch].sum;
        node[u].min = min ({node[lch].min, node[u].val, node[rch].min});
        node[u].max = max ({node[lch].max, node[u].val, node[rch].max});
    }

    int NewNode (ll _val, ll _cnt) {
        int u = node.size ();
        node.push_back (Node (_val, _cnt));
        return u;
    }

    void Rotate (int &u, int d) {
        int t = tch;
        tch = node[t].ch[d], node[t].ch[d] = u, u = t;
        PushUp (dch), PushUp (u);
    }

    void InsertHelp (int &u, ll _val, ll _cnt) {
        if (!u) {
            u = NewNode (_val, _cnt);
            return;
        } else if (node[u].val == _val) {
            node[u].cnt += _cnt;
        } else {
            int d = node[u].val < _val;
            InsertHelp (dch, _val, _cnt);
            if (node[u].rnd < node[dch].rnd) {
                Rotate (u, d ^ 1);
            }
        }
        PushUp (u);
    }

    void RemoveHelp (int &u, ll _val, ll _cnt) {
        if (!u) {
            return;
        } else if (node[u].val == _val) {
            if (node[u].cnt > _cnt) {
                node[u].cnt -= _cnt;
            } else if (lch || rch) {
                int d = (!rch || node[lch].rnd > node[rch].rnd);
                Rotate (u, d), RemoveHelp (dch, _val, _cnt);
            } else {
                u = 0;
                return;
            }
        } else {
            int d = node[u].val < _val;
            RemoveHelp (dch, _val, _cnt);
        }
        PushUp (u);
    }

    ll GetRankHelp (int u, ll _val) {
        if (!u) {
            return 0LL;
        } else if (node[u].val == _val) {
            return node[lch].siz;
        } else if (node[u].val > _val) {
            return GetRankHelp (lch, _val);
        } else {
            return node[lch].siz + node[u].cnt + GetRankHelp (rch, _val);
        }
    }

    ll GetValueHelp (int u, ll _rnk) {
        if (!u) {
            return LINF;
        } else if (node[lch].siz < _rnk && (node[u].siz - node[rch].siz) >= _rnk) {
            return node[u].val;
        } else if (node[lch].siz >= _rnk) {
            return GetValueHelp (lch, _rnk);
        } else {
            return GetValueHelp (rch, _rnk - (node[u].siz - node[rch].siz));
        }
    }

    ll GetPrevHelp (int u, ll _val) {
        if (!u) {
            return -LINF;
        } else if (node[u].val < _val) {
            return max (node[u].val, GetPrevHelp (rch, _val));
        } else {
            return GetPrevHelp (lch, _val);
        }
    }

    ll GetNextHelp (int u, ll _val) {
        if (!u) {
            return LINF;
        } else if (node[u].val > _val) {
            return min (node[u].val, GetNextHelp (lch, _val));
        } else {
            return GetNextHelp (rch, _val);
        }
    }

    ll GetSumValueHelp (int u, ll _val) {
        if (!u) {
            return 0LL;
        } else if (node[u].val == _val) {
            return (node[u].sum - node[rch].sum);
        } else if (node[u].val > _val) {
            return GetSumValueHelp (lch, _val);
        } else {
            return (node[u].sum - node[rch].sum) + GetSumValueHelp (rch, _val);
        }
    }

    ll GetSumRankHelp (int u, ll _rnk) {
        if (!u) {
            return 0LL;
        } else if (node[lch].siz < _rnk && (node[u].siz - node[rch].siz) >= _rnk) {
            return node[lch].sum + 1LL * node[u].val * (_rnk - node[lch].siz);
        } else if (node[lch].siz >= _rnk) {
            return GetSumRankHelp (lch, _rnk);
        } else {
            return (node[u].sum - node[rch].sum) + GetSumRankHelp (rch, _rnk - (node[u].siz - node[rch].siz));
        }
    }

    void ShowHelp (int u) {
        if (!u) {
            return;
        }
        ShowHelp (lch);
        node[u].Show (u);
        ShowHelp (rch);
    }

#undef lch
#undef rch
#undef dch
#undef tch

   public:
    Treap () {
        Init ();
    }

    void Init (int node_capacity = DEFAULT_NODE_CAPACITY) {
        if (node_capacity > node.capacity ()) {
            node.reserve (node_capacity);
        }
        root = 0;
        node.clear ();
        node.push_back (Node ());
    }

    void Insert (ll val, ll cnt = 1LL) {
        if (node.size () == node.capacity ()) {
            node.reserve (2 * node.capacity ());
        }
        InsertHelp (root, val, cnt);
    }

    void Remove (ll val, ll cnt = 1LL) {
        RemoveHelp (root, val, cnt);
    }

    ll GetRank (ll val) {
        return GetRankHelp (root, val) + 1LL;
    }

    ll GetValue (ll rnk) {
        return GetValueHelp (root, rnk);
    }

    ll GetPrev (ll v) {
        return GetPrevHelp (root, v);
    }

    ll GetNext (ll v) {
        return GetNextHelp (root, v);
    }

    ll GetSumValue (ll val) {
        return GetSumValueHelp (root, val);
    }

    ll GetSumRank (ll rnk) {
        return GetSumRankHelp (root, rnk);
    }

    void Show () {
        printf ("Treap = [\n");
        ShowHelp (root);
        printf ("]\n");
    }

} treap;
