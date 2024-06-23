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

struct EulerSieveMinPrime : public BaseSieve {
    vector<int> min_p, min_p_k;

    string to_string(int lim) {
        string p_str = "p = [";
        for (int j = 1; j < p.size() && j <= lim; ++j) {
            p_str += std::to_string(p[j]) + ", ";
        }
        p_str = p_str.substr(0, max(0, (int)p_str.length() - 2)) + "]";
        // return p_str;
        string min_p_str = "min_p = [";
        for (int j = 1; j <= lim; ++j) {
            min_p_str += std::to_string(min_p[j]) + ", ";
        }
        min_p_str = min_p_str.substr(0, max(0, (int)min_p_str.length() - 2)) + "]";
        string min_p_k_str = "min_p_k = [";
        for (int j = 1; j <= lim; ++j) {
            min_p_k_str += std::to_string(min_p_k[j]) + ", ";
        }
        min_p_k_str = min_p_k_str.substr(0, max(0, (int)min_p_k_str.length() - 2)) + "]";
        return p_str + ",\n" + min_p_str + ",\n" + min_p_k_str;
    }

    void init(int n) {
        p.clear();
        min_p.clear(), min_p.resize(n + 2);
        min_p_k.clear(), min_p_k.resize(n + 2);
        for (int i = 1; i <= n; ++i) {
            if (min_p[i] == 0) {
                p.push_back(i);
                min_p[i] = i;
                min_p_k[i] = i;
            }
            for (int j = 1, t; j < p.size() && (t = i * p[j]) <= n; ++j) {
                min_p[t] = p[j];
                if (i % p[j] == 0) {
                    min_p_k[t] = min_p_k[i] * p[j];
                    break;
                } else {
                    min_p_k[t] = p[j];
                }
            }
        }

        show();
    }
};

struct EulerSieveNotPrime : public BaseSieve {
    vector<bool> not_p;

    void init(int n) {
        p.clear();
        not_p.clear(), not_p.resize(n + 2);
        for (int i = 1; i <= n; ++i) {
            if (not_p[i] == 0) {
                p.push_back(i);
            }
            for (int j = 1, t; j < p.size() && (t = i * p[j]) <= n; ++j) {
                not_p[t] = true;
                if (i % p[j] == 0) {
                    break;
                }
            }
        }

        show();
    }
};

EulerSieveNotPrime euler_sieve;
