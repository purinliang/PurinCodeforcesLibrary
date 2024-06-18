#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef LOCAL
#include ".\标准本地调试_StandardLocalDebug.h"
#else
#define D(...)
#define DN(arr, n)
#define DF()
#define ASSERT(x)
#endif

template <typename T>
void _RD (T& var) {
    cin >> var;
}

void _RD (char* var) {
    cin >> (var + 1);
}

void RD () {
}

template <typename T, typename... U>
void RD (T& Head, U&... Tail) {
    _RD (Head);
    RD (Tail...);
}

template <typename T>
void RDN (T* arr, int n) {
    for (int i = 1; i <= n; ++i) {
        _RD (arr[i]);
    }
}

template <typename T>
void _WT (const T& var) {
    cout << var;
}

void _WT (const char* var) {
    cout << (var + 1);
}

void WT () {
}

template <typename T, typename... U>
void WT (const T& Head, const U&... Tail) {
    _WT (Head);
    cout << (sizeof...(Tail) ? " " : "\n");
    WT (Tail...);
}

template <typename T>
void WTN (T* arr, int n) {
    for (int i = 1; i <= n; ++i) {
        _WT (arr[i]);
        cout << (i < n ? " " : "\n");
    }
}

/* MY CODE BEGIN */

const int INF = 0x3F3F3F3F;
const ll LINF = 0x3F3F3F3F3F3F3F3FLL;
const int MAXN = 3e5 + 10;

void purin_init () {
    cout << fixed << setprecision (12);
    ios::sync_with_stdio (false);
    cin.tie (nullptr);
    cout.tie (nullptr);
#define endl "\n"
#define fout fflush (stdout)
}

int n;
int a[MAXN];

void purin_solve () {
    RD (n);
    RDN (a, n);
    D (n);
    DN (a, n);
    // WT (n);
    // WTN (a, n);
}

int main () {
    purin_init ();
#ifdef LOCAL
    purin_local_multi_case ();
#else
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        purin_solve ();
    }
#endif
    return 0;
}
