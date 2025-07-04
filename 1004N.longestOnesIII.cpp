// Created: 2025-07-04
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1004. 最大连续1的个数 III
给定一个二进制数组nums和一个整数 k，假设最多可以翻转 k 个 0，则返回执行操作后 数组中连续 1 的最大个数。
示例 1：
	输入：nums = {1,1,1,0,0,0,1,1,1,1,0}, K = 2
	输出：6
	解释：{1,1,1,0,0,1,1,1,1,1,1}
	粗体数字从 0 翻转到 1，最长的子数组长度为 6。
示例 2：
	输入：nums = {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1}, K = 3
	输出：10
	解释：{0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1}
	粗体数字从 0 翻转到 1，最长的子数组长度为 10。
提示：
	1 <= nums.length <= 10^5
	nums{i}不是0就是1
	0 <= k <= nums.length */

class Solution {
public:
	int longestOnes(vector<int> &nums, int k) {
		int res = 0, n = nums.size(), i = 0, j = 0;
		while(i < n) {
			if(!nums[i]) {
				if(k > 0) {
					--k;
				} else {
					while(nums[j]) ++j;
					++j; // 注意这里还要在加一次才能移除第一个 0
				}
			}
			res = max(res, i - j + 1);
			++i;
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	int k;
	nums = { 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 }, k = 2;
	cout << sol.longestOnes(nums, k) << endl; // 6
	nums = { 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1 }, k = 3;
	cout << sol.longestOnes(nums, k) << endl; // 10
}