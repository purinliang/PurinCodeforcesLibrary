#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct AhoCorasickAutomaton {
    struct Node {
        int ch[26] = {}, fail = 0;
        vector<int> fail_ch;

        // Extended data:
        // 在文本串中，当前节点被遍历的次数，也是当前节点作为最长真后缀的
        // 出现次数，在 dp_on_fail_tree 之后，为当前节点的出现次数
        ll cnt = 0LL;
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
        // 显式调用默认构造函数才能自动初始化
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

    /**
     * 清除上一次访问对AC自动机的影响
     * 针对 query1 类型的影响，可以再次遍历文本串 T 将其清空。
     * 针对 query2 类型的影响，由于进行了 dp_on_fail_tree，
     * 所以要将所有相关节点清空，为了图方便直接整个自动机清空。
     */
    void clear_cnt() {
        for (int i = 0; i < node.size(); ++i) {
            // 清空上次查询的影响，注意 dp_on_fail_tree 污染了其他节点
            node[i].cnt = 0;
        }
    }

    /**
     * 将文本串 T 输入AC自动机，统计每个节点的访问次数。也就是
     * 每个节点作为最长真后缀的出现次数。
     */
    void query1(char* t) {
        int u = root;
        for (int i = 1; t[i]; ++i) {
            u = node[u].ch[t[i] - 'a'];
            ++node[u].cnt;
        }
    }

    /**
     * 将文本串 T 输入AC自动机，统计每个节点的出现次数。也就是
     * 每个节点作为子串的出现次数。
     */
    void query2(char* t) {
        query1(t);
        dp_on_fail_tree(root);
    }

    /**
     * 查询并输出一共有多少种模式串 S_id 在文本串 T 中出现
     */
    void answer1(char* t) {
        query2(t);

        int ans = 0;
        for (auto [id, u] : pattern_id_to_node_id) {
            ans += (node[u].cnt > 0);
        }
        cout << ans << endl;

        clear_cnt();
    }

    /**
     * 查询哪种模式串 S_id 在文本串 T 中出现次数最多，返回他们的编号和出现次数
     */
    pair<vector<int>, int> answer2(char* t) {
        query2(t);

        vector<int> res1;
        int res2 = 0;
        for (auto [id, u] : pattern_id_to_node_id) {
            if (node[u].cnt >= res2) {
                if (node[u].cnt > res2) {
                    res1.clear();
                }
                res1.push_back(id);
                res2 = node[u].cnt;
            }
        }

        clear_cnt();
        return {res1, res2};
    }

    /**
     * 查询并输出每种模式串 S_id 在文本串 T 中出现的次数
     */
    void answer3(char* t) {
        query2(t);

        for (auto [id, u] : pattern_id_to_node_id) {
            cout << node[u].cnt << endl;
        }

        clear_cnt();
    }

} acam;
