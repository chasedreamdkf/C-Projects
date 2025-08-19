/**
 * 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
 * 有效字符串需满足：
 * 1. 左括号必须用相同类型的右括号闭合。
 * 2. 左括号必须以正确的顺序闭合。
 * 3. 每个右括号都有一个对应的相同类型的左括号。
 */

#include <iostream>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        if(s.length() <= 1) return false;
        stack<char> stk;
        int count = 0;
        for(char c: s) {
            if(c == '{' || c == '[' || c == '(') {
                stk.push(c);
                ++count;
            }
            if(c == '}') {
                if(stk.size() != 0 && stk.top() == '{') stk.pop();
                else {
                    return false;
                }
            }
            if(c == ']') {
                if(stk.size() != 0 && stk.top() == '[') stk.pop();
                else {
                    return false;
                }
            }
            if(c == ')') {
                if(stk.size() != 0 && stk.top() == '(') stk.pop();
                else {
                    return false;
                }
            }
        }
        if (count == s.length() || stk.size() != 0){
            return false;
        }
        return true;
    }
};

int main() {
    Solution s;
    string str;
    while(1) {
        cin >> str;
        auto res = s.isValid(str);
        cout << res << endl;
    }
    
    return 0;
}

