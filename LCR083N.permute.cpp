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
	vector<vector<int>> permute(vector<int> &nums) {
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
			if(!inserted[j]) {
				inserted[j].flip();
				curr[i] = nums[j]; // 用赋值优化插入
				dfs(res, i + 1, nums);
				inserted[j].flip();
			}
		}
	}
}; // 方法1、标记数组法，每次加入一个元素，当到达指定长度加入结果，每次递归都要插入元素，插入时需要从inserted中查找还没插入过的元素
// 全排列不是选或不选，每次回朔的时候都要插入一个元素

class Solution {
public:
	vector<vector<int>> permute(vector<int> &nums) {
		n = nums.size();
		curr.resize(n); // 用赋值优化插入
		vector<vector<int>> res;
		res.reserve(n);
		dfs(res, 0, nums);
		return res;
	}

private:
	int n;
	vector<int> curr;
	void dfs(vector<vector<int>> &res, int i, vector<int> &nums) {
		if(i == n) {
			res.push_back(curr);
			return;
		}
		for(int j = i; j < n; ++j) {
			swap(nums[i], nums[j]);
			curr[i] = nums[i]; // 用赋值优化插入
			dfs(res, i + 1, nums);
			swap(nums[i], nums[j]);
		}
	}
}; // 方法2、交换元素法，维持一个下标i，i之前的元素都是已经插入过的，i之后的元素都是未插入的，因此某个元素后需要将其与i换位，维持单侧已插入性

// 方法1的结果是按照字典序的，方法2的结果不是按照字典序的

int main() {
	Solution sol;
	vector<int> nums;
	nums = { 1, 2, 3 };
	cout << sol.permute(nums) << endl;
	nums = { 0, 1 };
	cout << sol.permute(nums) << endl;
	nums = { 1 };
	cout << sol.permute(nums) << endl;
}