#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

/* RANDOM */

#define TIME chrono::system_clock::now ().time_since_epoch ().count ()

#ifdef LOCAL
const int rnd_seed = 19937;
#else
const int rnd_seed = TIME;
#endif  // LOCAL

mt19937 rnd (rnd_seed);

// Generate an signed int between [L, R]
int range_rand (int L, int R) {
    assert (L <= R);
    int res = (int)((1.0 * rnd () / UINT_MAX) * (R - L + 1)) + L;
    return res;
}

// Generate an int between [0, R)
int range_rand (int R) {
    assert (R > 0);
    return range_rand (0, R - 1);
}

// shuffle(a + 1, a + 1 + n, rnd);