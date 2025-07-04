// Created: 2025-07-03
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 334. 递增的三元子序列
给你一个整数数组nums，判断这个数组中是否存在长度为 3 的递增子序列。
如果存在这样的三元组下标 (i, j, k)且满足 i < j < k，
使得nums{i} < nums{j} < nums{k}，返回 true ；否则，返回 false。
示例 1：
	输入：nums = {1,2,3,4,5}
	输出：true
	解释：任何 i < j < k 的三元组都满足题意
示例 2：
	输入：nums = {5,4,3,2,1}
	输出：false
	解释：不存在满足题意的三元组
示例 3：
	输入：nums = {2,1,5,0,4,6}
	输出：true
	解释：三元组 (3, 4, 5) 满足题意，
	因为 nums{3} == 0 < nums{4} == 4 < nums{5} == 6
提示：
	1 <= nums.length <= 5 * 10^5
	-2^31 <= nums{i} <= 231 - 1
	进阶：你能实现时间复杂度为 O(n)，空间复杂度为 O(1) 的解决方案吗？ */

class Solution1 {
public:
	bool increasingTriplet(vector<int> &nums) {
		int n = nums.size();
		if(n < 3) {
			return false;
		}
		int first = nums[0], second = INT_MAX;
		for(int i = 1; i < n; i++) {
			int num = nums[i];
			if(num > second) {
				return true;
			} else if(num > first) {
				second = num;
			} else {
				first = num;
			}
		}
		return false;
	}
}; // 贪心算法

class Solution {
public:
	bool increasingTriplet(vector<int> &nums) {
		array<int, 3> tree;
		int n = 0, i;
		for(auto num : nums) {
			for(i = 0; i < n && num > tree[i]; ++i);
			tree[i] = num;
			if(i == n) ++n;
			if(n == 3) return true;
		}
		return false;
	}
}; // 最长递增子序列 分层DAG算法

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 2, 3, 4, 5 };
	cout << sol.increasingTriplet(nums) << endl; // true
	nums = { 5, 4, 3, 2, 1 };
	cout << sol.increasingTriplet(nums) << endl; // false
	nums = { 2, 1, 5, 0, 4, 6 };
	cout << sol.increasingTriplet(nums) << endl; // true
}