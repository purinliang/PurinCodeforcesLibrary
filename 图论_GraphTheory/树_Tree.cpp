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

    Tree() {}
    Tree(int n, int root = 1) { init(n, root); }

    void init(int n, int root = 1) {
        _node.clear(), _node.resize(n + 2);
        _root = root;
    }

    void add_edge(int u, int v) {
        _node[u]._adj.push_back(v);
        _node[v]._adj.push_back(u);
    }

    string to_string(int u, int p, string prefix, string u_prefix) const {
        string lch_res, rch_res, u_res = _node[u].to_string(u) + "\n";
        vector<int> ch;
        for (int v : _node[u]._adj) {
            if (v == p) {
                continue;
            }
            ch.push_back(v);
        }
        if (ch.empty()) {
            return (prefix + u_prefix) + u_res;
        }
        for (int i = 0; i < ch.size(); ++i) {
            int v = ch[i];
            bool is_lch = i * 2 + 1 < ch.size();
            if (is_lch) {
                string l_prefix = (u == _root) ? "" : ((u_prefix == "╭── ") ? "    " : "│   ");
                lch_res += to_string(v, u, prefix + l_prefix, (v == ch.front()) ? "╭── " : "├── ");
            } else {
                string r_prefix = (u == _root) ? "" : ((u_prefix == "╰── ") ? "    " : "│   ");
                rch_res += to_string(v, u, prefix + r_prefix, (v == ch.back()) ? "╰── " : "├── ");
            }
        }
        return lch_res + (prefix + u_prefix) + u_res + rch_res;
    }

    string to_string() const { return "Tree = [\n" + to_string(_root, _root, "", "") + "]"; }

    void show() { cout << to_string() << endl; }
};

int rand_int(int n) {
    return (n <= 1) ? n : (rand() % (n - 1) + 1);
}

int rand_int_low(int n) {
    int res = n, times = 5;
    while (times--) {
        res = std::min(res, rand_int(n));
    }
    return res;
}

int rand_int_high(int n) {
    return n + 1 - rand_int_low(n);
}

vector<int> rand_perm(int n) {
    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) {
        perm[i] = i;
    }
    random_shuffle(perm.begin() + 1, perm.end());
    return perm;
}

vector<pair<int, int>> gen_rand_tree(int n, function<int(int)> rand_int) {
    vector<pair<int, int>> edge;
    vector<int> perm = rand_perm(n);
    Tree tree(n, perm[1]);
    for (int i = 2; i <= n; ++i) {
        int prt_i = rand_int(i - 1);
        int u = perm[i], v = perm[prt_i];
        if (std::rand() % 2 == 0) {
            swap(u, v);
        }
        edge.push_back({u, v});
    }
    random_shuffle(edge.begin(), edge.end());
    for (auto& [u, v] : edge) {
        tree.add_edge(u, v);
    }
    tree.show();
    return edge;
}

void test_gen_rand_tree() {
    const int n = 40;
    gen_rand_tree(n, rand_int_low);
    gen_rand_tree(n, rand_int);
    gen_rand_tree(n, rand_int_high);
}

int main() {
    test_gen_rand_tree();
    return 0;
}
