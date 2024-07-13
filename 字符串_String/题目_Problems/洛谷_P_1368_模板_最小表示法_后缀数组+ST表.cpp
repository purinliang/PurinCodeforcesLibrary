#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef LOCAL
#include ".\标准本地调试_StandardLocalDebug.h"
#else
#define D(...)
#define DN(arr, n)
#define DF()
#define ASSERT(x)

template <typename T>
void _RD(T& var) {
    cin >> var;
}

void _RD(char* var) {
    string str;
    cin >> str;
    strcpy(var + 1, str.c_str());
}

void RD() {}

template <typename T, typename... U>
void RD(T& Head, U&... Tail) {
    _RD(Head);
    RD(Tail...);
}

template <typename T>
void RDN(T* arr, int n) {
    for (int i = 1; i <= n; ++i) {
        _RD(arr[i]);
    }
}

template <typename T>
void _WT(const T& var) {
    cout << var;
}

void _WT(const char* var) {
    cout << (var + 1);
}

void WT() {}

template <typename T, typename... U>
void WT(const T& Head, const U&... Tail) {
    _WT(Head);
    cout << (sizeof...(Tail) ? " " : "\n");
    WT(Tail...);
}

void WTY(bool var, bool capital = false) {
    if (capital) {
        cout << (var ? "YES" : "NO") << "\n";
    } else {
        cout << (var ? "Yes" : "No") << "\n";
    }
}

template <typename T>
void WTN(T* arr, int n) {
    for (int i = 1; i <= n; ++i) {
        _WT(arr[i]);
        cout << (i < n ? " " : "\n");
    }
}

#endif

void purin_ios() {
    cout << fixed << setprecision(12);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#define endl "\n"
#define fout fflush(stdout)
}

void purin_init();
void purin_solve();

void purin_online_test(bool ignore_test_case_count) {
    purin_ios();
    purin_init();
    if (!ignore_test_case_count) {
        int t = 1;
        cin >> t;
        for (int i = 1; i <= t; ++i) {
            purin_solve();
        }
    } else {
        auto cin_eof = [&]() -> bool {
            char ch;
            while (cin >> ch) {
                if (!isspace(ch)) {
                    cin.unget();
                    return false;
                }
            }
            return cin.eof();
        };
        while (!cin_eof()) {
            purin_solve();
        }
    }
}

/* MY CODE BEGIN */

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

const int MAXN = 1e6 + 10;
int n;
int a[MAXN];

namespace SuffixArray {

    int n;
    vector<int> sa, rk, height;

    struct SparseTable {
       private:
        int _n;
        vector<int> _log2;
        vector<vector<int>> _st;

       public:
        void init(vector<int>& a, int n) {
            _n = n;
            _log2.clear(), _log2.resize(_n + 2);
            for (int i = 2; i <= _n; ++i) {
                _log2[i] = _log2[i >> 1] + 1;
            }

            _st.clear(), _st.resize(_n + 2);
            for (int i = 1; i <= _n; ++i) {
                _st[i].resize(_log2[_n] + 1);
                _st[i][0] = a[i];
            }
            for (int j = 1; j <= _log2[_n]; ++j) {
                for (int i = 1; i + (1 << j) - 1 <= _n; ++i) {
                    _st[i][j] =
                        std::min(_st[i][j - 1], _st[i + (1 << (j - 1))][j - 1]);
                }
            }
        }

        int query_min(int l, int r) {
            int s = _log2[r - l + 1];
            return std::min(_st[l][s], _st[r - (1 << s) + 1][s]);
        }
    } st;

    void suffix_sort(int* s, int n) {
        const int SIGMA = MAXN;
        vector<int> cnt(max(n, SIGMA) + 2), rk2(n + 2);
        sa.clear(), sa.resize(n + 2);
        rk.clear(), rk.resize(n + 2);

        for (int i = 1; i <= n; ++i) {
            rk[i] = s[i];  // 第一关键字，可以在此处进行值域偏移
            rk2[i] = i;    // 第二关键字
        }
        auto radix_sort = [&](int m) {
            for (int i = 0; i <= m; ++i) cnt[i] = 0;
            for (int i = 1; i <= n; ++i) ++cnt[rk[i]];
            for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; --i) sa[cnt[rk[rk2[i]]]--] = rk2[i];
        };
        radix_sort(SIGMA);  // 第一次后缀排序，单个字符比较，相同字符排相同名次

