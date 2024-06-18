#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define MKSTR(x) #x
#define CONCAT(x, y) x##y

/* TO STRING */

template <typename A, typename B>
string to_string (pair<A, B> p);

template <typename A, typename B, typename C>
string to_string (tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string (tuple<A, B, C, D> p);

template <typename A, typename B, typename C, typename D, typename E>
string to_string (tuple<A, B, C, D, E> p);

string to_string (const string& str) {
    return '"' + str + '"';
}

string to_string (const char* str) {
    return to_string ((string)(str + 1));
}

string to_string (bool b) {
    return (b ? "true" : "false");
}

template <size_t N>
string to_string (bitset<N> bs) {
    string res = "";
    for (int i = 0; i < N; ++i) {
        res += char ('0' + bs[i]);
    }
    return res;
}

template <typename T>
string to_string (const T& vec) {
    bool first = true;
    string res = "[";
    for (const auto& val : vec) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string (val);
    }
    res += "]";
    return res;
}

template <typename A, typename B>
string to_string (pair<A, B> p) {
    return "(" + to_string (p.first) + ", " + to_string (p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string (tuple<A, B, C> p) {
    return "(" + to_string (get<0> (p)) + ", " + to_string (get<1> (p)) + ", " + to_string (get<2> (p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string (tuple<A, B, C, D> p) {
    return "(" + to_string (get<0> (p)) + ", " + to_string (get<1> (p)) + ", " + to_string (get<2> (p)) + ", " +
           to_string (get<3> (p)) + ")";
}

template <typename A, typename B, typename C, typename D, typename E>
string to_string (tuple<A, B, C, D> p) {
    return "(" + to_string (get<0> (p)) + ", " + to_string (get<1> (p)) + ", " + to_string (get<2> (p)) + ", " +
           to_string (get<3> (p)) + ", " + to_string (get<4> (p)) + ")";
}

template <typename T>
string to_string (T* arr, int n) {
    bool first = true;
    string res = "[";
    for (int i = 1; i <= n; ++i) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string (arr[i]);
    }
    res += "]";
    return res;
}

/* DEBUG */

void DEBUG () {
}

template <typename T, typename... U>
void DEBUG (const T& Head, const U&... Tail) {
    cout << to_string (Head);
    cout << (sizeof...(Tail) ? ", " : "\n");
    DEBUG (Tail...);
}

vector<string> DEBUG_NAMES (string name_list) {
    vector<string> res;
    string cur = "";
    for (char ch : name_list) {
        if (ch == ',') {
            if (!cur.empty ()) {
                res.push_back (cur);
                cur = "";
            }
        } else {
            cur += ch;
        }
    }
    if (!cur.empty ()) {
        res.push_back (cur);
        cur = "";
    }
    return res;
}

vector<string> DEBUG_VALUES () {
    return {};
}

template <typename T, typename... U>
vector<string> DEBUG_VALUES (const T& Head, const U&... Tail) {
    vector<string> res;
    res.push_back (to_string (Head));
    if (sizeof...(Tail)) {
        vector<string> tmp = DEBUG_VALUES (Tail...);
        for (auto& t : tmp) {
            res.push_back (t);
        }
    }
    return res;
}

string COMBINE_DEBUG_OUTPUT (const vector<string>& names, const vector<string>& values) {
    auto name_it = names.begin ();
    auto value_it = values.begin ();
    bool first = true;
    string res = "";
    while (name_it != names.end () && value_it != values.end ()) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += *name_it + " = " + *value_it;
        ++name_it;
        ++value_it;
    }
    return res;
}

#ifdef LOCAL
#define D(...)                                                                                                   \
    do {                                                                                                         \
        cout << "[D] " << COMBINE_DEBUG_OUTPUT (DEBUG_NAMES (#__VA_ARGS__), DEBUG_VALUES (__VA_ARGS__)) << endl; \
    } while (false)

#define DN(arr, n)                                                     \
    do {                                                               \
        cout << "[D] " << #arr << " = " << to_string (arr, n) << endl; \
    } while (false)

#define DF(...)                                    \
    do {                                           \
        cout << "[D] func = " << __func__ << endl; \
    } while (false)

#define ASSERT(x) assert (x)
#else
#define D(...)
#define DN(arr, n)
#define DF()
#define ASSERT(x)
#endif

void purin_init ();

void purin_solve ();

void purin_local_multi_case () {
    freopen ("标准输入_StarndardInput.in", "r", stdin);
    freopen ("标准输出_StarndardOutput.out", "w", stdout);

    auto skip_space_and_check_eof = [] () {
        char ch = getc (stdin);
        while (isspace (ch)) {
            ch = getc (stdin);
        }
        if (ch == EOF) {
            return true;
        }
        ungetc (ch, stdin);
        return false;
    };

    int t = 1;
    const int T_LIM = 20;

    cin >> t;
    cout << "CASE_COUNT = " << t << endl;
    for (int i = 1; i <= t; ++i) {
        cout << "--------" << endl << "CASE #" << i << endl;
        purin_solve ();
        cout << endl << endl;
        // only use the following code in LOCAL testing
        if (t < T_LIM && !skip_space_and_check_eof ()) {
            t = max (t, i + 1);
        }
    }
    puts ("");
}
