// Created: 2025-12-15
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个无重复元素的正整数数组candidates和一个正整数target，
找出candidates中所有可以使数字和为目标数target的唯一组合。
candidates中的数字可以无限制重复被选取。如果至少一个所选数字数量不同，则两种组合是不同的。
对于给定的输入，保证和为target 的唯一组合数少于 150 个。
示例 1：
	输入: candidates = {2,3,6,7}, target = 7
	输出: {{7},{2,2,3}}
示例 2：
	输入: candidates = {2,3,5}, target = 8
	输出: {{2,2,2,2},{2,3,3},{3,5}}
示例 3：
	输入: candidates = {2}, target = 1
	输出: {}
示例 4：
	输入: candidates = {1}, target = 1
	输出: {{1}}
示例 5：
	输入: candidates = {1}, target = 2
	输出: {{1,1}}
提示：
	1 <= candidates.length <= 30
	1 <= candidates{i} <= 200
	candidate 中的每个元素都是独一无二的。
	1 <= target <= 500 */

class Solution {
public:
	vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
		dfs(candidates, 0, target);
		return std::move(res);
	}

private:
	vector<int> curr {};
	vector<vector<int>> res {};
	void dfs(vector<int> &candidates, unsigned i, int target) {
		if(target < 0 || i >= candidates.size()) {
			return;
		}
		curr.push_back(candidates[i]);
		target -= candidates[i];
		if(target == 0) {
			res.push_back(curr);
		} else if(target > 0) {
			dfs(candidates, i, target);
		}
		target += candidates[i];
		curr.pop_back();
		dfs(candidates, i + 1, target);
	}
};

int main() {
	Solution sol;
	vector<int> candidates;
	int target;
	candidates = { 2, 3, 6, 7 }, target = 7;
	cout << sol.combinationSum(candidates, target) << endl;
	candidates = { 2, 3, 5 }, target = 8;
	cout << sol.combinationSum(candidates, target) << endl;
	candidates = { 2 }, target = 1;
	cout << sol.combinationSum(candidates, target) << endl;
	candidates = { 1 }, target = 1;
	cout << sol.combinationSum(candidates, target) << endl;
	candidates = { 1 }, target = 2;
	cout << sol.combinationSum(candidates, target) << endl;
}