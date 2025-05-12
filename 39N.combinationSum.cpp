// Created: 2025-05-12
#include "MyUtils.h"

/*39. 组合总和
给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，
并以列表形式返回。你可以按 任意顺序 返回这些组合。
candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 
对于给定的输入，保证和为 target 的不同组合数少于 150 个。*/

class Solution {
public:
	vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
		std::sort(candidates.begin(), candidates.end());
		tar = target;
		dfs(candidates, 0);
		return res;
	}

private:
	vector<vector<int>> res;
	vector<int> temp;
	int sum = 0, tar;
	void dfs(vector<int> &candidates, int start) {
		if(sum > tar) {
			return;
		} else if(sum == tar) {
			res.emplace_back(temp);
			return;
		}
		for(int i = start; i < candidates.size(); ++i) {
			int val = candidates[i];
			if(val + sum > tar) {
				return;
			}
			temp.emplace_back(val);
			sum += val;
			dfs(candidates, i);
			temp.pop_back();
			sum -= val;
		}
	}
};

int main() {
	Solution sol;
	vector<int> candidates;
	candidates = { 2, 3, 6, 7 };
	int target = 7;
	cout << sol.combinationSum(candidates, target);
}