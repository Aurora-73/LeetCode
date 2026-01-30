// Created: 2025-12-15
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个整数数组nums，数组中的元素 互不相同。
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

class Solution1 {
public:
	vector<vector<int>> subsets(vector<int> &nums) {
		vector<vector<int>> res = { {} }; // 先插入空集
		vector<int> curr;
		dfs(curr, 0, nums, res);
		return res;
	}

private:
	void dfs(vector<int> &curr, unsigned i, const vector<int> &nums, vector<vector<int>> &res) {
		if(i == nums.size()) return;
		curr.push_back(nums[i]);
		res.push_back(curr); // 仅在插入新的元素后加入结果，防止重复
		dfs(curr, i + 1, nums, res);
		curr.pop_back();
		dfs(curr, i + 1, nums, res);
	}
};

class Solution {
public:
	vector<vector<int>> subsets(vector<int> &nums) {
		n = nums.size();
		res.clear(), curr.clear();
		res.reserve(1 << n);
		curr.reserve(n);
		backtrack(nums, 0);
		return res;
	}

private:
	vector<vector<int>> res;
	vector<int> curr;
	int n;
	void backtrack(vector<int> &nums, int i) {
		if(i == n) {
			res.push_back(curr);
			return;
		}
		curr.push_back(nums[i]);
		backtrack(nums, i + 1);
		curr.pop_back();
		backtrack(nums, i + 1);
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 2, 3 };
	cout << sol.subsets(nums) << endl;
	nums = { 0 };
	cout << sol.subsets(nums) << endl;
}