#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct GridGraph {
    int _n, _m;
    vector<vector<int>> _graph;
    vector<vector<bool>> _vis;

    bool is_valid(int x, int y) {
        if (x < 1 || x > n || y < 1 || y > n) {
            return false;
        }
        return true;
    }

    static const int D_LEN = 4;
    vector<int> dx = {-1, 0, 1, 0, -1, -1, 1, 1};
    vector<int> dy = {0, -1, 0, 1, -1, 1, -1, 1};

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
            vis[x][y] = true;
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

const int MAXN = 1e3 + 10;  // 图的行数的最大值
const int MAXM = 1e3 + 10;  // 图的列数的最大值

int n, m;  // 图的行数，列数
char graph[MAXN][MAXM];
bool vis[MAXN][MAXM];

bool is_valid(int x, int y, char target_color) {
    if (x < 1 || x > n || y < 1 || y > m) {  // 判断x和y不要越界
        return false;
    }
    if (vis[x][y] || graph[x][y] != target_color) {
        // 判断点[x][y]没有被访问过，且和目标颜色一致
        return false;
    }
    return true;
}

void flood_fill_dfs(int ux, int uy, char target_color) {
    // 下面三行是为了方便枚举上、下、左、右四个方向
    static int dx[] = {-1, 0, 1, 0};
    static int dy[] = {0, -1, 0, 1};
    const int d_len = 4;
    for (int k = 0; k < d_len; ++k) {
        int vx = ux + dx[k];
        int vy = uy + dy[k];
        if (is_valid(vx, vy, target_color)) {
            flood_fill_dfs(vx, vy, target_color);  // dfs写法
        }
    }
}

void flood_fill_bfs(int sx, int sy) {
    char target_color = graph[sx][sy];
    queue<pair<int, int>> q;
    vis[sx][sy] = 1;
    q.push({sx, sy});
    while (!q.empty()) {
        int ux = q.front().first;
        int uy = q.front().second;
        q.pop();
        // 下面三行是为了方便枚举上、下、左、右四个方向
        static int dx[] = {-1, 0, 1, 0};
        static int dy[] = {0, -1, 0, 1};
        const int d_len = 4;
        for (int k = 0; k < d_len; ++k) {
            int vx = ux + dx[k];
            int vy = uy + dy[k];
            if (is_valid(vx, vy, target_color)) {
                vis[vx][vy] = 1;
                q.push({vx, vy});  // bfs写法
            }
        }
    }
}
