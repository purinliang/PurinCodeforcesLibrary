#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void bucket_sort(int* a, int n, int val_range) {
    static vector<int> cnt;
    cnt.clear(), cnt.resize(val_range + 2);
    for (int i = 1; i <= n; ++i) {
        ++cnt[a[i]];
    }
    int top = 0;
    for (int i = 1; i <= n; ++i) {
        while (cnt[top] == 0) {
            ++top;
        }
        --cnt[top];
        a[i] = top;
    }
}

void WTN(int* a, int n) {
    for (int i = 1; i <= n; ++i) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

const int MAXN = 20 + 10;
int n;
int a[MAXN];

int main() {
    n = 16;
    for (int i = 1; i <= n; ++i) {
        a[i] = rand() % n + 1;
    }
    WTN(a, n);

    bucket_sort(a, n, *max_element(a + 1, a + 1 + n));
    WTN(a, n);
}
