#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

/* SORT 1-INDEX ARRAY */

template <typename T>
void my_reverse (T* arr, int n) {
    reverse (arr + 1, arr + 1 + n);
}
template <typename T>
void my_sort (T* arr, int n) {
    sort (arr + 1, arr + 1 + n);
}
template <typename T>
int my_unique (T* arr, int n) {
    sort (arr + 1, arr + 1 + n);
    return unique (arr + 1, arr + 1 + n) - (arr + 1);
}
template <typename T>
int my_lower_bound_pos (T* arr, int n, const T& val) {
    return lower_bound (arr + 1, arr + 1 + n, val) - arr;
}
template <typename T>
int my_upper_bound_pos (T* arr, int n, const T& val) {
    return upper_bound (arr + 1, arr + 1 + n, val) - arr;
}
template <typename T>
bool my_find (T* arr, int n, const T& val) {
    int pos = my_lower_bound_pos (arr, n, val);
    return pos <= n && arr[pos] == val;
}

/* SORT VECTOR */

template <typename T>
void my_reverse (vector<T>& vec) {
    reverse (all (vec));
}
template <typename T>
void my_sort (vector<T>& vec) {
    sort (all (vec));
}
template <class T>
int my_unique (vector<T>& vec) {
    sort (all (vec));
    vec.erase (unique (all (vec)), vec.end ());
    return vec.size ();
}
template <typename T>
int my_lower_bound_pos (vector<T>& vec, const T& val) {
    return lower_bound (all (vec), val) - vec.begin ();
}
template <typename T>
int my_upper_bound_pos (vector<T>& vec, const T& val) {
    return upper_bound (all (vec), val) - vec.begin ();
}
template <typename T>
bool my_find (vector<T>& vec, const T& val) {
    int pos = my_lower_bound_pos (vec, val);
    return pos < vec.size () && vec[pos] == val;
}
