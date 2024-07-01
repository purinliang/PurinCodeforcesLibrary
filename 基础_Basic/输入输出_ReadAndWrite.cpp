#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

// TODO 下面好像有点bug的
/* READ */

template <typename T>
void _RD(T& var) {
    cin >> var;
}
void _RD(int& var) {
    scanf("%d", &var);
}
void _RD(uint& var) {
    scanf("%u", &var);
}
void _RD(ll& var) {
    scanf("%lld", &var);
}
void _RD(ull& var) {
    scanf("%llu", &var);
}
void _RD(double& var) {
    scanf("%lf", &var);
}
void _RD(char& var) {
    scanf(" %c", &var);
}
void _RD(char* var) {
    scanf("%s", var + 1);
}
template <typename A, typename B>
void _RD(pair<A, B>& var) {
    _RD(var.first);
    _RD(var.second);
}
void RD() {}
template <typename T, typename... U>
void RD(T& Head, U&... Tail) {
    _RD(Head);
    RD(Tail...);
}
template <typename T>
void RDN(T* arr, int n) {
    for (int i = 1; i <= n; ++i) {
        _RD(arr[i]);
    }
}
template <typename T>
void RDV(vector<T>& vec, int n) {
    vec.resize(n);
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        _RD(*it);
    }
}

/* WRITE */

template <typename T>
void _WT(const T& var) {
    cout << var;
}
void _WT(const int& var) {
    printf("%d", var);
}
void _WT(const uint& var) {
    printf("%u", var);
}
void _WT(const ll& var) {
    printf("%lld", var);
}
void _WT(const ull& var) {
    printf("%llu", var);
}
void _WT(const double& var) {
    printf("%.12f", var);
}
void _WT(const char& var) {
    putchar(var);
}
void _WT(const char* var) {
    printf("%s", var + 1);
}
template <typename A, typename B>
void _WT(const pair<A, B>& var) {
    _WT(var.first);
    putchar(' ');
    _WT(var.second);
}
void WT() {}
template <typename T, typename... U>
void WT(const T& Head, const U&... Tail) {
    _WT(Head);
    putchar(sizeof...(Tail) ? ' ' : '\n');
    WT(Tail...);
}
template <typename T>
void WTN(T* arr, int n) {
    for (int i = 1; i <= n; ++i) {
        _WT(arr[i]);
        putchar(" \n"[i == n]);
    }
}
template <typename T>
void WTA(T& vec) {
    auto it = vec.begin();
    while (it != vec.end()) {
        _WT(*it);
        ++it;
        putchar(" \n"[it == vec.end()]);
    }
}
