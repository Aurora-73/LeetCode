// Created: 2025-06-12
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 3423. 循环数组中相邻元素的最大差值
给你一个 循环数组nums，请你找出相邻元素之间的最大绝对差值。
注意：一个循环数组中，第一个元素和最后一个元素是相邻的。
示例 1：
	输入：nums = {1,2,4}
	输出：3
	解释：
	由于nums是循环的，nums{0} 和nums{2}是相邻的，它们之间的绝对差值是最大值|4 - 1| = 3。
示例 2：
	输入：nums = {-5,-10,-5}
	输出：5
	解释：
	相邻元素nums{0} 和nums{1}之间的绝对差值为最大值|-5 - (-10)| = 5。
提示：
	2 <= nums.length <= 100
	-100 <= nums{i} <= 100 */

class Solution {
public:
	int maxAdjacentDistance(vector<int> &nums) {
		int n = nums.size(), maxDiff = abs(nums.front() - nums.back());
		for(int i = 0; i < n - 1; ++i) {
			maxDiff = max(maxDiff, abs(nums[i] - nums[i + 1]));
		}
		return maxDiff;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 2, 4 };
	cout << sol.maxAdjacentDistance(nums) << endl; // 3
	nums = { -5, -10, -5 };
	cout << sol.maxAdjacentDistance(nums) << endl; // 5
}