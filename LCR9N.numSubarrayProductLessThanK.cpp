// Created: 2025-10-27
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 009. 乘积小于 K 的子数组
给定一个正整数数组 nums和整数 k，请找出该数组内乘积小于 k 的连续的子数组的个数。
示例 1：
	输入: nums = {10,5,2,6}, k = 100
	输出: 8
	解释: 8 个乘积小于 100 的子数组分别为: {10}, {5}, {2}, {6}, {10,5}, {5,2}, {2,6}, {5,2,6}。
	
	需要注意的是 {10,5,2} 并不是乘积小于100的子数组。
示例 2：
	输入: nums = {1,2,3}, k = 0
	输出: 0
提示：
	1 <= nums.length <= 3 * 104
	1 <= nums{i} <= 1000
	0 <= k <= 106 */

class Solution {
public:
	int numSubarrayProductLessThanK(vector<int> &nums, int k) {
		int res = 0, l = 0, r = 0, now = 1, n = nums.size();
		while(r < n) {
			now *= nums[r]; // 左闭右闭
			while(l <= r && now >= k) {
				now /= nums[l];
				++l;
			}
			res += r - l + 1;
			++r;
		}
		return res;
	}
}; // 走一步  走完回缩  加当前长度个
// 每向前走一步要考虑以当前元素结尾的合法子数组个数，在回缩后，这个长度就等于当前窗口的长度

int main() {
	Solution sol;
	vector<int> nums;
	int k;
	nums = { 10, 5, 2, 6 }, k = 100;
	cout << sol.numSubarrayProductLessThanK(nums, k) << endl;
}