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

void ModularIntegersTest() {
    const int TEST_COUNT = 1e3;
    for (int i = 1; i <= TEST_COUNT; ++i) {
        ll rng = 1LL * rand() * rand() % MOD;
        mint a = rng;
        ll b = rng;

        auto show_and_compare = [&]() {
            cout << "a = " << a.num << ", b = " << b << endl;
            assert(a.num == (b % MOD + MOD) % MOD);
        };

        rng = 1LL * rand() * rand() % MOD;
        a += rng, b += rng;
        show_and_compare();

        rng = 1LL * rand() * rand() % MOD;
        a -= rng, b -= rng;
        show_and_compare();

        rng = 1LL * rand() * rand() % MOD;
        a *= rng;
        b *= rng;
        show_and_compare();

        a = -a;
        b = -b;
        show_and_compare();

        b %= MOD;

        auto qpow = [&](ll x, ll n) {
            ll res = 1LL;
            for (; n > 0LL; n >>= 1) {
                if (n & 1LL) res = res * x % MOD;
                x = x * x % MOD;
            }
            return res;
        };
        a = a.inv();
        b = qpow(b, MOD - 2);
        show_and_compare();
    }
}

int main() {
    ModularIntegersTest();
    return 0;
}
