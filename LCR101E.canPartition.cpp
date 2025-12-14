// Created: 2025-12-14
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个非空的正整数数组 nums，请判断能否将这些数字分成元素和相等的两部分。
示例 1：
	输入：nums = {1,5,11,5}
	输出：true
	解释：nums 可以分割成 {1, 5, 5} 和 {11}。
示例 2：
	输入：nums = {1,2,3,5}
	输出：false
	解释：nums 不可以分为和相等的两部分
提示：
	1 <= nums.length <= 200
	1 <= nums{i} <= 100 */

class Solution {
public:
	bool canPartition(vector<int> &nums) {
		int sum = 0, n = nums.size();
		for(int i = 0; i < n; ++i) {
			sum += nums[i];
		}
		if(sum % 2) return false;
		sum /= 2;
		array<vector<int>, 2> dp;
		dp[0].resize(n + 1), dp[1].resize(n + 1);
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 5, 11, 5 };
	cout << sol.canPartition(nums) << endl;
	nums = { 1, 2, 3, 5 };
	cout << sol.canPartition(nums) << endl;
}