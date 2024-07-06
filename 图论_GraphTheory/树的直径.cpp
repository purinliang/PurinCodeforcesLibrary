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

    /**
     * return: {a leaf with max depth, the max depth}
     */
    pair<int, int> find_max_dep_leaf(int u, int p) {
        pair<int, int> max_dep_leaf = {u, 1};
        for (int v : _node[u]._adj) {
            if (v == p) {
                continue;
            }
            pair<int, int> dep_leaf = find_max_dep_leaf(v, u);
            if (dep_leaf.second > max_dep_leaf.second) {
                max_dep_leaf = dep_leaf;
            }
        }
        return max_dep_leaf;
    }

    /**
     * return: the diameter
     */
    int find_diameter() {
        auto [max_dep_leaf_1, max_dep_1] = find_max_dep_leaf(_root, _root);
        auto [max_dep_leaf_2, max_dep_2] = find_max_dep_leaf(max_dep_leaf_1, max_dep_leaf_1);
        // the path between max_dep_leaf_1 and max_dep_leaf_2 is the diameter
        // max_dep_1 is the max_dep when root is _root (cound of nodes)
        // max_dep_2 is the length of the diameter path (cound of nodes)
        return max_dep_2;
    }

    int find_diameter_center(int u, int p, int target_dep) {
        if (target_dep == 0) {
            return u;
        }
        for (int v : _node[u]._adj) {
            if (v == p) {
                continue;
            }
            int target = find_diameter_center(v, u, target_dep - 1);
            if (target != 0) {
                return target;
            }
        }
        return 0;
    }

    /**
     * return: the center of diameter
     */
    int find_diameter_center() {
        auto [max_dep_leaf_1, max_dep_1] = find_max_dep_leaf(_root, _root);
        auto [max_dep_leaf_2, max_dep_2] = find_max_dep_leaf(max_dep_leaf_1, max_dep_leaf_1);
        // the path between max_dep_leaf_1 and max_dep_leaf_2 is the diameter
        // max_dep_1 is the max_dep when root is _root (cound of nodes)
        // max_dep_2 is the length of the diameter path (cound of nodes)
        int diameter_center =
            find_diameter_center(max_dep_leaf_1, max_dep_leaf_1, (max_dep_2 + 1) / 2);
        return diameter_center;
    }
};
