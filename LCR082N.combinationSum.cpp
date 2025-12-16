// Created: 2025-12-15
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个可能有重复数字的整数数组candidates和一个目标数target，
找出candidates中所有可以使数字和为target的组合。
candidates中的每个数字在每个组合中只能使用一次，解集不能包含重复的组合。
示例 1：
	输入：candidates = {10,1,2,7,6,1,5}, target = 8
	输出：
	{	{1,1,6},	{1,2,5},	{1,7},	{2,6}	}
示例 2：
	输入：candidates = {2,5,2,1,2}, target = 5
	输出：
	{	{1,2,2},	{5}	}
提示：
	1 <=candidates.length <= 100
	1 <=candidates{i} <= 50
	1 <= target <= 30 */

class Solution1 {
public:
	vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
		std::sort(candidates.begin(), candidates.end());
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
			dfs(candidates, i + 1, target);
		}
		target += candidates[i];
		curr.pop_back();
		for(unsigned j = i + 1; j < candidates.size(); ++j) {
			if(candidates[j] != candidates[i]) {
				dfs(candidates, j, target);
				return;
			}
		}
	}
};

class Solution {
public:
	typedef unordered_map<int, int>::iterator map_iter;
	vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
		int n = candidates.size();
		unordered_map<int, int> cnt;
		for(int i = 0; i < n; ++i) {
			++cnt[candidates[i]];
		}
		dfs(cnt.begin(), cnt.end(), target);
		return std::move(res);
	}

private:
	vector<int> curr {};
	vector<vector<int>> res {};
	void dfs(map_iter begin, map_iter end, int target) {
		if(target < 0 || begin == end) {
			return;
		}
		curr.push_back(begin->first);
		target -= begin->first;
		--begin->second;
		if(target == 0) {
			res.push_back(curr);
		} else if(target > 0 && begin->second > 0) {
			dfs(begin, end, target);
		} else if(target > 0 && begin->second == 0) {
			dfs(next(begin), end, target);
		}
		++begin->second;
		target += begin->first;
		curr.pop_back();
		dfs(next(begin), end, target);
	}
};

int main() {
	Solution sol;
	vector<int> candidates;
	int target;
	candidates = { 10, 1, 2, 7, 6, 1, 5 }, target = 8;
	cout << sol.combinationSum2(candidates, target) << endl;
	candidates = { 2, 5, 2, 1, 2 }, target = 5;
	cout << sol.combinationSum2(candidates, target) << endl;
}