#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace MultiBinarySearch {

    struct Query {
        int id;
        int cnt;  // the parameter of the query
    };

    vector<Query> _vec_qry;
    vector<int> _ans;

    void init_query() {
        _vec_qry.clear();
    }

    void add_query(int cnt) {
        Query qry;
        qry.id = _vec_qry.size();
        qry.cnt = cnt;
        _vec_qry.push_back(qry);
    }

    int calc_cnt(int M) {  // when answer is M, calc the maximum cnt
        int cnt = 0;
        // implement it, ordinary, the complexity is O(n)
        return cnt;
    }

    void multi_bs(int L, int R, vector<Query>& vec_qry) {
        if (L > R || vec_qry.empty()) {
            return;
        }
        if (L == R) {
            // Just like normal binary search, if there is always an answer
            // between the interval [L, R], then this solution is OK.
            // Otherwise, you should check whether there is a valid answer
            // when L == R.
            for (Query& qry : vec_qry) {
                _ans[qry.id] = L;
            }
            return;
        }
        int M = (L + R + 1) >> 1;  // Just like normal binary search, the value
                                   // of mid rely on how L and R move
        int cnt_M = calc_cnt(M);   // when answer is M, calc the maximum cnt
        vector<Query> vec_qry_L, vec_qry_R;
        // In certain problem, the parameter of Query would change.
        for (auto& qry : vec_qry) {
            if (cnt_M < qry.cnt) {
                // cannot meet the reqirement of qry, to left
                // that is, R = M - 1
                vec_qry_L.push_back(qry);
            } else {
                // can meet the reqirement of qry, to right
                // that is, L = M
                vec_qry_R.push_back(qry);
            }
        }
        multi_bs(L, M - 1, vec_qry_L);
        multi_bs(M, R, vec_qry_R);
        return;
    }

    void calc_all_ans(int L, int R) {
        _ans.clear(), _ans.resize(_vec_qry.size());
        multi_bs(L, R, _vec_qry);
    }

    void show_all_ans() {
        for (int i = 0; i < _ans.size(); ++i) {
            cout << _ans[i] << " ";
        }
        cout << endl;
    }

};  // namespace MultiBinarySearch

using namespace MultiBinarySearch;

/**
 * Check Link:
 *
 * https://codeforces.com/contest/1968/problem/G2
 * Cannot fully pass this problem, but can use for checking
 *
 */
