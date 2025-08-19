/**
 * 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
 * 示例 1：
 * 输入：n = 3
 * 输出：["((()))","(()())","(())()","()(())","()()()"]
 * 示例 2：
 * 输入：n = 1
 * 输出：["()"]
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result = {"()"};
        if(n == 1) return result;
        for(int i = 1; i < n; i++) {
            result = generateList(result);
        }
        return result;
    }

    /**
     * 在数组`arr`中查询是否有`target`
     * @param arr: 被查的数组
     * @param target: 查询目标
     * @return 查询到返回`true`, 否则返回`false`
     */
    bool isInArr(vector<string> arr, string target) {
        if(arr.size() == 0) return false;
        for(string item: arr) {
            if(target == item) return true;
        }
        return false;
    }

    /**
     * 生成一次`括号`序列
     * @param original: 原始序列
     */
    vector<string> generateList(vector<string> original) {
        vector<string> result = {};
        for (string item : original) {
            for(int i = 0; i <= item.length(); ++i) {
            string temp = item;
            temp.insert(i, "()");
            if(!isInArr(result, temp)) result.push_back(temp);
            }
            // string temp = "()";
            // temp.insert(1, item);
            // if(!isInArr(result, temp)) result.push_back(temp);
            // string temp1 = "()";
            // string temp2 = "()";
            // temp1.insert(0, item);
            // temp2.insert(2, item);
            // if(!isInArr(result, temp1)) result.push_back(temp1);
            // if(!isInArr(result, temp2)) result.push_back(temp2);
        }
        // for(string item: original) {
        //     string temp1 = "()";
        //     string temp2 = "()";
        //     temp1.insert(0, item);
        //     temp2.insert(2, item);
        //     if(!isInArr(result, temp1)) result.push_back(temp1);
        //     if(!isInArr(result, temp2)) result.push_back(temp2);
        // }
        // for(int i = 0; i <= original[original.size()-1].length(); ++i) {
        //     string temp = original[original.size()-1];
        //     temp.insert(i, "()");
        //     if(!isInArr(result, temp)) result.push_back(temp);
        // }
        return result;
    }
};

int main() {
    int n;
    Solution s;
    while(1) {
        cout << "请输入n值: ";
        cin >> n;
        auto res = s.generateParenthesis(n);
        for(auto item: res) {
            cout << item << ' ';
        }
        cout << endl;
        vector<string> test = {"(((())))","((()()))","((())())","((()))()","(()(()))","(()()())","(()())()","(())(())","(())()()","()((()))","()(()())","()(())()","()()(())","()()()()"};
        for(auto item: test) {
            if(!s.isInArr(res, item)) cout << item << endl;
        }
    }
    return 0;
}