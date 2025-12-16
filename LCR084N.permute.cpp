// Created: 2025-12-16
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个不含重复数字的整数数组 nums，返回其 所有可能的全排列。
可以 按任意顺序 返回答案。
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
	vector<vector<int>> permuteUnique(vector<int> &nums) {
		std::sort(nums.begin(), nums.end());
		n = nums.size();
		curr.resize(n); // 用赋值优化插入
		inserted = vector<bool>(n, 0);
		vector<vector<int>> res;
		res.reserve(n);
		dfs(res, 0, nums);
		return res;
	}

private:
	int n;
	vector<int> curr;
	vector<bool> inserted;
	void dfs(vector<vector<int>> &res, int i, const vector<int> &nums) {
		if(i == n) {
			res.push_back(curr);
			return;
		}
		for(int j = 0; j < n; ++j) {
			if(!inserted[j] && (j == 0 || nums[j] != nums[j - 1] || inserted[j - 1])) {
				inserted[j].flip();
				curr[i] = nums[j]; // 用赋值优化插入
				dfs(res, i + 1, nums);
				inserted[j].flip();
			}
		}
	}
}; // 方法1、标记数组法，首选要求相同的元素必须在一起，然后要求相同的元素必须按照顺序插入，也就是说后一个元素和前一个元素一样时，只有插入后一个元素之后才能插入前一个元素，从而避免相同元素的不同插入方式导致重复组合

class Solution {
public:
	vector<vector<int>> permuteUnique(vector<int> &nums) {
		vector<vector<int>> res;
		dfs(0, nums, res);
		return res;
	}

private:
	void dfs(int i, vector<int> &nums, vector<vector<int>> &res) {
		int n = nums.size();
		if(i == n) {
			res.push_back(nums);
			return;
		}

		for(int j = i; j < n; ++j) {
			// 关键：保证 nums[j] 在 [i, j) 中没出现过
			if(isDuplicate(nums, i, j)) continue;

			swap(nums[i], nums[j]);
			dfs(i + 1, nums, res);
			swap(nums[i], nums[j]);
		}
	}

	bool isDuplicate(const vector<int> &nums, int start, int cur) {
		for(int k = start; k < cur; ++k) {
			if(nums[k] == nums[cur]) return true;
		}
		return false;
	}
}; // 方法2、交换元素法，由于此时数组并非静态，因此不能简单的通过和前一个元素比较确定重复，需要跟还未插入区间的全部元素比较，确定是否重复，较为复杂
// 有重复元素则要求相同元素只能"从左到右"使用

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 0, 1, 0, 0, 9 };
	cout << sol.permuteUnique(nums) << endl;
	nums = { 1, 2, 3 };
	cout << sol.permuteUnique(nums) << endl;
	nums = { 0, 1 };
	cout << sol.permuteUnique(nums) << endl;
	nums = { 3, 3, 0, 3 };
	cout << sol.permuteUnique(nums) << endl;
}