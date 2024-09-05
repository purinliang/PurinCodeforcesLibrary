#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* MOD must be a prime. if not, don't use inv() */
const int MOD = 1e9 + 7;

struct ModularInteger {
#define mint ModularInteger

    int num = 0;

    ll normalize(ll x) {
        if (x >= 0) {
            if (x < MOD) return x;
            if (x < 2 * MOD) return x - MOD;
            return x % MOD;
        } else {
            if (x >= -MOD) return x + MOD;
            return (x % MOD + MOD) % MOD;
        }
    }

    mint() {}

    template <typename T>
    mint(const T& x) {
        num = normalize(x);
    }

    friend mint operator+(const mint& x, const mint& y) {
        return mint(x.num + y.num);
    }
    friend mint operator-(const mint& x, const mint& y) {
        return mint(x.num - y.num);
    }
    friend mint operator*(const mint& x, const mint& y) {
        return mint(1LL * x.num * y.num);
    }
    friend mint operator/(const mint& x, const mint& y) {
        return x * y.inv();
    }
    friend bool operator==(const mint& x, const mint& y) {
        return x.num == y.num;
    }
    friend bool operator!=(const mint& x, const mint& y) {
        return x.num != y.num;
    }
    mint operator+() {
        return num;
    }
    mint operator-() {
        return -num;
    }
    mint& operator+=(const mint& x) {
        num = ((*this) + x).num;
        return *this;
    }
    mint& operator-=(const mint& x) {
        num = ((*this) - x).num;
        return *this;
    }
    mint& operator*=(const mint& x) {
        num = ((*this) * x).num;
        return *this;
    }
    mint& operator/=(const mint& x) {
        num = ((*this) / x).num;
        return *this;
    }
    mint pow(ll x) const {
        mint res(1), cur(num);
        for (; x; cur *= cur, x >>= 1)
            if (x & 1) res *= cur;
        return res;
    }
    mint inv() const {
        return pow(MOD - 2);
    }

    operator int() {
        return num;
    }

    operator ll() {
        return num;
    }

#undef mint
};

typedef ModularInteger mint;

struct Matrix {
    int n, m;
    vector<vector<mint>> ma;

    Matrix(int _n = 0, int _m = 0) {
        init(_n, _m);
    }

    void init(int _n = 0, int _m = 0) {
        n = _n, m = _m;
        ma = vector<vector<mint>>(n, vector<mint>(m));
    }

    friend Matrix operator+(const Matrix& x, const Matrix& y) {
        assert(x.n == y.n && x.m == y.m);
        Matrix res(x.n, x.m);
        for (int i = 0; i < x.n; ++i) {
            for (int j = 0; j < x.m; ++j) {
                res.ma[i][j] = x.ma[i][j] + y.ma[i][j];
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
                    res.ma[i][j] += x.ma[i][t] * y.ma[t][j];
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
