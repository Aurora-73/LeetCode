// Created: 2025-12-27
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 幂集。
编写一种方法，返回某集合的所有子集。集合中不包含重复的元素。
说明：解集不能包含重复的子集。
示例：
 输入：nums = {1,2,3}
 输出：
{  {3}, {1}, {2}, {1,2,3}, {1,3}, {2,3}, {1,2}, {}} */

class Solution {
public:
	vector<vector<int>> subsets(vector<int> &nums) {
		vector<int> curr;
		curr.reserve(nums.size());
		vector<vector<int>> res;
		res.push_back({});
		dfs(0, nums, res, curr);
		return res;
	}

private:
	void dfs(int index, const vector<int> &nums, vector<vector<int>> &res, vector<int> &curr) {
		if(index == nums.size()) {
			if(!curr.empty()) {
				res.push_back(curr);
			}
			return;
		}
		dfs(index + 1, nums, res, curr);
		curr.push_back(nums[index]);
		dfs(index + 1, nums, res, curr);
		curr.pop_back();
	}
};

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 2, 3 };
	cout << sol.subsets(nums) << endl;
}