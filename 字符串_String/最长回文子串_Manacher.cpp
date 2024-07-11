#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Manacher {
    // len[i] 表示所有满足 i == l + r 的子串[l, r]中的
    // 最大回文长度（最长回文串的长度的一半的上整）
    vector<int> len;

    // 字符串 s，1-index，首字符是 s[1] 的字符串；n 字符串长度
    void init(char* s, int n) {
        len.clear(), len.resize(2 * n + 2);
        // 最右回文串的位置为 [lm, rm]
        int lm = 0, rm = -1;
        for (int i = 2; i <= 2 * n; ++i) {
            int lmid = i / 2, rmid = i - lmid;
            if (rmid > rm) {
                // 突破最右回文串的边界，使用暴力算法
                len[i] = (i % 2 == 0);
            } else {
                // 未突破最右回文串的边界， j 和 i 在该串中对称
                int j = 2 * (lm + rm) - i;
                // 回文长度至少为 len[j] ，但回文长度不能突破该串
                len[i] = min(len[j], rm - rmid + 1);
            }
            while (1 <= lmid - len[i] && rmid + len[i] <= n &&
                   s[lmid - len[i]] == s[rmid + len[i]]) {
                ++len[i];
            }
            if (rmid + len[i] - 1 > rm) {
                lm = lmid - len[i] + 1;
                rm = rmid + len[i] - 1;
            }
        }
    }

    // 所有满足 i == l + r 的子串 [l, r] 中的最长回文串的长度
    int max_length_palindrome(int i) {
        return 2 * len[i] - (i % 2 == 0);
    }

    // 判断子串 [l, r] 是否为回文串
    bool is_palindrome(int l, int r) {
        return max_length_palindrome(l + r) >= (r - l + 1);
    }

} manacher;
