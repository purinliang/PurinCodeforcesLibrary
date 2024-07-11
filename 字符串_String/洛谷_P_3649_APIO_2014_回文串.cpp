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

const int MAXN = 3e5 + 10;
int n;
char s[MAXN];

/**
 * 模版题：
 * https://www.luogu.com.cn/problem/P3649
 * 对每个回文子串，求 回文子串的出现次数 * 回文子串的长度 的最大值
 *
 * 对回文树上每次新增字符之后的新的 lst 节点进行计数，得到每个节点
 * 作为最长回文后缀时的出现次数。然后在 fail 树上进行 DAG 上的 DP，
 * 算出这个节点真正的出现次数。
 */
struct PalindromicAutomaton2 {
    struct Node {
        int ch[26] = {};
        int len, fail;
        /**
         * cnt:
         * before dp_on_fail_tree: how many times the substr occurs
         * as the longest_palinromix_suffix. (can be int)
         * after dp_on_fail_tree: how many times the substr occurs.
         * (should be long long)
         */
        ll cnt;
    };

    vector<char> s;
    vector<Node> node;
    int lst;

    void init() {
        s.clear(), s.push_back(0);
        node.clear();
        int even_root = new_node();  // even_root == 0;
        int odd_root = new_node();   // odd_root == 1;
        node[even_root].len = 0, node[even_root].fail = odd_root;
        node[odd_root].len = -1, node[odd_root].fail = even_root;
        lst = 0;
    }

    int new_node() {
        int nd_idx = node.size();
        node.push_back(Node());
        return nd_idx;
    }

    int slen() { return (int)s.size() - 1; }

    int fail(int u) {
        // 找到最长回文后缀
        while (s[slen() - node[u].len - 1] != s[slen()]) {
            u = node[u].fail;
        }
        return u;
    }

    void extend(char c) {
        s.push_back(c);
        int u = fail(lst), next = node[u].ch[c - 'a'];
        if (next == 0) {
            next = new_node();
            node[next].len = node[u].len + 2;
            node[next].fail = node[fail(node[u].fail)].ch[c - 'a'];
            // 这一行必须放在上一行之后否则会死循环
            node[u].ch[c - 'a'] = next;
        }
        lst = next;
        ++node[lst].cnt;
    }

    ll dp_on_fail_tree() {
        // 注意回文自动机的第一个真实节点的下标是2，最后一个节点的下标为
        // node.size() - 1 而不是 lst。因为 lst 是最后一次扩展新字符后
        // 停留的状态，未必是被新创建的状态。
        // 倒序枚举节点顺序即可按 DAG 进行 DP。因为新节点的 fail 指针一定
        // 指向旧节点。
        ll ans = 0LL;
        for (int i = node.size() - 1; i >= 2; --i) {
            node[node[i].fail].cnt += node[i].cnt;
            ll tans = 1LL * node[i].len * node[i].cnt;
            ans = max(ans, tans);
        }
        return ans;
    }

} pam2;

void purin_init() {}

void purin_solve() {
    RD(s);
    n = strlen(s + 1);
    pam2.init();
    for (int i = 1; i <= n; ++i) {
        pam2.extend(s[i]);
    }
    ll res = pam2.dp_on_fail_tree();
    WT(res);
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
