// Created: 2025-05-12
#include "MyUtils.hpp"

/* 39. 组合总和
给你一个 无重复元素 的整数数组candidates 和一个目标整数target，
找出candidates中可以使数字和为目标数target 的 所有不同组合，并以列表形式返回。
你可以按 任意顺序 返回这些组合。
candidates 中的 同一个 数字可以 无限制重复被选取。如果至少一个数字的被选数量不同，则两种组合是不同的。
对于给定的输入，保证和为target 的不同组合数少于 150 个。
示例1：
	输入：candidates = {2,3,6,7}, target = 7
	输出：{{2,2,3},{7}}
	解释：
	2 和 3 可以形成一组候选，2 + 2 + 3 = 7。注意 2 可以使用多次。
	7 也是一个候选， 7 = 7。
	仅有这两种组合。
示例2：
	输入: candidates = {2,3,5}, target = 8
	输出: {{2,2,2,2},{2,3,3},{3,5}}
示例 3：
	输入: candidates = {2}, target = 1
	输出: {}
提示：
	1 <= candidates.length <= 30
	2 <= candidates{i} <= 40
	candidates 的所有元素 互不相同
	1 <= target <= 40 */

class Solution1 {
public:
	vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
		res.clear();
		curr.clear();
		n = candidates.size();
		std::sort(candidates.begin(), candidates.end());
		backtrack(candidates, 0, target);
		return std::move(res);
	}

private:
	int n;
	vector<int> curr;
	vector<vector<int>> res;
	void backtrack(vector<int> &candidates, int i, int target) {
		if(target <= 0) {
			if(target == 0) {
				res.push_back(curr);
			}
			return;
		}
		if(i == n) {
			return;
		}
		if(target < candidates[i]) return;
		curr.push_back(candidates[i]);
		backtrack(candidates, i, target - candidates[i]);
		curr.pop_back();
		backtrack(candidates, i + 1, target);
	}
}; // 选或不选的 backtrack
/*每个 i 都分裂成两支，递归树更“胖”
剪枝点分散在多个 if
状态由 (i, target) 驱动，不太贴合“组合枚举”的直觉*/

class Solution {
public:
	vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
		sort(candidates.begin(), candidates.end());
		backtrack(candidates, 0, target);
		return std::move(res);
	}

private:
	vector<vector<int>> res;
	vector<int> temp;
	void backtrack(vector<int> &candidates, int start, int target) {
		if(target == 0) {
			res.emplace_back(temp);
			return;
		}

		for(int i = start; i < candidates.size(); ++i) {
			int val = candidates[i];
			if(val > target) {
				return;
			} // 因为 candidates 已排序，后面只会更大
			temp.emplace_back(val);
			backtrack(candidates, i, target - val);
			temp.pop_back();
		}
	}
}; // 每次至少选一个的 backtrack
/*每一层递归代表“当前组合选下一个数”
start 天然保证不重复组合
排序 + val + sum > tar → 非常干净的剪枝
递归树更窄，逻辑更贴合问题本质*/

int main() {
	Solution sol;
	vector<int> candidates;
	int target;

	candidates = { 2, 3, 6, 7 }, target = 7;
	cout << sol.combinationSum(candidates, target);

	candidates = { 2, 3, 5 }, target = 8;
	cout << sol.combinationSum(candidates, target);

	candidates = { 2 }, target = 1;
	cout << sol.combinationSum(candidates, target);
}