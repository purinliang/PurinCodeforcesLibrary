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

const int MAXN = 2e6 + 10;
int n;
char s[MAXN];

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
    vector<pair<int,int>> pattern_id_to_node_id;

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
        pattern_id_to_node_id.push_back({id,u});
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
     * 查询文本串T 在所有模式串 S_id 中出现的总次数
     */
    void answer(char* t) {
        query(t);
        dp_on_fail_tree(root);

        for (auto [id,u] : pattern_id_to_node_id) {
            cout << node[u].cnt << endl;
        }
        for (int i = 0; i < node.size(); ++i) {
            // 清空本次查询的影响，注意 dp_on_fail_tree 污染了其他节点
            node[i].cnt = 0;
        }
    }

} acam;

void purin_init() {}

void purin_solve() {
    RD(n);
    D(n);
    acam.init();
    for (int i = 1; i <= n; ++i) {
        RD(s);
        D(s);
        acam.insert(s, i);
    }
    acam.build();
    acam.build_fail_tree();
    RD(s);
    D(s);
    acam.answer(s);
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
