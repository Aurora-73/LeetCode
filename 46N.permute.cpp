// Created: 2025-05-12
#include "MyUtils.h"

/*46. 全排列
给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。*/

class Solution1 {
public:
	vector<vector<int>> permute(vector<int> &nums) {
		n = nums.size();
		temp.resize(n);
		size_t fact = 1;
		for(int i = 2; i <= n; ++i)
			fact *= i;
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
		n = nums.size();
		temp.resize(n);
		in_temp = vector<bool>(n, false);
		size_t fact = 1;
		for(int i = 2; i <= n; ++i)
			fact *= i;
		res.reserve(fact);
		top = 0;
		dfs(nums, 0); // 只传递递归深度
		return res;
	}

private:
	vector<vector<int>> res;
	vector<bool> in_temp;
	vector<int> temp;
	int n, top;
	void dfs(const vector<int> &nums, int depth) {
		if(depth == n) {
			res.push_back(temp); // 此时 top == n
			return;
		}
		for(int i = 0; i < n; ++i) {
			if(!in_temp[i]) {
				temp[top++] = nums[i];
				in_temp[i] = true;
				dfs(nums, depth + 1);
				--top; // 回溯
				in_temp[i] = false;
			}
		}
	}
};

class Solution3 {
public:
	vector<vector<int>> permute(vector<int> &nums) {
		int n = nums.size();
		// 预分配结果空间，n! 个排列
		size_t fact = 1;
		for(int i = 2; i <= n; ++i)
			fact *= i;
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

int main() {
	Solution2 sol;
	vector<int> vec;
	cout << sol.permute(vec = { 1, 2, 3, 4 });
}