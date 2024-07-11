#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct AhoCorasickAutomatonSimpleVersion {
    struct Node {
        int ch[26], fail;
        vector<int> fail_ch;

        // Extended data:
        // 在文本串中，当前节点被遍历的次数，也是当前节点作为最长真后缀的
        // 出现次数，在 dp_on_fail_tree 之后，为当前节点的出现次数
        ll cnt;
    };

    int root;
    vector<Node> node;

    // Extended data:
    vector<pair<int, int>> pattern_id_to_node_id;

    void init() {
        node.clear();
        root = new_node();  // root == 0

        // Maintain extended data:
        pattern_id_to_node_id.clear();
    }

    int new_node() {
        int idx = node.size();
        node.push_back(Node());
        return idx;
    }

    void insert(char* s, int id) {
        int u = root;
        for (int i = 1; s[i]; ++i) {
            if (!node[u].ch[s[i] - 'a']) {
                node[u].ch[s[i] - 'a'] = new_node();
            }
            u = node[u].ch[s[i] - 'a'];
        }

        // Maintain extended data:
        pattern_id_to_node_id.push_back({id, u});
    }

    void build() {
        queue<int> que;
        que.push(root);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i = 0; i < 26; ++i) {
                int& next = node[u].ch[i];
                if (u == root) {
                    if (next) {
                        que.push(next);
                    }
                    continue;
                }
                if (next) {
                    node[next].fail = node[node[u].fail].ch[i];
                    que.push(next);
                } else {
                    next = node[node[u].fail].ch[i];
                }
            }
        }
    }

    void build_fail_tree() {
        for (int i = 1; i < node.size(); ++i) {
            int fail_parent = node[i].fail;
            node[fail_parent].fail_ch.push_back(i);
        }
        dp_on_fail_tree(root);
    }

    void dp_on_fail_tree(int u) {
        for (auto& v : node[u].fail_ch) {
            dp_on_fail_tree(v);
            node[u].cnt += node[v].cnt;
        }
    }

    void query(char* t) {
        int u = root;
        for (int i = 1; t[i]; ++i) {
            u = node[u].ch[t[i] - 'a'];
            ++node[u].cnt;
        }
    }

    /**
     * 查询每种模式串 S_id 在文本串 T 中是否出现
     */
    void answer(char* t) {
        query(t);
        dp_on_fail_tree(root);

        int ans = 0;
        for (auto [id, u] : pattern_id_to_node_id) {
            if (node[u].cnt) {
                ++ans;
            }
        }
        cout << ans << endl;

        for (int i = 0; i < node.size(); ++i) {
            // 清空本次查询的影响，注意 dp_on_fail_tree 污染了其他节点
            node[i].cnt = 0;
        }
    }

} acamsv;

struct AhoCorasickAutomaton {
    struct Node {
        int ch[26], fail;
        vector<int> fail_ch;

        // Extended data:
        // 在文本串中，当前节点被遍历的次数，也是当前节点作为最长真后缀的
        // 出现次数，在 dp_on_fail_tree 之后，为当前节点的出现次数
        ll cnt;
    };

    int root;
    vector<Node> node;

    // Extended data:
    vector<pair<int, int>> pattern_id_to_node_id;

    void init() {
        node.clear();
        root = new_node();  // root == 0

        // Maintain extended data:
        pattern_id_to_node_id.clear();
    }

    int new_node() {
        int idx = node.size();
        node.push_back(Node());
        return idx;
    }

    void insert(char* s, int id) {
        int u = root;
        for (int i = 1; s[i]; ++i) {
            if (!node[u].ch[s[i] - 'a']) {
                node[u].ch[s[i] - 'a'] = new_node();
            }
            u = node[u].ch[s[i] - 'a'];
        }

        // Maintain extended data:
        pattern_id_to_node_id.push_back({id, u});
    }

    void build() {
        queue<int> que;
        que.push(root);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i = 0; i < 26; ++i) {
                int& next = node[u].ch[i];
                if (u == root) {
                    if (next) {
                        que.push(next);
                    }
                    continue;
                }
                if (next) {
                    node[next].fail = node[node[u].fail].ch[i];
                    que.push(next);
                } else {
                    next = node[node[u].fail].ch[i];
                }
            }
        }
    }

    void build_fail_tree() {
        for (int i = 1; i < node.size(); ++i) {
            int fail_parent = node[i].fail;
            node[fail_parent].fail_ch.push_back(i);
        }
        dp_on_fail_tree(root);
    }

    void dp_on_fail_tree(int u) {
        for (auto& v : node[u].fail_ch) {
            dp_on_fail_tree(v);
            node[u].cnt += node[v].cnt;
        }
    }

    void query(char* t) {
        int u = root;
        for (int i = 1; t[i]; ++i) {
            u = node[u].ch[t[i] - 'a'];
            ++node[u].cnt;
        }
    }

    /**
     * 查询每种模式串 S_id 在文本串 T 中出现的次数
     */
    void answer(char* t) {
        query(t);
        dp_on_fail_tree(root);

        for (auto [id, u] : pattern_id_to_node_id) {
            cout << node[u].cnt << endl;
        }
        for (int i = 0; i < node.size(); ++i) {
            // 清空本次查询的影响，注意 dp_on_fail_tree 污染了其他节点
            node[i].cnt = 0;
        }
    }

} acam;
