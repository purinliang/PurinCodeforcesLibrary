#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * DisjointSetUnion
 *
 * July 17, 2024
 * problem: https://www.luogu.com.cn/problem/P3367
 * submission: https://www.luogu.com.cn/record/166689145
 */
struct DisjointSetUnion {
    int n;
    vector<int> prt, siz;

    void init(int n) {
        this->n = n;
        prt.clear(), prt.resize(n + 2);
        siz.clear(), siz.resize(n + 2);
        for (int i = 1; i <= n; ++i) {
            prt[i] = i, siz[i] = 1;
        }
    }

    int find(int u) {
        int ru = u;
        while (prt[ru] != ru) {
            ru = prt[ru];
        }
        int p = prt[u];
        while (p != ru) {
            prt[u] = ru;
            u = p, p = prt[u];
        }
        return ru;
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    bool merge(int u, int v) {
        int ru = find(u), rv = find(v);
        if (ru == rv) return false;
        if (siz[ru] < siz[rv]) swap(ru, rv);
        prt[rv] = ru, siz[ru] += siz[rv];
        return true;
    }

} dsu;
