#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct DisjointSetUnion {
    vector<int> fnd, siz;

    void Init(int n) {
        fnd.clear(), fnd.resize(n + 2);
        siz.clear(), siz.resize(n + 2);
        for (int i = 1; i <= n; i++) {
            fnd[i] = i, siz[i] = 1;
        }
    }

    int Find(int x) {
        int rt = x;
        while (fnd[rt] != rt) {
            rt = fnd[rt];
        }
        int fx = fnd[x];
        while (fx != rt) {
            fnd[x] = rt;
            x = fx, fx = fnd[x];
        }
        return rt;
    }

    bool Same(int x, int y) {
        return Find(x) == Find(y);
    }

    bool Merge(int x, int y) {
        int rx = Find(x), ry = Find(y);
        if (rx == ry) {
            return false;
        }
        if (siz[rx] < siz[ry]) {
            swap(rx, ry);
        }
        fnd[ry] = rx, siz[rx] += siz[ry];
        return true;
    }

} dsu;
