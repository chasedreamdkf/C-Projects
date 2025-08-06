#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 无重复字符的最长子串
class Solution1 {
public:
    int lengthOfLongestSubstring(string s) {
        // cout << s.length() << endl;
        if(s.length() == 1) return 1;
        int maxSubstrLen = 0;
        int flag = 0;
        for(int i = 0; i < s.length(); i++){
            string sub = s.substr(i, 1);
            for(int j = i+1; j < s.length(); j++) {
                if(sub.find(s[j]) < sub.length()) {
                    if (maxSubstrLen < sub.length()) {
                        maxSubstrLen = sub.length();
                    }
                    flag = 1;
                    break;
                } else {
                    sub.append(s.substr(j, 1));
                }
                if(j == s.length()-1){
                    if (maxSubstrLen < sub.length()) {
                        maxSubstrLen = sub.length();
                    }
                }
            }
            // cout << sub << endl;
        }
        if(!flag) return s.length();
        // cout << endl;
        // cout << s.find('6') << endl;
        return maxSubstrLen;
    }
};

// 寻找两个正序数组的中位数
class Solution2 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 合并数组
        for(int i = 0; i < nums2.size(); i++){
            nums1.push_back(nums2[i]);
        }
        // 排序
        for(int i = 0; i < nums1.size(); i++){
            for(int j = i+1; j < nums1.size(); j++){
                if(nums1[i] > nums1[j]){
                    swap(nums1[i], nums1[j]);
                }
            }
        }
        if(nums1.size() % 2) {
            return (double)nums1[nums1.size() / 2];
        } else {
            return (nums1[nums1.size() / 2] + nums1[nums1.size() / 2 - 1]) / 2.0;
        }
    }
};

// 最长回文子串, 中心扩散法
class Solution3 {
public:
    pair<int, int> extendSubstr(string s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        return {left + 1, right - 1};
    }

    string longestPalindrome(string s) {
        int start = 0, end = 0;
        for(int i = 0; i < s.length(); i++) {
            auto [left1, right1] = extendSubstr(s, i, i);
            auto [left2, right2] = extendSubstr(s, i, i + 1);
            if(right1 - left1 > end -start) {
                start = left1;
                end = right1;
            }

            if(right2 - left2 > end -start) {
                start = left2;
                end = right2;
            }
        }
        return s.substr(start, end - start + 1);
    }
};

// Z 字形变换
class Solution4 {
public:
    string convert(string s, int numRows) {
        string result = "";
        if(s.length() <= numRows) return s;
        if(numRows == 1) return s;
        int sumGap = numRows + (numRows - 2);
        int nextGap = 0;
        for(int i = 0; i < numRows; i++) {
            int t = i + (sumGap-nextGap);
            result += s[i];
            while(1) {
                if(t >= s.length()) break;
                if(t < s.length() && nextGap != sumGap) {
                    result += s[t];
                }
                if(nextGap) {
                    if(t+nextGap >= s.length()) break;
                    result += s[t+nextGap];
                }
                t += sumGap;

            }
            nextGap += 2;
        }
        return result;
    }
};

// 字符串转换整数 (atoi)
class Solution5 {
public:
    int myAtoi(string s) {
        s = removeStartSpace(s);
        // cout << s << endl;
        int i = 0;
        long result = 0;
        if (s[0] == '+' || s[0] == '-')
            i = 1;
        for (; i < s.length(); i++) {
            // cout << i;
            if (s[i] < '0' || s[i] > '9')
                break;
            
            result = result * 10 + (s[i] - '0');
            // cout << i << ": " << result << endl;
            if(result > 2147483647) {
                if(s[0] == '+') return 2147483647;
                if(s[0] == '-') return -2147483648;
            }
            if(result > 2147483647) return 2147483647;
        }
        if(s[0] == '-') return result * -1;
        return result;
    }

    string removeStartSpace(string s) {
        int i = 0;
        while(1) {
            if(s[i] != ' ') break;
            i++;
        }
        return s.substr(i);
    }
};

// 盛最多水的容器
class Solution6 {
public:
    int maxArea(vector<int>& height) {
        if(height.size() == 1) return 0;
        if(height.size() == 2) return min(height[0], height[1]);
        int mArea = 0;
        int l = height.size();
        int i = 0, j = l - 1;
        while(i < j) {
            mArea = max(mArea, min(height[i], height[j]) *  (j - i));
            if(height[i] <= height[j]) i++;
            else if(height[i] > height[j]) j--;
        }
        return mArea;
    }
};

// 整数转罗马数字
class Solution7 {
public:
    string intToRoman(int num) {
        string result = "";
        int d = 0;
        while(num) {
            result = OneIntToRoman(num % 10, d) + result;
            num /= 10;
            d++;
        }
        return result;
    }

    /**
     * @param num: 需转换的数字
     * @param d: 该数字对应的位置，0：个位；1：十位；2：百位；3：千位
     * @return result: 返回的字符串
     */
    string OneIntToRoman(int num, int d) {
        string result = "";
        if(num == 4) {
            switch(d) {
                case 0: result = "IV"; break;
                case 1: result = "XL"; break;
                case 2: result = "CD"; break;
            }
        }
        if(num == 9) {
            switch(d) {
                case 0: result = "IX"; break;
                case 1: result = "XC"; break;
                case 2: result = "CM"; break;
            }
        }
        if(num > 0 && num < 4) {
            string temp = "";
            switch(d) {
                case 0: temp = "I"; break;
                case 1: temp = "X"; break;
                case 2: temp = "C"; break;
                case 3: temp = "M"; break;
            }
            while(num--) {
                result += temp;
            }
        }
        if(num >= 5 && num < 9) {
            string temp = "";
            switch(d) {
                case 0: result = "V"; temp = "I"; break;
                case 1: result = "L"; temp = "X"; break;
                case 2: result = "D"; temp = "C"; break;
            }
            num %= 5;
            while(num--) {
                result += temp;
            }
        }
        return result;
    }
};

// 三数之和
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        // 枚举 a
        for (int first = 0; first < n; ++first) {
            // 需要和上一次枚举的数不相同
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            // c 对应的指针初始指向数组的最右端
            int third = n - 1;
            int target = -nums[first];
            // 枚举 b
            for (int second = first + 1; second < n; ++second) {
                // 需要和上一次枚举的数不相同
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                // 需要保证 b 的指针在 c 的指针的左侧
                while (second < third && nums[second] + nums[third] > target) {
                    --third;
                }
                // 如果指针重合，随着 b 后续的增加
                // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
                if (second == third) {
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    result.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return result;
    }
};

string Map[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

// 电话号码的字母组合
class Solution17 {
public:
    vector<string> letterCombinations(string digits) {
        if(digits == "" || digits == "1") return vector<string>(0);
        int index = digits[0] - '0';
        // cout << Map[index] << endl;
        vector<string> result(1);
        vector<string> temp;
        for(int i = 0; i < digits.length(); i++) {
            index = digits[i] - '0';
            // cout << index << endl;
            for(int j = 0; j < result.size(); j++) {
                for(int k = 0; k < Map[index].length(); k++) {
                    temp.push_back(result[j]+Map[index][k]);
                }
            }
            result = temp;
            temp.clear();
        }
        return result;
    }
};
int main() {
    // Solution s;
    // vector<int> arr = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    // auto out = s.intToRoman(58);
    // cout << out << endl;
    return 0;
}