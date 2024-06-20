#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Tree {
    struct Node {
        vector<int> _adj;

        string to_string(int u) const { return std::to_string(u); }
    };

    int _root;
    vector<Node> _node;

    void init(int n, int root = 1) {
        _node.clear(), _node.resize(n + 2);
        _root = root;
    }

    void add_edge(int u, int v) {
        _node[u]._adj.push_back(v);
        _node[v]._adj.push_back(u);
    }

    string to_string(int u, int p, string prefix, bool is_last_ch) const {
        if (!u) {
            return "";
        }
        string r_prefix = prefix + (u != _root ? (is_last_ch ? "╰── " : "├── ") : "    ");
        string r_res = _node[u].to_string(u) + "\n";
        string ch_res;
        int last_ch = 0;
        for (auto& v : _node[u]._adj) {
            if (v == p) {
                continue;
            }
            last_ch = v;
        }
        for (auto& v : _node[u]._adj) {
            if (v == p) {
                continue;
            }
            ch_res += to_string(v, u, prefix + (is_last_ch ? "    " : "│   "), (v == last_ch));
        }
        return r_prefix + r_res + ch_res;
    }

    string to_string() const { return "Tree = [\n" + to_string(_root, _root, "", true) + "]"; }

    void show() { cout << to_string() << endl; }
};

int n = 20;
int p[500];

int main() {
    Tree tree;
    tree.init(n);
    tree.show();
    for (int i = 2; i <= n; ++i) {
        p[i] = rand() % (i - 1) + 1;
        cout << i << " " << p[i] << endl;
        tree.add_edge(i, p[i]);
    }
    tree.show();
}
