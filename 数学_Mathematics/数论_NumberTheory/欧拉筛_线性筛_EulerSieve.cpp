#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace EulerSieveMinPrime {

vector<int> p, min_p, min_p_k;

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

void show() {
#ifdef LOCAL
    cout << "[D] " << to_string(20) << endl;
#endif
}

void euler_sieve(int n) {
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

}  // namespace EulerSieveMinPrime

namespace EulerSieveNotPrime {

vector<int> p;
vector<bool> not_p;

string to_string(int lim) {
    string res = "p = [";
    for (int j = 1; j < p.size() && j <= lim; ++j) {
        res += std::to_string(p[j]) + ", ";
    }
    res = res.substr(0, max(0, (int)res.length() - 2)) + "]";
    return res;
}

void show() {
#ifdef LOCAL
    cout << "[D] " << to_string(20) << endl;
#endif
}

void euler_sieve(int n) {
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
}  // namespace EulerSieveNotPrime
