// Created: 2025-10-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个整数数组和一个整数k，请找到该数组中和为k的连续子数组的个数。
示例 1：
	输入:nums = {1,1,1}, k = 2
	输出: 2
	解释: 此题 {1,1} 与 {1,1} 为两种不同的情况
示例 2：
	输入:nums = {1,2,3}, k = 3
	输出: 2
提示:
	1 <= nums.length <= 2 * 10^4
	-1000 <= nums{i} <= 1000
	-10^7<= k <= 10^7
注意：本题与主站 560题相同： */

class Solution {
public:
	int subarraySum(vector<int> &nums, int k) {
		int res = 0, now = 0;
		unordered_map<int, int> prefix;
		for(auto num : nums) {
			++prefix[now];
			now += num;
			auto pair = prefix.find(now - k);
			if(pair != prefix.end()) {
				res += pair->second;
			}
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	int k;
	nums = { 1, 1, 1 }, k = 2;
	cout << sol.subarraySum(nums, k) << endl;
	nums = { 1, 2, 3 }, k = 3;
	cout << sol.subarraySum(nums, k) << endl;
}