#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 找模式串t在文本串s中的所有出现位置的起始下标，这些出现可以互相重叠
namespace KnuthMorrisPrattAlgorithm {

vector<int> getPi(char* s) {
    int slen = strlen(s + 1);
    vector<int> pi(slen + 1);
    for (int i = 2, j = 0; i <= slen; ++i) {
        for (; j > 0 && s[i] != s[j + 1]; j = pi[j]);  // 不断失配，直到第一个匹配或者j为0
        j += (s[i] == s[j + 1]);  // 如果匹配，则前缀函数+1，这些都是正常的前缀函数操作
        pi[i] = j;                // [1,i]串的最长公共前后缀长度为j
    }
    return pi;
}

vector<int> kmp(char* s, char* t) {
    int slen = strlen(s + 1), tlen = strlen(t + 1);
    vector<int> pi = getPi(t), res;
    for (int i = 1, j = 0; i <= slen; ++i) {
        for (; j > 0 && s[i] != t[j + 1]; j = pi[j]);  // 不断失配，直到第一个匹配或者j为0
        j += (s[i] == t[j + 1]);  // 如果匹配，则前缀函数+1，这些都是正常的前缀函数操作
        if (j == tlen)  // 前缀函数刚好是模式串的长度
            res.push_back(i - tlen +
                          1);  // 串s的[i-tlen+1, i]位置出现了这个串，其实就是以i为结尾的串
    }
    return res;
}

// 一个变形，求s的长度为tlen的前缀，在s中出现的所有不重叠的位置，解决这个问题时，如果多次调用kmp求解不同长度的前缀的答案，则不如改成用Z函数会更快，因为Z函数可以更方便地利用“无重叠”这个条件。

int kmp2(char* s, int tlen) {
    vector<int> pi = getPi(s);
    char* t = s;
    int slen = strlen(s + 1);
    int cnt = 0;
    int last = 0;
    for (int i = 1, j = 0; i <= slen; ++i) {
        for (; j > 0 && (j + 1 > tlen || s[i] != t[j + 1]);
             j = pi[j]);  // 不断失配，直到第一个匹配或者j为0
        j += (j <= tlen && s[i] == t[j + 1]);  // 如果匹配，则前缀函数+1，这些都是正常的前缀函数操作
        if (j == tlen) {
            int begin = i - tlen + 1;
            if (begin > last) {
                ++cnt;
                last = begin + tlen - 1;
            }
        }
    }
    return cnt;
}

}  // namespace KnuthMorrisPrattAlgorithm

namespace ExtendKnuthMorrisPrattAlgorithm {

vector<int> getZ(char* s, int n) {
    vector<int> z(n + 1);
    z[1] = n;
    for (int i = 2, l = 0, r = 0; i <= n; ++i) {
        if (i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        for (; i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]; ++z[i]);
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

vector<int> exkmp(char* s, char* t) {
    int n = strlen(s + 1), m = strlen(t + 1);
    vector<int> z = getZ(t, m), res(n + 1);
    for (int i = 1, l = 0, r = 0; i <= n; ++i) {
        if (i <= r) res[i] = min(z[i - l + 1], r - i + 1);
        for (; i + res[i] <= n && s[i + res[i]] == t[res[i] + 1]; ++res[i]);
        if (i + res[i] - 1 > r) l = i, r = i + res[i] - 1;
    }
    return res;
}

}  // namespace ExtendKnuthMorrisPrattAlgorithm
