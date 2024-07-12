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

const int MAXN = 1e6 + 10;
int n;
char s[MAXN];

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

void purin_init() {}

void purin_solve() {
    RD(s);
    n = strlen(s + 1);
    sam.init(n);
    for (int i = 1; i <= n; ++i) {
        sam.extend(s[i]);
    }
    ll res = sam.answer1();
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
