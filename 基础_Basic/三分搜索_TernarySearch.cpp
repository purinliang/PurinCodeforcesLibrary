#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct TernarySearch {
    static double ternary_search(double l, double r, function<double(double)> f) {
        const double EPS = 1e-10, STEP = 10.0;
        while (l + EPS < r) {
            double m1 = (l + r) / 2.0 - (r - l) / STEP;
            double m2 = (l + r) / 2.0 + (r - l) / STEP;
            // 如果 f 是上凸/先增后减函数，寻找“最靠左的”最大值，则为 < 号
            // 如果 f 是下凸/先减后增函数，寻找“最靠左的”最小值，则为 > 号
            // 如果要改成“最靠右的”最值，添加 = 号
            if (f(m1) > f(m2)) {
                l = m1;
            } else {
                r = m2;
            }
        }
        return l;
    }

    // TODO
    static ll ternary_search(ll l, ll r, function<ll(ll)> f) {
        while (l < r) {
            ll m1 = (l + r) >> 1;  // 由于可能是负数，所以用右移，向负无穷取整
            ll m2 = m1 + 1;        // l <= m1 < m2 <= r 恒成立
            // 如果 f 是上凸/先增后减函数，寻找“最靠左的”最大值，则为 < 号
            // 如果 f 是下凸/先减后增函数，寻找“最靠左的”最小值，则为 > 号
            // 如果要改成“最靠右的”最值，添加 = 号
            if (f(m1) > f(m2)) {
                l = m1 + 1;
            } else {
                r = m2 - 1;
            }
        }
        return l;
    }
};

/**
 * cout << fixed << setprecision(4);
 * cout << l << " " << r << endl;
 */
