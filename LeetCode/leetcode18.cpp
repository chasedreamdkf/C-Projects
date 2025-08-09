// 四数之和
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        if (nums.size() < 4) {
            return result;
        }
        sort(nums.begin(), nums.end());
        int length = nums.size();
        for (int i = 0; i < length - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            if ((long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] >
                target) {
                break;
            }
            if ((long)nums[i] + nums[length - 3] + nums[length - 2] +
                    nums[length - 1] <
                target) {
                continue;
            }
            for (int j = i + 1; j < length - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                if ((long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] >
                    target) {
                    break;
                }
                if ((long)nums[i] + nums[j] + nums[length - 2] +
                        nums[length - 1] <
                    target) {
                    continue;
                }
                int left = j + 1, right = length - 1;
                while (left < right) {
                    long sum =
                        (long)nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum == target) {
                        result.push_back(
                            {nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) {
                            left++;
                        }
                        left++;
                        while (left < right && nums[right] == nums[right - 1]) {
                            right--;
                        }
                        right--;
                    } else if (sum < target) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        return result;
    }
};

int main() {
    vector<int> arr = {5, 1, 4, 3, 2, 0};
    sort(arr.begin(), arr.end());
    for(auto item: arr) {
        cout << item << " ";
    }
    cout << endl;
    arr.clear();
    cout << arr.size() << endl;
    return 0;
}