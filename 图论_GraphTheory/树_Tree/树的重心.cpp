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

    int calc_siz(int u, int p) {
        int siz = 1;
        for (int v : _node[u]._adj) {
            if (v == p) {
                continue;
            }
            siz += calc_siz(v, u);
        }
        return siz;
    }

    // TODO
};
