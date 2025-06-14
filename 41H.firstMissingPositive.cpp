// Created: 2025-06-14
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 41. 缺失的第一个正数
给你一个未排序的整数数组 nums，请你找出其中没有出现的最小的正整数。
请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
示例 1：
	输入：nums = {1,2,0}
	输出：3
	解释：范围 {1,2} 中的数字都在数组中。
示例 2：
	输入：nums = {3,4,-1,1}
	输出：2
	解释：1 在数组中，但 2 没有。
示例 3：
	输入：nums = {7,8,9,11,12}
	输出：1
	解释：最小的正数 1 没有出现。
提示：
	1 <= nums.length <= 10 ^ 5
	-2 ^ 31 <= nums{i} <= 2 ^ 31 - 1 */

class Solution {
public:
	int firstMissingPositive(vector<int> &nums) {
		int n = nums.size();
		for(int i = 0; i < n; ++i) {
			while(nums[i] >= 1 && nums[i] < n + 1 && nums[i] != i + 1
			    && nums[i] != nums[nums[i] - 1]) { // 防止重复元素导致死循环
				swap(nums[i], nums[nums[i] - 1]);
			}
		}
		for(int i = 0; i < n; ++i) {
			if(nums[i] != i + 1) {
				return i + 1;
			}
		}
		return n + 1;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 2, 0 };
	cout << sol.firstMissingPositive(nums) << endl; // 3
	nums = { 3, 4, -1, 1 };
	cout << sol.firstMissingPositive(nums) << endl; // 2
	nums = { 7, 8, 9, 11, 12 };
	cout << sol.firstMissingPositive(nums) << endl; // 1
	nums = { 1 };
	cout << sol.firstMissingPositive(nums) << endl; // 2
	nums = { 1, 1 };
	cout << sol.firstMissingPositive(nums) << endl; // 2
}