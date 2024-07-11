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

const int MAXN = 5e5 + 10;
int n;
char s[MAXN];

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
            D(u, node[u].fail);
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
            // dep 表示 fail 树的高度，而非回文树的高度。 fail 树的高度
            // 表示子串数量。回文树的高度表示子串长度（的一半）、
            node[next].dep = node[node[next].fail].dep + 1;
            // 这一行必须放在最后，否则会死循环
            node[u].ch[c - 'a'] = next;
        }
        lst = next;
        R.push_back(node[next].dep);  // 以新字符为结尾的回文子串的数量
    }

    void show_R() {
        for (int i = 1; i <= slen(); ++i) {
            cout << R[i] << " ";
        }
        cout << endl;
    }

} pam;

void purin_init() {}

void purin_solve() {
    RD(s);
    n = strlen(s + 1);
    pam.init();
    for (int i = 1; i <= n; ++i) {
        int k = pam.R[i - 1];
        char c = (s[i] - 97 + k) % 26 + 97;
        pam.extend(c);
    }
    pam.show_R();
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
