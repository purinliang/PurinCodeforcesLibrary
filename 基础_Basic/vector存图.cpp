#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 10;

int n;
vector<int> graph[MAXN];

void init() {
    for (int i = 1; i <= n; ++i) {
        graph[i].clear();
    }
}

void add_edge(int u, int v) {
    graph[u].push_back(v);
}

bool vis[MAXN];

void dfs(int u) {
    if (vis[u]) {
        return;
    }
    vis[u] = true;
    for (int v : graph[u]) {
        dfs(v);
    }
}

void bfs(int s) {
    queue<int> q;
    vis[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
}
