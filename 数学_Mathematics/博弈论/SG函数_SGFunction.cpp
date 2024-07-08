
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * sg[u] == 0 Bob(the second player) Win
 * sg[u] != 0 Alice(the first player) Win
 *
 * How to find sg[u]? If stage u can change into stage v using one operation, than stage v is one of
 * the next stages of stage u. sg[u] means "the smallest non-negative integer that does not exist in
 * the set of sg[v]" or "mex of the set of sg[v]". For example, if stage u has three next stages v1,
 * v2, and v3, and their corresponding sg[v1] == 1, sg[v2] == 2, sg[v3] == 4, then "the smallest
 * non-negative integer that does not exist in {1, 2, 4}" is 0, so sg[u] == 0. If the set is {0, 1,
 * 2, 4}, then sg[u] == 3.
 *
 * If there are several different or same type of sub game, and they are pairwisely independent. The
 * whole game's sg function is the xor sum of all of the sub game. If two game have the same sg
 * function, they are totally the same game! Bob can just imitate Alice's operation to win the whole
 * game.
 *
 * For example, in NIM game, there are several groups of stones. Each operation, a player has to
 * choose one non empty group, and then remove at least one stone from it. The one who cannot
 * operator first will lose the game. Each group of stones are a game with sg[i] == i, (if the group
 * has x stones, the sg function is x itself). The whole sg function of the whole game is
 * xorsum(a[i]).
 * auto gen_v_of_u_sample_1 = [&](int u) {
 *   vector<int> vs;
 *   for (int i = 1; i <= u; ++i)
 *       if (u - i >= 0) vs.push_back(u - i);
 *   return vs;
 * };
 *
 * Another example, if for one non-empty group, the player has to remove 1 or 2 stone(s) from it.
 * Then, sg[0] == 0, sg[1] == max{sg[0]} == 1, sg[2] == mex{sg[0], sg[1]} == 2, sg[3] == mex{sg[1],
 * sg[2]} == 0. Then, sg[i] == i % 3.
 * auto gen_v_of_u_sample_2 = [&](int u) {
 *   vector<int> vs;
 *   for (int i = 1; i <= 2; ++i)
 *       if (u - i >= 0) vs.push_back(u - i);
 *   return vs;
 * };
 *
 * You can combine a game with sg[x] == x and sg[y] == y % 3, by using xorsum.
 */

struct SGFunction {
   private:
    int _n;
    vector<int> _sg;
    function<vector<int>(int)> _gen_v_of_u;

    int dfs(int u) {
        if (_sg[u] != -1) {
            return _sg[u];
        }
        vector<int> vs = _gen_v_of_u(u), sg_v;
        for (const int& v : vs) {  // v is one of the children of u
            sg_v.push_back(dfs(v));
        }
        sort(sg_v.begin(), sg_v.end());
        int res = 0;
        for (const int& i : sg_v) {
            if (res < i) {
                break;
            }
            ++res;
        }
        _sg[u] = res;
        return res;
    }

   public:
    void init(int n, function<vector<int>(int)> gen_v_of_u) {
        _n = n, _gen_v_of_u = gen_v_of_u;
        _sg.clear(), _sg.resize(_n + 2);
        fill(_sg.begin(), _sg.end(), -1);
        for (int i = 0; i <= _n; ++i) {
            dfs(i);
        }
        show_sg();
    }

    void show_sg() {
        for (int i = 0; i <= _n; ++i) {
            cout << format("sg[{}] = {}", i, _sg[i]) << endl;
        }
    }
} sg;

auto gen_v_of_u_sample_1 = [&](int u) {
    vector<int> vs;
    for (int i = 1; i <= u; ++i)
        if (u - i >= 0) vs.push_back(u - i);
    return vs;
};
// sg.init(20, gen_v_of_u_sample_1);

auto gen_v_of_u_sample_2 = [&](int u) {
    vector<int> vs;
    for (int i = 1; i <= 2; ++i)
        if (u - i >= 0) vs.push_back(u - i);
    return vs;
};
// sg.init(20, gen_v_of_u_sample_2);
