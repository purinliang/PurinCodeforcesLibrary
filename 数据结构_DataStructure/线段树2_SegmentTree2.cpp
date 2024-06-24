#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;

void try_mod(ll& x) {
    if (x >= MOD) {
        x %= MOD;
    }
}

/**
 * If apply M = _mul_tag first, and then apply A = _add_tag:
 *
 *      If there is already an M, and now you want to apply an A, the original val should be R1 = (V
 * * M) + A. And under the tag-applying order, the new val will be R2 = (V * M') + A', which is
 * totally the same.
 *
 *      If there is already an A, and now you want to apply an M, the original val should be R1 = (V
 * + A) * M. However, under the tag-applying order, the new val will be R2 = (V * M') + A'. To make
 * them equal, it requires V * (M - M') + (A * M - A') == 0. Since V is unknown, so M' == M and A'
 * == A * M are required.
 *
 * If apply A = _add_tag first, and then apply M = _mul_tag:
 *
 *      If there is already an A, and now you want to apply an M, the original val should be R1 = (V
 * + A) * M. And under the tag-applying order, the new val will be R2 = (V + A') * M', which is
 * totally the same.
 *
 *  If there is already an M, and now you want to apply an A, the original val should be R1 = (V
 * * M) + A. However, under the tag-applying order, the new val will be R2 = (V + A') * M'. To make
 * them equal, it requires V * (M - M') + (A - A' * M') == 0. Since V is unknown, so M' == M and A'
 * == A / M are required. However, in modint operations, division (/) is hard when MOD is not a
 * prime.
 */
struct NodeTag {
    ll _mul_tag = 1LL;
    ll _add_tag = 0LL;
    NodeTag() {};
    static NodeTag mul(ll val) {
        NodeTag tag;
        tag._mul_tag = val;
        return tag;
    }
    static NodeTag add(ll val) {
        NodeTag tag;
        tag._add_tag = val;
        return tag;
    }
    void apply_tag(int l, int r, const NodeTag& tag) {
        if (tag._mul_tag != 1LL) {
            _mul_tag *= tag._mul_tag;
            _add_tag *= tag._mul_tag;
        }
        if (tag._add_tag != 0LL) {
            _add_tag += tag._add_tag;
        }
        try_mod(_mul_tag);
        try_mod(_add_tag);
    }
    string to_string() const { return std::to_string(_mul_tag) + " " + std::to_string(_add_tag); }
};

struct NodeInfo {
    static const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
    ll _sum = 0LL;
    NodeInfo() {}
    NodeInfo(int l, int r, const NodeInfo& lch, const NodeInfo& rch) {
        _sum = lch._sum + rch._sum;
        try_mod(_sum);
    }
    void apply_tag(int l, int r, const NodeTag& tag) {
        if (tag._mul_tag != 1LL) {
            _sum *= tag._mul_tag;
        }
        if (tag._add_tag != 0LL) {
            _sum += 1LL * (r - l + 1) * tag._add_tag;
        }
        try_mod(_sum);
    }
    string to_string() const { return std::to_string(_sum); }
};
