#include <bits/stdc++.h>
using namespace std;

const int TIME_LIMIT = 5000;
const int OUTPUT_LIMIT = 256 * 1024;
const int TEST_CASE_LIMIT = 20;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;

#define MKSTR(x) #x
#define CONCAT(x, y) x##y

/* TO STRING */

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

template <typename A, typename B, typename C, typename D, typename E>
string to_string(tuple<A, B, C, D, E> p);

string to_string(const string& str) {
    return '"' + str + '"';
}

string to_string(const char* str) {
    return to_string((string)(str + 1));
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <size_t N>
string to_string(bitset<N> bs) {
    string res = "";
    for (int i = 0; i < N; ++i) {
        res += char('0' + bs[i]);
    }
    return res;
}

template <typename T>
string to_string(const T& vec) {
    bool first = true;
    string res = "[";
    for (const auto& val : vec) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(val);
    }
    res += "]";
    return res;
}

template <typename T>
string to_string(T* ptr) {
    stringstream stream;
    stream << std::hex << (ll)ptr;
    string res = "addr(0x" + (stream.str()) + ")";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) +
           ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) +
           ", " + to_string(get<3>(p)) + ")";
}

template <typename A, typename B, typename C, typename D, typename E>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) +
           ", " + to_string(get<3>(p)) + ", " + to_string(get<4>(p)) + ")";
}

template <typename T>
string to_string(T* arr, int n) {
    bool first = true;
    string res = "[";
    for (int i = 1; i <= n; ++i) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(arr[i]);
    }
    res += "]";
    return res;
}

/* DEBUG */

void DEBUG() {}

template <typename T, typename... U>
void DEBUG(const T& Head, const U&... Tail) {
    cout << to_string(Head);
    cout << (sizeof...(Tail) ? ", " : "\n");
    fflush(stdout);
    DEBUG(Tail...);
}

vector<string> DEBUG_NAMES(string name_list) {
    vector<string> res;
    string cur = "";
    for (char ch : name_list) {
        if (ch == ',') {
            if (!cur.empty()) {
                res.push_back(cur);
                cur = "";
            }
        } else {
            cur += ch;
        }
    }
    if (!cur.empty()) {
        res.push_back(cur);
        cur = "";
    }
    return res;
}

vector<string> DEBUG_VALUES() {
    return {};
}

template <typename T, typename... U>
vector<string> DEBUG_VALUES(const T& Head, const U&... Tail) {
    vector<string> res;
    res.push_back(to_string(Head));
    if (sizeof...(Tail)) {
        vector<string> tmp = DEBUG_VALUES(Tail...);
        for (auto& t : tmp) {
            res.push_back(t);
        }
    }
    return res;
}

