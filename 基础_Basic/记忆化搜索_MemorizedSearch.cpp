#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Parameter {
    int p1;
    ll p2;
    bool p3;

    bool operator<(const Parameter& par) const {
        if (p1 < par.p1 || par.p1 < p1) {
            return p1 < par.p1;
        }
        if (p2 < par.p2 || par.p2 < p2) {
            return p2 < par.p2;
        }
        if (p3 < par.p3 || par.p3 < p3) {
            return p3 < par.p3;
        }
        return false;
    }

    bool operator==(const Parameter& par) const {
        if ((*this) < par || par < (*this)) {
            return false;
        }
        return true;
    }
};

// TODO: 研究一下变长参数的模板，争取做到和python一样
struct MemorizedSearchMap {
   private:
    map<Parameter, ll> _map;

   public:
    void init() { _map.clear(); }

    ll search(Parameter par) {
        auto _map_it = _map.find(par);
        if (_map_it != _map.end()) {
            return _map_it->second;
        }
        auto& [cnt, lim, suc] = par;
        ll res = 0LL;

        // calc it
        Parameter next_par = {cnt, lim, suc};
        res += search(next_par);

        _map[par] = res;
        return res;
    }
};

struct MemorizedSearchUnorderedMap {
   private:
    unordered_map<Parameter, ll> _map;

   public:
    void init(int n) {
        _map.clear();
        _map.reserve(3 * n);
    }

    ll search(Parameter par) {
        auto _map_it = _map.find(par);
        if (_map_it != _map.end()) {
            return _map_it->second;
        }
        auto& [cnt, lim, suc] = par;
        ll res = 0LL;

        // calc it
        Parameter next_par = {cnt, lim, suc};
        res += search(next_par);

        _map[par] = res;
        return res;
    }
};
