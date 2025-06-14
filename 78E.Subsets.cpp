// Created: 2025-06-14
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 78. 子集
给你一个整数数组nums，数组中的元素 互不相同。
返回该数组所有可能的子集（幂集）。
解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。
示例 1：
	输入：nums = {1,2,3}
	输出：{{},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3}}
示例 2：
	输入：nums = {0}
	输出：{{},{0}}
提示：
	1 <= nums.length <= 10
	-10 <= nums{i} <= 10
	nums 中的所有元素 互不相同 */

class Solution {
public:
	vector<vector<int>> subsets(vector<int> &nums) {
		res = { {} }, now.clear();
		n = nums.size();
		now.reserve(n), res.reserve(int(pow(2, n)));
		dfs(nums, 0);
		return res;
	}

private:
	int n;
	vector<int> now;
	vector<vector<int>> res;
	void dfs(vector<int> &nums, int index) {
		if(index >= n) return;
		now.push_back(nums[index]);
		res.push_back(now);
		dfs(nums, index + 1);
		now.pop_back();
		dfs(nums, index + 1);
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 2, 3 };
	cout << sol.subsets(nums) << endl; // {{},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3}}
	nums = { 0 };
	cout << sol.subsets(nums) << endl; // {{},{0}}
}