string COMBINE_DEBUG_OUTPUT(const vector<string>& names, const vector<string>& values) {
    auto name_it = names.begin();
    auto value_it = values.begin();
    bool first = true;
    string res = "";
    while (name_it != names.end() && value_it != values.end()) {
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
template <typename T>
void _RD(T& var) {
    cin >> var;
}

void _RD(char* var) {
    string str;
    cin >> str;
    strcpy(var + 1, str.c_str());
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

bool count_output();

template <typename T>
void _WT(const T& var) {
    if (!count_output()) {
        return;
    }
    cout << var;
    fflush(stdout);
}

void _WT(const char* var) {
    if (!count_output()) {
        return;
    }
    cout << (var + 1);
    fflush(stdout);
}

void WT() {}

template <typename T, typename... U>
void WT(const T& Head, const U&... Tail) {
    if (!count_output()) {
        return;
    }
    _WT(Head);
    if (!count_output()) {
        return;
    }
    cout << (sizeof...(Tail) ? " " : "\n");
    if (!count_output()) {
        return;
    }
    WT(Tail...);
}

void WTY(bool var, bool capital = false) {
    if (!count_output()) {
        return;
    }
    if (capital) {
        cout << (var ? "YES" : "NO") << "\n";
    } else {
        cout << (var ? "Yes" : "No") << "\n";
    }
}

template <typename T>
void WTN(T* arr, int n) {
    if (!count_output()) {
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (!count_output()) {
            return;
        }
        _WT(arr[i]);
        if (!count_output()) {
            return;
        }
        cout << (i < n ? " " : "\n");
    }
    fflush(stdout);
}
#endif

#ifdef LOCAL
#define D(...)                                                                             \
    do {                                                                                   \
        if (!count_output()) {                                                             \
            break;                                                                         \
        }                                                                                  \
        cout << "[D] "                                                                     \
             << COMBINE_DEBUG_OUTPUT(DEBUG_NAMES(#__VA_ARGS__), DEBUG_VALUES(__VA_ARGS__)) \
             << endl;                                                                      \
        fflush(stdout);                                                                    \
    } while (false)

#define DN(arr, n)                                                    \
    do {                                                              \
        if (!count_output()) {                                        \
            break;                                                    \
        }                                                             \
        cout << "[D] " << #arr << " = " << to_string(arr, n) << endl; \
        fflush(stdout);                                               \
    } while (false)

#define DF(...)                                    \
    do {                                           \
        if (!count_output()) {                     \
            break;                                 \
        }                                          \
        cout << "[D] func = " << __func__ << endl; \
        fflush(stdout);                            \
    } while (false)

#define ASSERT(x) assert(x)
#else
#define D(...)
#define DN(arr, n)
#define DF()
#define ASSERT(x)
#endif

void purin_init();

void purin_solve();

auto start_time = chrono::high_resolution_clock::now();
auto end_time = chrono::high_resolution_clock::now();
bool is_child_thread_finished;

void report_child_thread_finished() {
    is_child_thread_finished = true;
    end_time = chrono::high_resolution_clock::now();
}

int running_time() {
    if (!is_child_thread_finished) {
        end_time = chrono::high_resolution_clock::now();
    }
    auto running_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    return running_time;
}

int output_count;
bool count_output() {
    if (output_count < OUTPUT_LIMIT) {
        ++output_count;
        return true;
    }
    return false;
}

void init_child_thread() {
    cerr << endl << "Running..." << endl << endl;
    start_time = chrono::high_resolution_clock::now();
    output_count = 0;
    is_child_thread_finished = false;
}

bool cin_eof() {
    char ch;
    while (cin >> ch) {
        if (!isspace(ch)) {
            cin.unget();
            return false;
        }
    }
    return cin.eof();
}

void purin_local_main(bool ignore_test_case_count) {
    init_child_thread();

    purin_init();

    int t = 1;
    if (!ignore_test_case_count) {
        cin >> t;
        cerr << "TestCaseCount = " << t << endl;
    } else {
        t = 16;
        cerr << "MultiCase" << endl;
    }

    for (int i = 1; i <= t; ++i) {
        if (cin_eof()) {
            break;
        }
        cerr << "Running TestCase #" << i << endl;
        if (i > 1) {
            cout << endl << endl << endl;
        }
        cout << "---- " << "TestCase #" << i << " ----" << endl;
        purin_solve();
        if (i == t) {
            cerr << "TestCaseCountExceed, TestCaseCount = " << t << endl;
            t = INT_MAX;
        }
    }

    cerr << endl;

    report_child_thread_finished();
}

void purin_local_test(bool ignore_test_case_count) {
    freopen("标准输入_StarndardInput.in", "r", stdin);
    freopen("标准输出_StarndardOutput.out", "w", stdout);

    thread childThread(purin_local_main, ignore_test_case_count);
    while (true) {
        if (is_child_thread_finished) {
            cerr << "OK" << endl;
            cerr << "RunningTime = " << running_time() << endl;
            break;
        }
        if (running_time() > TIME_LIMIT) {
            cerr << "TimeLimitExceed, TimeLimit = " << TIME_LIMIT << endl;
            cerr << "RunningTime = " << running_time() << endl;
            break;
        }
        if (output_count >= OUTPUT_LIMIT) {
            cerr << "OutputLimitExceed, OutputLimit = " << OUTPUT_LIMIT << endl;
            cerr << "RunningTime = " << running_time() << endl;
            break;
        }
        this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    cerr << endl;
    exit(0);
}
