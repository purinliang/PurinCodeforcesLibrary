#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void apply_op(stack<ll>& num, char op) {
    if (op < 0) {  // unary_operator is stored as minus
        ll r = num.top();
        num.pop();
        switch (-op) {
            case '+':
                num.push(r);
                break;
            case '-':
                num.push(-r);
                break;
        }
        return;
    }

    // binary_operator
    ll r = num.top();
    num.pop();
    ll l = num.top();
    num.pop();

    switch (op) {
        case '+':
            num.push(l + r);
            break;
        case '-':
            num.push(l - r);
            break;
        case '*':
            num.push(l * r);
            break;
        case '/':
            num.push(l / r);
            break;
    }
}

ll evaluate(const string& s) {
    auto is_digit = [&](char c) { return '0' <= c && c <= '9'; };
    auto is_unary_op = [&](char c) { return c == '+' || c == '-'; };
    auto is_op = [&](char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    };
    auto is_space = [&](char c) { return std::isspace(c); };
    auto op_priority = [&](char op) {
        if (op < 0) {  // unary_operator is stored as minus
            return 3;
        }
        if (op == '+' || op == '-') {
            return 1;
        }
        if (op == '*' || op == '/') {
            return 2;
        }
        return -1;
    };

    stack<ll> num;
    stack<char> op;
    bool can_be_unary = true;
    for (int i = 0; i < s.size(); ++i) {
        if (is_space(s[i])) {
            continue;
        }
        if (s[i] == '(') {
            op.push('(');
            can_be_unary = true;
            continue;
        }
        if (s[i] == ')') {
            while (op.top() != '(') {
                apply_op(num, op.top());
                op.pop();
            }
            op.pop();
            can_be_unary = false;
            continue;
        }
        if (is_op(s[i])) {
            char cur_op = s[i];
            if (can_be_unary && is_unary_op(s[i])) {
                cur_op = -cur_op;  // unary_operator is stored as minus
            }
            while (!op.empty() && ((cur_op >= 0 && op_priority(op.top()) >=
                                                       op_priority(cur_op)) ||
                                   (cur_op < 0 && op_priority(op.top()) >
                                                      op_priority(cur_op)))) {
                apply_op(num, op.top());
                op.pop();
            }
            op.push(cur_op);
            can_be_unary = true;
            continue;
        }
        if (is_digit(s[i])) {
            ll number = 0;
            while (i < s.size() && is_digit(s[i])) {
                number = number * 10LL + (s[i] - '0');
                ++i;
            }
            num.push(number);
            --i;
            can_be_unary = false;
            continue;
        }
    }
    while (!op.empty()) {
        apply_op(num, op.top());
        op.pop();
    }
    return num.top();
}

int main() {
    string str1 = "-(1 - 2) * 3 - (+4 * 5)";  // = -17
    cout << evaluate(str1) << endl;
    string str2 = "-(1 + 2) / 3 + (-4 + 5)";  // = 0
    cout << evaluate(str2) << endl;
}
