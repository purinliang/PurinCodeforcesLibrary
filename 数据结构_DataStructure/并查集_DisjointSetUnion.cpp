#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct DisjointSetUnion {
    int _n;
    vector<int> _prt, _siz;

    void init(int n) {
        _n = n;
        _prt.clear(), _prt.resize(_n + 2);
        _siz.clear(), _siz.resize(_n + 2);
        for (int i = 1; i <= _n; i++) {
            _prt[i] = i, _siz[i] = 1;
        }
    }

    int find(int x) {
        int rt = x;
        while (_prt[rt] != rt) {
            rt = _prt[rt];
        }
        int prtx = _prt[x];
        while (prtx != rt) {
            _prt[x] = rt;
            x = prtx, prtx = _prt[x];
        }
        return rt;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    bool merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) {
            return false;
        }
        if (_siz[rx] < _siz[ry]) {
            swap(rx, ry);
        }
        _prt[ry] = rx, _siz[rx] += _siz[ry];
        return true;
    }

} dsu;
