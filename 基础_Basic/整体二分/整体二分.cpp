#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace MultiBinarySearch {
    struct Query {
        int id;
        int l, r, k;  // the parameter of the query
    };

    vector<Query> _vec_qry;
    vector<int> _ans;

    void init_query(int q_cnt = 0) {
        _vec_qry.clear();
        _vec_qry.reserve(q_cnt);
    }

    void add_query(int l, int r, int k) {
        Query qry;
        qry.id = _vec_qry.size();
        qry.l = l;
        qry.r = r;
        qry.k = k;
        _vec_qry.push_back(qry);
    }

    void calc_k(int L, int M, int dir) {
        // for (int i = L; i <= M; ++i) {
        //     for (auto& p : pos[i]) {
        //         bit_add.add(p, dir);
        //     }
        // }
    }

    bool is_right_query(Query& qry) {
        // int k_M = bit_add.sum(qry.r) - bit_add.sum(qry.l - 1);
        // return qry.k > k_M;
    }

    int partition(int ql, int qr) {
        int i = ql, j = qr, qm;
        while (i < j) {
            for (; i < j && !is_right_query(_vec_qry[i]); ++i);
            for (; i < j && is_right_query(_vec_qry[j]); --j);
            if (i < j) {
                swap(_vec_qry[i], _vec_qry[j]);
                ++i, --j;
            }
        }
        for (qm = qr; qm >= ql && is_right_query(_vec_qry[qm]); --qm);
        return qm;
    }

    void multi_bs(int L, int R, int ql, int qr) {
        if (L > R || ql > qr) {
            return;
        }
        if (L == R) {
            for (int qi = ql; qi <= qr; ++qi) {
                Query& qry = _vec_qry[qi];
                _ans[qry.id] = L;
            }
            return;
        }
        int M = (L + R) >> 1;
        calc_k(L, M, 1);
        int qm = partition(ql, qr);
        for (int qi = qm + 1; qi <= qr; ++qi) {
            // int k_M =
            //     bit_add.sum(_vec_qry[qi].r) - bit_add.sum(_vec_qry[qi].l -
            //     1);
            _vec_qry[qi].k -= k_M;
        }
        calc_k(L, M, -1);
        multi_bs(L, M, ql, qm);
        multi_bs(M + 1, R, qm + 1, qr);
        return;
    }

    void calc_all_ans(int L, int R) {
        // bit_add.init(n);  // here is not len
        int cnt_q = _vec_qry.size();
        _ans.clear(), _ans.resize(cnt_q);
        multi_bs(L, R, 0, cnt_q - 1);
    }

    void show_all_ans() {
        // for (int i = 0; i < _ans.size(); ++i) {
        //     cout << idx[_ans[i]] << endl;
        // }
    }

};  // namespace MultiBinarySearch

using namespace MultiBinarySearch;
