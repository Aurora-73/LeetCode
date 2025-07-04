// Created: 2025-07-04
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1493. 删掉一个元素以后全为 1 的最长子数组
给你一个二进制数组nums，你需要从中删掉一个元素。
请你在删掉元素的结果数组中，返回最长的且只包含 1 的非空子数组的长度。
如果不存在这样的子数组，请返回 0。
示例 1：
    输入：nums = {1,1,0,1}
    输出：3
    解释：删掉位置 2 的数后，{1,1,1} 包含 3 个 1。
示例 2：
	输入：nums = {0,1,1,1,0,1,1,0,1}
	输出：5
	解释：删掉位置 4 的数字后，{0,1,1,1,1,1,0,1} 的最长全 1 子数组为 {1,1,1,1,1}。
示例 3：
	输入：nums = {1,1,1}
	输出：2
	解释：你必须要删除一个元素。
提示：
	1 <= nums.length <= 10^5
	nums{i}要么是0要么是1。 */

class Solution {
public:
	int longestSubarray(vector<int> &nums) {
		int res = 0, n = nums.size(), i = 0, j = 0, k = 1;
		while(i < n) {
			if(!nums[i]) {
				if(k > 0) {
					--k;
				} else {
					while(nums[j]) ++j;
					++j;
				}
			}
			res = max(res, i - j); // 必须删除一个元素
			++i;
		}
		return res;
	}
}; // 类似于 1004N，k 固定为1，且必须删除元素

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 1, 0, 1 };
	cout << sol.longestSubarray(nums) << endl; // 3

	nums = { 0, 1, 1, 1, 0, 1, 1, 0, 1 };
	cout << sol.longestSubarray(nums) << endl; // 5

	nums = { 1, 1, 1 };
	cout << sol.longestSubarray(nums) << endl; // 2
}