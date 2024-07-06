#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct GridGraph {
    int _n, _m;
    vector<vector<int>> _graph;
    vector<vector<bool>> _vis;

    bool is_valid(int x, int y) {
        if (x < 1 || x > _n || y < 1 || y > _m) {
            return false;
        }
        return true;
    }

    void init(int n, int m) {
        _n = n, _m = m;
        _graph.clear(), _graph.resize(_n + 2);
        fill(_graph.begin(), _graph.end(), vector<int>(_m + 2));
        _vis.clear(), _vis.resize(_n + 2);
        fill(_vis.begin(), _vis.end(), vector<int>(_m + 2));
        for (int i = 1; i <= _n; ++i) {
            for (int j = 1; j <= _m; ++j) {
                _graph[i][j] = 0;
                _vis[i][j] = false;
            }
        }
    }

    static const int D_LEN = 4;
    vector<int> dx = {-1, 0, 1, 0, -1, -1, 1, 1};
    vector<int> dy = {0, -1, 0, 1, -1, 1, -1, 1};

    void dfs(int ux, int uy) {
        for (int di = 0; di < D_LEN; ++di) {
            int vx = ux + dx[di];
            int vy = uy + dy[di];
            if (is_valid(vx, vy)) {
                dfs(vx, vy);
            }
        }
    }

    void bfs(int sx, int sy) {
        queue<pair<int, int>> q;
        auto enqueue = [&](int x, int y) {
            _vis[x][y] = true;
            q.push({x, y});
        };
        enqueue(sx, sy);
        while (!q.empty()) {
            auto [ux, uy] = q.front();
            q.pop();
            for (int di = 0; di < D_LEN; ++di) {
                int vx = ux + dx[di];
                int vy = uy + dy[di];
                if (is_valid(vx, vy)) {
                    enqueue(vx, vy);
                }
            }
        }
    }
};
