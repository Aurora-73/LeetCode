// Created: 2025-10-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 011. 连续数组
给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的 最长连续子数组，并返回该子数组的长度 。
示例 1：
	输入: nums = {0,1}
	输出: 2
	解释: {0, 1} 是具有相同数量 0 和 1 的最长连续子数组。
示例 2：
	输入: nums = {0,1,0}
	输出: 2
	解释: {0, 1} (或 {1, 0}) 是具有相同数量 0 和 1 的最长连续子数组。
提示：
	1 <= nums.length <= 105
	nums{i} 不是 0 就是 1 */

class Solution {
public:
	int findMaxLength(vector<int> &nums) {
		int res = 0, now = 0, n = nums.size();
		unordered_map<int, int> prefix; // 1的缺少或多出个数 -> 初次出现该情况的下标
		prefix[0] = -1;                 // 因为后续记录的是i，因此这里要从-1开始
		for(int i = 0; i < n; ++i) {
			if(nums[i]) {
				++now;
			} else {
				--now;
			}
			auto pair = prefix.find(now); // 因为是作差，所以应该查找 now 而不是 -now
			if(pair != prefix.end()) {
				res = max(res, i - pair->second);
			} else {
				prefix[now] = i;
			}
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 0, 1 };
	cout << sol.findMaxLength(nums) << endl;
	nums = { 0, 1, 0 };
	cout << sol.findMaxLength(nums) << endl;
}