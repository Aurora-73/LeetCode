// Created: 2025-05-12
#include "MyUtils.hpp"

/* 46. 全排列
给定一个不含重复数字的数组 nums，返回其 所有可能的全排列。
你可以 按任意顺序 返回答案。
示例 1：
	输入：nums = {1,2,3}
	输出：{{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}}
示例 2：
	输入：nums = {0,1}
	输出：{{0,1},{1,0}}
示例 3：
	输入：nums = {1}
	输出：{{1}}
提示：
	1 <= nums.length <= 6
	-10 <= nums{i} <= 10
	nums 中的所有整数 互不相同 */

class Solution1 {
public:
	vector<vector<int>> permute(vector<int> &nums) {
		n = nums.size();
		temp.resize(n);
		size_t fact = 1;
		for(int i = 2; i <= n; ++i) fact *= i;
		res.reserve(fact);
		in_temp = vector<bool>(n, false);
		for(int j = 0; j < n; ++j) {
			dfs(nums, j);
		}
		return res;
	}

private:
	void dfs(vector<int> &nums, int i) {
		if(i < 0 || i >= n || in_temp[i]) {
			return;
		}
		temp[top++] = nums[i];
		in_temp[i] = true;
		if(top == n) {
			res.push_back(temp);
		} else {
			for(int j = 0; j < n; ++j) {
				if(!in_temp[j]) {
					dfs(nums, j);
				}
			}
		}
		--top;
		in_temp[i] = false;
	}
	vector<vector<int>> res;
	vector<bool> in_temp;
	vector<int> temp;
	int n, top = 0;
};

class Solution2 {
public:
	vector<vector<int>> permute(vector<int> &nums) {
		int n = nums.size();
		// 预分配结果空间，n! 个排列
		size_t fact = 1;
		for(int i = 2; i <= n; ++i) fact *= i;
		res.reserve(fact);
		backtrack(nums, 0);
		return res;
	}

private:
	vector<vector<int>> res;

	// 从索引 first 开始，对 nums[first..n-1] 进行全排列
	void backtrack(vector<int> &nums, int first) {
		if(first == nums.size()) {
			res.emplace_back(nums);
			return;
		}
		for(int i = first; i < nums.size(); ++i) {
			swap(nums[first], nums[i]);
			backtrack(nums, first + 1);
			swap(nums[first], nums[i]); // 恢复现场
		}
	}
}; // 去掉标记数组

class Solution {
public:
	vector<vector<int>> permute(vector<int> &nums) {
		n = nums.size();
		curr = std::vector<int>(n);
		visited = std::vector<bool>(n);
		dfs(0, nums);
		return std::move(res);
	}

private:
	int n;
	vector<vector<int>> res;
	vector<int> curr;
	vector<bool> visited;
	void dfs(int i, vector<int> &nums) {
		if(i == n) {
			res.push_back(curr);
			return;
		}
		for(int j = 0; j < n; ++j) {
			if(!visited[j]) {
				curr[i] = nums[j];
				visited[j] = 1;
				dfs(i + 1, nums);
				visited[j] = 0;
			}
		}
	}
};

int main() {
	Solution sol;
	vector<int> vec;
	cout << sol.permute(vec = { 1, 2, 3, 4 });
}