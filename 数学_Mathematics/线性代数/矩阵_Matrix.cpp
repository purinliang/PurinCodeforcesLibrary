#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;
const int MAXN = 500 + 1;

int a[MAXN][MAXN];

struct Matrix {
    int _n, _m;
    vector<vector<int>> _ma;

    void init(int n, int m, vector<vector<int>> a) {}
    void init(int n, int m, int a[MAXN][MAXN]) {}
};
