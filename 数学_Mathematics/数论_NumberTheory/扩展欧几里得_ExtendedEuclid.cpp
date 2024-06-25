#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * ExGcd
 */
struct ExtendedEuclid {
   private:
    static ll ex_gcd(ll a, ll b, ll& x, ll& y) {
        if (b == 0) {
            x = 1, y = 0;
            return a;
        }
        ll d = ex_gcd(b, a % b, x, y), t;
        t = x, x = y, y = t - a / b * y;
        return d;
    }

   public:
    /**
     * solve ax + by == c
     *
     * if x0 < 0, there is not solution. otherwise, answer is the smallest x0 >= 0 and its
     * coressponding y0, all answers look like: x = x0 + k * dx, y = y0 + k * dy, dx > 0, dy > 0
     */
    static tuple<ll, ll, ll, ll> solve_ax_plus_by_equal_to_c(ll a, ll b, ll c) {
        ll x0 = 0, y0 = 0, dx = 0, dy = 0;
        ll d = ex_gcd(a, b, x0, y0), t = b / d;
        if (c % d != 0) {
            // no solution
            x0 = -1, y0 = -1, dx = -1, dy = -1;
            return {x0, y0, dx, dy};
        }
        // solution is: x = x + k * dx, y = y - k * dy
        x0 = ((x0 % t) * (c / d % t) % t + t) % t;
        y0 = (c - a * x0) / b, dx = t, dy = a / d;
        assert(dx > 0 && dy > 0);
        return {x0, y0, dx, dy};
    }

    /**
     * solve ax == r mod m, m may be not a prime.
     * ax == r mod m <==> ax + my == r
     *
     * if x0 < 0, there is not solution, otherwise, answer is the smallest x0 >= 0 and its
     * coressponding y0, all answers look like: x = x0 + k * dx, dx > 0
     */
    static tuple<ll, ll> solve_ax_equal_to_r_mod_m(ll a, ll r, ll m) {
        auto [x0, y0, dx, dy] = solve_ax_plus_by_equal_to_c(a, m, r);
        return {x0, dx};
    }

    /**
     * find inv of a, when mod is m, m may be not a prime
     * let x == inv(a), a * inv(a) == 1 mod m <==> ax == 1 mod m,
     *
     * if x0 < 0, there is not solution, otherwise, answer is the smallest x0 >= 0 and its
     * coressponding y0, all answers look like: x = x0 + k * dx, dx > 0
     */
    static tuple<ll, ll> inv(ll a, ll m) {
        auto [x0, dx] = solve_ax_equal_to_r_mod_m(a, 1, m);
        return {x0, dx};
    }
};
