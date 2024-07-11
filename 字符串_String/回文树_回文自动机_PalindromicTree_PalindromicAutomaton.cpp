#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 模版题：
 * https://www.luogu.com.cn/problem/P5496
 * 对每个位置，求 以其为右端点的回文子串的出现次数
 *
 * 回文子串的长度为 len，回文子串的最长回文真后缀为 fail，当一个节点被 extend
 * 之后被访问到，那么它作为最长回文子串出现次数加1，而它的各级 fail 父亲也应该
 * + 1。对于这个新字符的位置，它出现的总次数就是当前节点的 fail 树的高度，本题
 * 中选择额外用一个 R 数组存起来。dep 和 R 数组并非是回文自动机的一部分。
 */
struct PalindromicAutomaton {
    struct Node {
        int ch[26] = {};
        int len, fail, dep;
    };

    vector<char> s;
    vector<int> R;  // how many palindromic substrs that end with R
    vector<Node> node;
    int lst;

    void init() {
        s.clear(), s.push_back(0);
        R.clear(), R.push_back(0);
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

    int slen() {
        return (int)s.size() - 1;
    }

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
        if (!next) {
            next = new_node();
            node[next].len = node[u].len + 2;
            node[next].fail = node[fail(node[u].fail)].ch[c - 'a'];
            // 这一行必须放在上一行之后否则会死循环
            node[u].ch[c - 'a'] = next;
            // dep 表示 fail 树的高度，而非回文树的高度。 fail 树的高度
            // 表示子串数量。回文树的高度表示子串长度（的一半）。
            node[next].dep = node[node[next].fail].dep + 1;
        }
        lst = next;
        R.push_back(node[lst].dep);  // 以新字符为结尾的回文子串的数量
    }

    void show_R() {
        for (int i = 1; i <= slen(); ++i) {
            cout << R[i] << " ";
        }
        cout << endl;
    }

} pam;

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
         * as the longest_palinromix_suffix.
         * after dp_on_fail_tree: how many times the substr occurs.
         */
        int cnt;
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

    int slen() {
        return (int)s.size() - 1;
    }

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
        // 注意回文自动机的第一个真实节点的下标是2
        ll ans = 0LL;
        for (int i = lst; i >= 2; --i) {
            node[node[i].fail].cnt += node[i].cnt;
            ll tans = 1LL * node[i].len * node[i].cnt;
            ans = max(ans, tans);
        }
        return ans;
    }

} pam2;
