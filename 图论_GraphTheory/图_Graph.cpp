#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Graph {
    struct Node {
        vector<int> _adj;
        string to_string(int u) const { return std::to_string(u); }
    };

    int _n;
    vector<Node> _node;
    set<pair<int, int>> _edge;

    Graph() {}
    Graph(int n) { init(n); }

    void init(int n) {
        _n = n;
        _node.clear(), _node.resize(_n + 2);
        _edge.clear();
    }

    void add_edge(int u, int v) {
        _node[u]._adj.push_back(v);
        _node[v]._adj.push_back(u);
        _edge.insert(std::minmax(u, v));
    }

    string to_string(vector<bool>& vis_node, vector<pair<int, int>>& vis_edge, int u, int r,
                     string prefix, string u_prefix) const {
        if (vis_node[u]) {
            return "";
        }
        vis_node[u] = true;
        string lch_res, rch_res, u_res = _node[u].to_string(u) + "\n";
        vector<int> ch;
        for (int v : _node[u]._adj) {
            if (vis_node[v]) {
                continue;
            }
            ch.push_back(v);
        }
        for (int i = 0; i < ch.size(); ++i) {
            int v = ch[i];
            if (vis_node[v]) {
                continue;
            }
            vis_edge.push_back({u, v});
            bool is_lch = i * 2 + 1 < ch.size();
            if (is_lch) {
                string l_prefix = (u == r) ? "" : ((u_prefix == "╭── ") ? "    " : "│   ");
                lch_res += to_string(vis_node, vis_edge, v, r, prefix + l_prefix,
                                     (v == ch.front()) ? "╭── " : "├── ");
            } else {
                string r_prefix = (u == r) ? "" : ((u_prefix == "╰── ") ? "    " : "│   ");
                rch_res += to_string(vis_node, vis_edge, v, r, prefix + r_prefix,
                                     (v == ch.back()) ? "╰── " : "├── ");
            }
        }
        return lch_res + (prefix + u_prefix) + u_res + rch_res;
    }

    string to_string() const {
        vector<bool> vis_node(_n + 2);
        vector<pair<int, int>> vis_edge;
        string res = "Graph = [\n";
        for (int i = 1; i <= _n; ++i) {
            res += to_string(vis_node, vis_edge, i, i, "", "");
        }
        res += " ExtraEdge = [\n";
        set<pair<int, int>> extra_edge(_edge.begin(), _edge.end());
        for (auto& [u, v] : vis_edge) {
            // cout << " vis " << u << " " << v << endl;
            extra_edge.erase({u, v});
            extra_edge.erase({v, u});
        }
        for (auto& [u, v] : extra_edge) {
            res += "    " + std::to_string(u) + " ── " + std::to_string(v) + "\n";
        }
        res += "]";
        return res;
    }

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
    // random_shuffle(perm.begin() + 1, perm.end());
    return perm;
}

vector<pair<int, int>> gen_rand_graph(int n, int m, bool connected, function<int(int)> rand_int) {
    vector<pair<int, int>> edge;
    vector<int> perm = rand_perm(n);
    Graph graph(n);
    if (connected) {
        assert(m >= n - 1);
        for (int i = 2; i <= n; ++i) {
            int prt_i = rand_int(i - 1);
            int u = perm[i], v = perm[prt_i];
            if (u > v) {
                swap(u, v);
            }
            edge.push_back({u, v});
            graph.add_edge(u, v);
        }
        m -= n - 1;
        for (int i = 1; i <= m; ++i) {
            int u, v;
            while (true) {
                u = rand_int(n), v = rand_int(n);
                if (u == v) {
                    continue;
                }
                if (u > v) {
                    swap(u, v);
                }
                if (graph._edge.count(std::minmax(u, v))) {
                    continue;
                }
                break;
            }
            edge.push_back({u, v});
            graph.add_edge(u, v);
        }
    }
    sort(edge.begin(), edge.end());
    // random_shuffle(edge.begin(), edge.end());
    for (auto& [u, v] : edge) {
        // cout << u << " " << v << endl;
        // graph.add_edge(u, v);
    }
    graph.show();
    return edge;
}

void test_gen_rand_graph() {
    const int n = 10, m = 15;
    const bool connected = true;
    const bool allow_self_loop = true;
    const bool allow_parralel_edge = true;
    gen_rand_graph(n, m, connected, rand_int);
}

int main() {
    test_gen_rand_graph();
    return 0;
}
