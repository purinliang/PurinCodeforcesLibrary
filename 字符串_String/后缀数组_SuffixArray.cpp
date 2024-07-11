#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

namespace SuffixArray {

    int n;
    vector<int> sa, rk, height;

    void suffix_sort(char* s) {
        const int SIGMA = CHAR_MAX;
        n = strlen(s + 1);
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

        // 比较排名为 i 的后缀和排名为 j 的后缀，在长度不超过 len 的前提下，
        // 谁更小？i 是否小于 j？
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
    }

    void calc_height(char* s) {
        height.clear(), height.resize(n + 2);
        for (int i = 1, k = 0; i <= n; ++i) {
            if (rk[i] == 1) continue;  // 第一名的 height 为 0
            if (k > 0) --k;            // h[i] >= h[i - 1] + 1;
            int j = sa[rk[i] - 1];
            while (j + k <= n && i + k <= n && s[i + k] == s[j + k]) ++k;
            height[rk[i]] = k;  // h[i] = height[rk[i]];
        }
    }

    /**
     * 未验证：后缀 sa[x] 和后缀 sa[y] 之间的 lcp 的长度
     */
    int lcp(int x, int y) {
        if (x > y) {
            swap(x, y);
        }
        int res = n - y + 1;
        for (int i = x + 1; i <= y; ++i) {
            res = min(res, height[i]);
        }
        return res;
    }

    /**
     * 未验证：比较子串 [l1, r1] 和子串 [l2, r2]
     */
    int cmp_substr(int l1, int r1, int l2, int r2) {
        int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
        if (lcp(l1, l2) >= min(len1, len2)) {
            // 他们的最长公共前缀的长度超过需要比较的区间
            return len1 < len2;
        }
        return rk[l1] < rk[l2];  // 否则返回他们的后缀排序名次
    }

    /**
     * 查找模式串 T 在文本串 S 中的所有匹配。前缀相同的子串在
     * 后缀排序名次中是连续的。也就是在 rk 数组中相邻的两个位置，从
     * 他们开始的后缀的前缀是字典序连续的。所以可以在上面二分，
     * 然后暴力比较模式串 T 的长度看看当前位置的字典序是偏大还是
     * 偏小，找到所有拥有与模式串 T 相等的前缀的区间 [lower_bound,
     * upper_bound)，然后他们的 sa 值就是他们的起始位置。
     */
    vector<int> get_all_occurences(char* s, char* t) {
        int sl = strlen(s + 1), tl = strlen(t + 1);
        suffix_sort(s);

        auto binary_search = [&](function<bool(int, int)> cmp) {
            int L = 1, R = sl;
            while (L < R) {
                int M = (L + R) >> 1;
                int strcmp_res = strncmp(s + sa[M], t + 1, tl);
                if (cmp(strcmp_res, 0)) {
                    R = M;
                } else {
                    L = M + 1;
                }
            }
            return L;
        };

        int lower_bound = binary_search(greater_equal<int>());
        int upper_bound = binary_search(greater<int>());

        vector<int> ans;
        for (int i = lower_bound; i < upper_bound; ++i) {
            ans.push_back(sa[i]);
        }
        sort(ans.begin(), ans.end());
        return ans;
    }

}  // namespace SuffixArray
