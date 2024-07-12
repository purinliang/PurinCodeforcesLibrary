#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SuffixAutomaton {
    static const int DEFAULT_STRLEN = 1e6;
    struct Node {
        int len = 0, link = 0;
        int ch[26] = {};
        ll cnt = 0;
    };

    vector<Node> node;
    int root, last;  // last末尾节点的位置

    void init(int strlen = DEFAULT_STRLEN) {
        node.clear(), node.reserve(2 * strlen + 2);
        node.push_back(Node());
        root = new_node();
        last = root;
    }

    int new_node() {
        int idx = node.size();
        node.push_back(Node());
        return idx;
    }

    int clone_new_node(int clone_from) {
        int idx = new_node();
        node[idx].link = node[clone_from].link;
        memcpy(node[idx].ch, node[clone_from].ch, sizeof(node[clone_from].ch));
        return idx;
    }

    void extend(char ch) {
        int p = last, u = new_node();
        last = u;
        node[u] = Node();
        node[u].len = node[p].len + 1;
        node[u].cnt = 1LL;
        while (p > 0 && !node[p].ch[ch - 'a']) {
            node[p].ch[ch - 'a'] = u;
            p = node[p].link;
        }
        if (p == 0) {
            node[u].link = root;
            return;
        }
        int q = node[p].ch[ch - 'a'];
        if (node[p].len + 1 == node[q].len) {
            node[u].link = q;
            return;
        }
        int cq = clone_new_node(q);
        node[cq].len = node[p].len + 1;
        node[q].link = node[u].link = cq;
        while (p > 0 && node[p].ch[ch - 'a'] == q) {
            node[p].ch[ch - 'a'] = cq;
            p = node[p].link;
        }
    }

    void dp_on_link_tree() {
        int siz = node.size() - 1;
        vector<int> cnt_len(siz + 2), rk(siz + 2);
        for (int i = 1; i <= siz; ++i) ++cnt_len[node[i].len];
        for (int i = 1; i <= siz; ++i) cnt_len[i] += cnt_len[i - 1];
        for (int i = 1; i <= siz; ++i) rk[cnt_len[node[i].len]--] = i;
        for (int i = siz; i >= 1; --i) {
            int u = rk[i], v = node[u].link;
            node[v].cnt += node[u].cnt;
        }
    }

    ll answer1() {
        dp_on_link_tree();
        ll ans = 0LL;
        int siz = node.size() - 1;
        for (int i = 1; i <= siz; ++i) {
            if (node[i].cnt > 1LL) {
                ans = max(ans, 1LL * node[i].cnt * node[i].len);
            }
        }
        return ans;
    }

} sam;

// not recommanded when only lowercase latin letters
struct SuffixAutomaton2 {
    static const int DEFAULT_STRLEN = 1e6;
    struct Node {
        int len = 0, link = 0;
        map<char, int> ch;
        ll cnt = 0;
    };

    vector<Node> node;
    int root, last;  // last末尾节点的位置

    void init(int strlen = DEFAULT_STRLEN) {
        node.clear(), node.reserve(2 * strlen + 2);
        node.push_back(Node());
        root = new_node();
        last = root;
    }

    int new_node() {
        int idx = node.size();
        node.push_back(Node());
        return idx;
    }

    int clone_new_node(int clone_from) {
        int idx = new_node();
        node[idx].link = node[clone_from].link;
        node[idx].ch = node[clone_from].ch;
        return idx;
    }

    void extend(char ch) {
        int p = last, u = new_node();
        last = u;
        node[u] = Node();
        node[u].len = node[p].len + 1;
        node[u].cnt = 1LL;
        while (p > 0 && !node[p].ch.count(ch - 'a')) {
            node[p].ch[ch - 'a'] = u;
            p = node[p].link;
        }
        if (p == 0) {
            node[u].link = root;
            return;
        }
        int q = node[p].ch[ch - 'a'];
        if (node[p].len + 1 == node[q].len) {
            node[u].link = q;
            return;
        }
        int cq = clone_new_node(q);
        node[cq].len = node[p].len + 1;
        node[q].link = node[u].link = cq;
        while (p > 0 && node[p].ch.count(ch - 'a') &&
               node[p].ch[ch - 'a'] == q) {
            node[p].ch[ch - 'a'] = cq;
            p = node[p].link;
        }
    }

    void dp_on_link_tree() {
        int siz = node.size() - 1;
        vector<int> cnt_len(siz + 2), rk(siz + 2);
        for (int i = 1; i <= siz; ++i) ++cnt_len[node[i].len];
        for (int i = 1; i <= siz; ++i) cnt_len[i] += cnt_len[i - 1];
        for (int i = 1; i <= siz; ++i) rk[cnt_len[node[i].len]--] = i;
        for (int i = siz; i >= 1; --i) {
            int u = rk[i], v = node[u].link;
            node[v].cnt += node[u].cnt;
        }
    }

    ll answer1() {
        dp_on_link_tree();
        ll ans = 0LL;
        int siz = node.size() - 1;
        for (int i = 1; i <= siz; ++i) {
            if (node[i].cnt > 1LL) {
                ans = max(ans, 1LL * node[i].cnt * node[i].len);
            }
        }
        return ans;
    }

} sam2;
