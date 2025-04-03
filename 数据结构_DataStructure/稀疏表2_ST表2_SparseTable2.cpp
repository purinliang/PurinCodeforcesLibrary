#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * SparseTable can maintain range query of min/max values,
 * bitwise_and (&), logical_and (&&) and gcd (__gcd), are also min values
 * bitwise_or (|), logical_and (||) and lcm (__lcm), are also max values
 *
 * sum (+) and xor_sum (^) are not supported.
 *
 * TODO: There is an O(n) init - O(1) query version
 */
struct SparseTable {
   private:
    static const int INF = 0x3F3F3F3F;
    static const ll LINF = 0x3F3F3F3F3F3F3F3F;

    int _n;
    vector<int> _log2;

    typedef int T;
    vector<vector<T>> _st1;
    function<T(T, T)> _op1 = [](T x, T y) -> T { return min(x, y); };
    T _op1_iden = INF;  // be careful!

    vector<vector<T>> _st2;
    function<T(T, T)> _op2 = [](T x, T y) -> T { return max(x, y); };
    T _op2_iden = -INF;  // be careful!

    void init_help(T* a, vector<vector<T>>& st, function<T(T, T)>& op) {
        st.clear(), st.resize(_n + 2);
        for (int i = 1; i <= _n; ++i) {
            st[i].resize(_log2[_n] + 1);
            st[i][0] = a[i];
        }
        for (int j = 1; j <= _log2[_n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= _n; ++i) {
                st[i][j] = op(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query_help(int l, int r, vector<vector<T>>& st, function<T(T, T)>& op,
                 T op_iden) {
        l = max(l, 1), r = min(r, _n);
        if (l > r) {
            return op_iden;
        }
        int s = _log2[r - l + 1];
        return op(st[l][s], st[r - (1 << s) + 1][s]);
    }

   public:
    void init(int n, T* a) {
        _n = n;
        _log2.clear(), _log2.resize(_n + 2);
        for (int i = 2; i <= _n; ++i) {
            _log2[i] = _log2[i >> 1] + 1;
        }
        // if you don't need which of the following one,
        // just delete the  only one following line!
        init_help(a, _st1, _op1);  // min
        init_help(a, _st2, _op2);  // max
    }

    /**
     * min[l, r]
     */
    T query1(int l, int r) {
        return query_help(l, r, _st1, _op1, _op1_iden);
    }

    /**
     * max[l, r]
     */
    T query2(int l, int r) {
        return query_help(l, r, _st2, _op2, _op2_iden);
    }

} st;
