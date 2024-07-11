#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
        if (next == 0) {
            next = new_node();
            node[u].ch[c - 'a'] = next;
            node[next].len = node[u].len + 2;
            node[next].fail = node[fail(node[u].fail)].ch[c - 'a'];
            // dep 表示 fail 树的高度，而非回文树的高度。 fail 树的高度
            // 表示子串数量。回文树的高度表示子串长度（的一半）、
            node[next].dep = node[node[next].fail].dep + 1;
        }
        lst = next;
        R.push_back(node[next].dep);  // 以新字符为结尾的回文子串的数量
    }

} pam;
