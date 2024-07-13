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

const int MAXN = 1.1e7 + 10;

char s[MAXN];

struct Manacher {
    // len[i] 表示所有满足 i == l + r 的子串[l, r]中的
    // 最大回文长度（最长回文串的长度的一半的上整）
    vector<int> len;

    // 字符串 s，1-index，首字符是 s[1] 的字符串；n 字符串长度
    void init(char* s, int n = -1) {
        if (n == -1) {
            n = strlen(s + 1);
        }
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
    int longest_palindrome_length(int i) {
        return 2 * len[i] - (i % 2 == 0);
    }

    // 所有满足 i == l + r 的子串 [l, r] 中的最长回文串的范围
    pair<int, int> longest_palindrome_range(int i) {
        int lmid = i / 2, rmid = i - lmid;
        int l = lmid - len[i] + 1, r = rmid + len[i] - 1;
        return {l, r};  // longest_palindrome_length(i) == r - l + 1
    }

    // 判断子串 [l, r] 是否为回文串
    bool is_palindrome(int l, int r) {
        return longest_palindrome_length(l + r) >= (r - l + 1);
    }

} manacher;

void purin_init() {}

void purin_solve() {
    RD(s);
    int n = strlen(s + 1);
    manacher.init(s, n);
    int ans = 0;
    for (int i = 1; i <= 2 * n; ++i) {
        ans = max(ans, manacher.longest_palindrome_length(i));
    }
    WT(ans);
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
