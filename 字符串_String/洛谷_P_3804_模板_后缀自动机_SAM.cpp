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
    struct Node {
        int len = 0, link = 0;
        int ch[26] = {};
        ll cnt = 0;
        Node() {};
        void CopyNewNode(const int& l, const Node& n) {
            len = l, link = n.link;
            memcpy(ch, n.ch, sizeof(ch));
            // cnt = 0;
        }
    };

    vector<Node> node;
    int last;  // last末尾节点的位置

    void init() {
        node.clear();
        node.push_back(Node());
        node.push_back(Node());
        node[1] = Node();
        last = 1;
    }

    int new_node() {
        int idx = node.size();
        node.push_back(Node());
        return idx;
    }

    void extend(char ch) {
        int p = last, u = new_node();
        last = u;
        node[u] = Node();
        node[u].len = node[p].len + 1;
        node[u].cnt = 1;
        for (; p && !node[p].ch[ch - 'a']; p = node[p].link)
            node[p].ch[ch - 'a'] = u;
        if (!p)
            node[u].link = 1;
        else {
            int q = node[p].ch[ch - 'a'];
            if (node[p].len + 1 == node[q].len)
                node[u].link = q;
            else {
                int y = new_node();
                node[y].CopyNewNode(node[p].len + 1, node[q]);
                node[q].link = node[u].link = y;
                for (; p && node[p].ch[ch - 'a'] == q; p = node[p].link)
                    node[p].ch[ch - 'a'] = y;
            }
        }
    }

    vector<int> d, rk;

    void dp_on_link_tree() {
        int siz = node.size() - 1;
        d.clear(), d.resize(siz + 2);
        rk.clear(), rk.resize(siz + 2);

        for (int i = 1; i <= siz; ++i) ++d[node[i].len];
        for (int i = 1; i <= siz; ++i) d[i] += d[i - 1];
        for (int i = 1; i <= siz; ++i) rk[d[node[i].len]--] = i;

        for (int i = siz; i >= 1; --i) {
            int u = rk[i], v = node[u].link;  // 对u进行更新则达到了从底向上更新
            node[v].cnt += node[u].cnt;
        }
    }

    ll answer1() {
        dp_on_link_tree();
        ll ans = 0LL;
        int siz = node.size() - 1;
        for (int i = 1; i <= siz; ++i) {
            ans = max(ans, 1LL * node[i].cnt * node[i].len);
        }
        return ans;
    }

} sam;

void purin_init() {}

void purin_solve() {
    RD(s);
    n = strlen(s + 1);
    sam.init();
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
