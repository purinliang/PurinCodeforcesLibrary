#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* MOD must be a prime. if not, don't use inv() */
const int MOD = 1e9 + 7;

struct Matrix {
    int n, m;
    vector<vector<int>> ma;

    Matrix(int _n = 0, int _m = 0) {
        init(_n, _m);
    }

    void init(int _n = 0, int _m = 0) {
        n = _n, m = _m;
        ma = vector<vector<int>>(n, vector<int>(m));
    }

    friend Matrix operator+(const Matrix& x, const Matrix& y) {
        assert(x.n == y.n && x.m == y.m);
        Matrix res(x.n, x.m);
        for (int i = 0; i < x.n; ++i) {
            for (int j = 0; j < x.m; ++j) {
                res.ma[i][j] = x.ma[i][j] + y.ma[i][j];
                if (res.ma[i][j] >= MOD) res.ma[i][j] -= MOD;
            }
        }
        return res;
    }

    friend Matrix operator-(const Matrix& x, const Matrix& y) {
        assert(x.n == y.n && x.m == y.m);
        Matrix res(x.n, x.m);
        for (int i = 0; i < x.n; ++i) {
            for (int j = 0; j < x.m; ++j) {
                res.ma[i][j] = x.ma[i][j] - y.ma[i][j];
                if (res.ma[i][j] < 0) res.ma[i][j] += MOD;
            }
        }
        return res;
    }

    friend Matrix operator*(const Matrix& x, const Matrix& y) {
        assert(x.m == y.n);
        Matrix res(x.n, y.m);
        for (int i = 0; i < x.n; ++i) {
            for (int t = 0; t < x.m; ++t) {
                for (int j = 0; j < y.m; ++j) {
                    res.ma[i][j] += 1LL * x.ma[i][t] * y.ma[t][j] % MOD;
                    if (res.ma[i][j] >= MOD) res.ma[i][j] -= MOD;
                }
            }
        }
        return res;
    }

    friend Matrix pow(const Matrix& x, ll n) {
        assert(x.n == x.m);
        Matrix res(x.n, x.m), cx = x;
        for (int i = 0; i < x.n; ++i) res.ma[i][i] = 1;
        for (Matrix cx = x; n; cx = cx * cx, n >>= 1) {
            if (n & 1) res = res * cx;
        }
        return res;
    }

    void show() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << (ll)(ma[i][j]) << " ";
            }
            cout << endl;
        }
    }
};
