#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    int left_child;
    int right_child;
    int data;
};

const int MAXN = 2e5 + 10;

int root;
Node tree[MAXN];

void dfs(int u) {
    if (u == 0) {
        return;
    }
    cout << tree[u].data << endl;
    dfs(tree[u].left_child);
    dfs(tree[u].right_child);
}
