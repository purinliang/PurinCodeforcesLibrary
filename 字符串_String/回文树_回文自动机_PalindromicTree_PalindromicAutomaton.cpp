#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * 使用回文自动机，要清晰理解每个变量的含义：
 *
 * 回文自动机的节点：
 * len：当前节点代表的回文子串的长度。与后缀自动机用路径代表子串不同，回文自动机
 * 表示的子串一定是要从回文中心（even_root 或者 odd_root）也就是根节点往下走的
 * 路径。
 * fail：当前节点的最长回文真后缀由哪个节点表示。注意，fail 树上，后代节点的信息
 * 可以传递给祖先节点，但是反过来不行。（后代节点是长字符串，祖先节点是短字符串，
 * 长字符串出现则短字符串一定出现）
 * dep：当前节点在 fail 树上的深度，而不是在回文树上的深度（回文树上的深度为 len
 * 的一半）。在某些题目中会有用。一定要记住 fail 树才是各种自动机改动的核心。
 * cnt：当前节点作为最长回文真后缀的出现次数，每次 extend 之后要对当前节点加1。
 *
 * 回文自动机：
 * lst：最后一次 extend 操作之后，回文自动机停留在的状态。注意不是每次 extend 都
 * 会创建新的节点。
 * 第一个真实节点：第一个真实节点为2，因为0和1分别表示 even_root 和 odd_root。
 * 最后一个节点：末尾节点为 node.size() - 1，而不是 lst。
 * dp_on_fail_tree：当回文自动机构建完毕，可以通过倒序枚举节点（节点范围如上），
 * 把长字符串的信息依次逐级转移给短字符串。最常见的转移是从最长回文真后缀的出现次
 * 数，转移到出现次数。
 */

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
        int ch[26] = {}, len = 0, fail = 0;

        // Extended data
        int dep = 0;  // the depth of the node on the fail tree
    };

    vector<char> s;
    vector<Node> node;
    int lst;

    // Extended data
    vector<int> R;  // how many palindromic substrs that end with R

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
        // 显式调用默认构造函数才能自动初始化
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

            // Maintain extended data:
            // dep 表示 fail 树的高度，而非回文树的高度。 fail 树的高度
            // 表示子串数量。回文树的高度表示子串长度（的一半），回文子串
            // 的长度一般用 len 直接维护。
            node[next].dep = node[node[next].fail].dep + 1;
        }
        lst = next;

        // Maintain extended data:
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
        int ch[26] = {}, len = 0, fail = 0;

        // Extended Data
        /**
         * cnt:
         * before dp_on_fail_tree: how many times the substr occurs
         * as the longest_palinromix_suffix. (can be int)
         * after dp_on_fail_tree: how many times the substr occurs.
         * (should be long long)
         */
        ll cnt = 0LL;
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

            // Maintain extended data:
        }
        lst = next;

        // Maintain extended data:
        ++node[lst].cnt;
    }

    // Maintain extended data:
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
