#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* DEBUG AND ASSERT*/

#ifdef LOCAL
#include ".\LOCAL.h"
#else
#define D(...)
#define DN(arr, n)
#define DF()
#define ASSERT(x)
#endif

/* MY CODE BEGIN */

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;

void purin_init () {
    cout << fixed << setprecision (12);
    ios::sync_with_stdio (false);
    cin.tie (nullptr);
    cout.tie (nullptr);
}

void purin_solve () {
}

/* MY CODE END */

int main () {
    purin_init ();
#ifdef LOCAL
    local_multi_case ();
#else
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        purin_solve ();
    }
#endif
    return 0;
}