        // 比较排名为 i 的后缀和排名为 j 的后缀，长度不超过 len 时，是否 i < j
        auto cmp = [&](int i, int j, int len) {
            if (rk2[sa[i]] == rk2[sa[j]]) {
                if (sa[i] + len <= n && sa[j] + len <= n) {
                    if (rk2[sa[i] + len] == rk2[sa[j] + len]) return true;
                }
            }
            return false;
        };
        for (int len = 1; len <= n; len <<= 1) {
            int lst_rk2 = 0;
            // 由于第 len 位不存在，所以下面枚举的 i 是已经排好序的
            for (int i = n - len + 1; i <= n; ++i) rk2[++lst_rk2] = i;
            for (int i = 1; i <= n; ++i) {
                if (sa[i] > len) rk2[++lst_rk2] = sa[i] - len;
            }
            radix_sort(n);  // lst_rk2 == n

            swap(rk2, rk);
            for (int i = 1, lst_rk = 0; i <= n; ++i) {
                if (i == 1 || !cmp(i - 1, i, len)) ++lst_rk;
                rk[sa[i]] = lst_rk;
            }
        }
        auto calc_height = [&]() {
            height.clear(), height.resize(n + 2);
            for (int i = 1, k = 0; i <= n; ++i) {
                if (rk[i] == 1) continue;  // 第一名的 height 为 0
                if (k > 0) --k;            // h[i] >= h[i - 1] + 1;
                int j = sa[rk[i] - 1];
                while (j + k <= n && i + k <= n && s[i + k] == s[j + k]) ++k;
                height[rk[i]] = k;  // h[i] = height[rk[i]];
            }
        };
        calc_height();
        st.init(height, n);
    }

    // 从 x位置开始 和 从y位置开始 的子串的 lcp 的长度
    int lcp(int x, int y) {  //
        x = rk[x], y = rk[y];
        if (x > y) {
            swap(x, y);
        }
        return st.query_min(x + 1, y);
    }

    // 比较子串 [l1, r1] 和子串 [l2, r2] 的大小
    int cmp_substr(int l1, int r1, int l2, int r2) {
        int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
        if (lcp(l1, l2) >= min(len1, len2)) {
            // 他们的最长公共前缀的长度超过需要比较的区间
            return len1 == len2 ? 0 : len1 < len2 ? -1 : 1;
        }
        return rk[l1] < rk[l2] ? -1 : 1;  // 否则返回他们的后缀排序名次
    }

}  // namespace SuffixArray

/**
 * 牢记两个数组的意义：
 * sa[i] 数组：排名为 i 的后缀的起始位置为 sa[i]
 * rk[i] 数组：以 i 为开头的后缀，在后缀排序中的名次为 rk[i]
 *
 * 恒等式： sa[rk[i]] == i, 且 sa[rk[i]] == i
 *
 * 也就是说：通过字符串的位置比较大小关系，用 rk 数组，通过字符串
 * 的大小
 *
 *
 * 最小循环表示：
 * 将字符串复制一遍拼在原串之后，求一次后缀数组。
 * 取所有 sa <= n 的位置（后缀的开始位置在原字符串长度以内），就是所有循环表示。
 * https://www.luogu.com.cn/problem/P1368
 *
 * 拥有height数组之后，可以O(1)比较两个子串，所以可以方便套用。
 */

void purin_init() {}

void purin_solve() {
    RD(n);
    RDN(a, n);
    for (int i = 1; i <= n; ++i) {
        a[n + i] = a[i];
    }
    SuffixArray::suffix_sort(a, 2 * n);
    int minl = 1, minr = n;
    for (int i = 2; i <= n; ++i) {
        int newl = i, newr = i + n - 1;
        if (SuffixArray::cmp_substr(minl, minr, newl, newr) > 0) {
            minl = newl, minr = newr;
        }
    }
    WTN(a - 1 + minl, n);
}

int main() {
    const bool ignore_test_case_count = true;
#ifdef LOCAL
    purin_local_test(ignore_test_case_count);
#else
    purin_online_test(ignore_test_case_count);
#endif
    return 0;
}
