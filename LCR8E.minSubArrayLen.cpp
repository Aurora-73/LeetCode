// Created: 2025-07-24
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 008. 长度最小的子数组
给定一个含有n个正整数的数组和一个正整数 target。
找出该数组中满足其和 ≥ target 的长度最小的 连续子数组{numsl, numsl+1, ..., numsr-1, numsr}，
并返回其长度。如果不存在符合条件的子数组，返回 0。
示例 1：
	输入：target = 7, nums = {2,3,1,2,4,3}
	输出：2
	解释：子数组{4,3}是该条件下的长度最小的子数组。
示例 2：
	输入：target = 4, nums = {1,4,4}
	输出：1
示例 3：
	输入：target = 11, nums = {1,1,1,1,1,1,1,1}
	输出：0
提示：
	1 <= target <= 10^9
	1 <= nums.length <= 10^5
	1 <= nums{i} <= 10^5
进阶：
	如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。 */

class Solution {
public:
	int minSubArrayLen(int target, vector<int> &nums) {
		int n = nums.size(), l = 0, r = 0, res = 0;
		while(r < n) {
			target -= nums[r++];
			if(target <= 0) {
				while(target + nums[l] <= 0) {
					target += nums[l++];
				}
				if(res == 0 || res >= r - l) {
					res = r - l;
				}
			}
		}
		return res;
	}
};

int main() {
	Solution sol;
	int target;
	vector<int> nums;
	target = 7, nums = { 2, 3, 1, 2, 4, 3 };
	cout << sol.minSubArrayLen(target, nums) << endl; // 2
	target = 4, nums = { 1, 4, 4 };
	cout << sol.minSubArrayLen(target, nums) << endl; // 1
	target = 11, nums = { 1, 1, 1, 1, 1, 1, 1, 1 };
	cout << sol.minSubArrayLen(target, nums) << endl; // 0
}