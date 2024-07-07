#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace MoAlgorithm {

    struct Query {
        int l, r, id;
        ll ans = 0LL;
        Query() {}
        Query(int _l, int _r, int _id) {
            l = _l, r = _r, id = _id;
        }
    };

    int n;
    vector<Query> q;

    void init(int _n) {
        n = _n;
        q.clear();
    }

    void add_query(int l, int r) {
        q.push_back(Query(l, r, q.size() + 1));
    }

    /* Calc Answer */

    int l, r;
    ll ans;
    vector<int> cnt;

    ll sq(ll x) {
        return x * x;
    }

    void extend_left() {
        // ans -= sq(cnt[a[l]]);
        // ++cnt[a[l]];
        // ans += sq(cnt[a[l]]);
    }

    void extend_right() {
        // ans -= sq(cnt[a[r]]);
        // ++cnt[a[r]];
        // ans += sq(cnt[a[r]]);
    }

    void shrink_left() {
        // ans -= sq(cnt[a[l]]);
        // --cnt[a[l]];
        // ans += sq(cnt[a[l]]);
    }

    void shrink_right() {
        //     ans -= sq(cnt[a[r]]);
        //     --cnt[a[r]];
        //     ans += sq(cnt[a[r]]);
    }

    void calc_all_ans() {
        int sqrtn = ceil(sqrt(n));
        sort(q.begin(), q.end(), [&](Query& q1, Query& q2) {
            if (q1.l / sqrtn != q2.l / sqrtn) return q1.l < q2.l;
            return ((q1.l / sqrtn) & 1) ? (q1.r < q2.r) : (q1.r > q2.r);
        });

        l = 1, r = 0, ans = 0LL;
        // cnt.clear(), cnt.resize(k + 2);
        for (auto& [ql, qr, qid, qans] : q) {
            while (ql < l) {
                --l;
                extend_left();
            }
            while (qr > r) {
                ++r;
                extend_right();
            }
            while (ql > l) {
                shrink_left();
                ++l;
            }
            while (qr < r) {
                shrink_right();
                --r;
            }
            qans = ans;
        }
    }

    void show_all_ans() {
        sort(q.begin(), q.end(),
             [&](Query& q1, Query& q2) { return q1.id < q2.id; });
        for (int i = 0; i < q.size(); ++i) {
            cout << q[i].ans << endl;
        }
    }

}  // namespace MoAlgorithm
