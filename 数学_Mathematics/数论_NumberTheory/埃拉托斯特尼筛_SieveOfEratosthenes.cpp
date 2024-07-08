#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct BaseSieve {
    vector<int> p;

    string to_string(int lim) {
        string res = "p = [";
        for (const auto& d : p) {
            if (d > lim) {
                break;
            }
            res += std::to_string(d) + ", ";
        }
        res = res.substr(0, max(0, (int)res.length() - 2)) + "]";
        return res;
    }

    void show() {
#ifdef LOCAL
        cout << "[D] " << to_string(20) << endl;
#endif
    }

    template <typename function>
    void calc_prime_divisor(ll x, bool skip_1, function f) {
        if (!skip_1) {
            f(1);
        }
        // Could be faster if preprocess minimal prime divisor of x
        for (const auto& d : p) {
            if (d * d > x) {
                break;
            }
            if (d == 1 || x % d != 0) {
                continue;
            }
            f(d);
            while (x % d == 0) {
                x /= d;
            }
        }
        if (x != 1) {
            f(x);
        }
    }

    template <typename function>
    void calc_any_divisor(ll x, bool skip_1, function f) {
        if (!skip_1) {
            f(1);
        }
        // Could be faster if preprocess all divisor of x
        for (ll d = 2; d * d <= x; ++d) {
            if (x % d != 0) {
                continue;
            }
            f(d);
            if (d * d != x) {
                f(x / d);
            }
        }
    }
};

// TODO 补充其他的数论函数
struct SieveOfEratosthenesNotPrime : public BaseSieve {
    vector<bool> not_p;

    void init(int n) {
        p.clear(), p.push_back(1);
        not_p.clear(), not_p.resize(n + 2);
        for (int i = 2; i <= n; ++i) {
            if (not_p[i] == false) {
                p.push_back(i);
                for (int j = 2 * i; j <= n; j += i) {
                    not_p[j] = true;
                }
            }
        }
    }
};

SieveOfEratosthenesNotPrime sieve;
