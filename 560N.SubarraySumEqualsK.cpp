// Created: 2025-06-10
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 560. 和为 K 的子数组
给你一个整数数组 nums 和一个整数k，请你统计并返回 该数组中和为 k 的子数组的个数。
子数组是数组中元素的连续非空序列。
示例 1：
	输入：nums = {1,1,1}, k = 2
	输出：2
示例 2：
	输入：nums = {1,2,3}, k = 3
	输出：2
提示：
	1 <= nums.length <= 2 * 10^4
	-1000 <= nums{i} <= 1000
	-10^7 <= k <= 10^7 */

class Solution1 {
public:
	int subarraySum(vector<int> &nums, int k) {
		int res = 0, suff = 0;
		unordered_map<int, int> map; // 前缀和的值到出现次数的映射
		map[0] = 1;                  // 关键：初始前缀和0出现1次，全部占满也可以作为左侧
		for(auto num : nums) {
			suff += num;
			auto it = map.find(suff - k); // 避免过多的插入次数，导致空间消耗
			if(it != map.end()) {
				res += it->second;
			}
			++map[suff]; // 不能先插入元素
		}
		return res;
	}
};

class Solution {
public:
	int subarraySum(vector<int> &nums, int k) {
		int res = 0, suff = 0;
		unordered_map<int, int> map; // 前缀和的值到出现次数的映射
		for(auto num : nums) {
			++map[suff]; // 先插入元素
			suff += num;
			auto it = map.find(suff - k); // 避免过多的插入次数，导致空间消耗
			if(it != map.end()) {
				res += it->second;
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
	cout << sol.subarraySum(nums, k) << endl; // 2
	nums = { 1, 2, 3 }, k = 3;
	cout << sol.subarraySum(nums, k) << endl; // 2
}