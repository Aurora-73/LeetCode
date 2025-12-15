// Created: 2025-12-15
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
示例 1：
	输入:n = 4, k = 2
	输出:
	{
	  {2,4},
	  {3,4},
	  {2,3},
	  {1,2},
	  {1,3},
	  {1,4},
	}
示例 2：
	输入:n = 1, k = 1
	输出: {{1}}
提示：
	1 <= n <= 20
	1 <= k <= n */

class Solution {
public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> res;
		vector<int> curr;
		dfs(res, curr, n, 1, k);
		return res;
	}

private:
	void dfs(vector<vector<int>> &res, vector<int> &curr, int n, int i, unsigned k) {
		if(i > n || curr.size() >= k || n - i + 1 + curr.size() < k) {
			return;
		} // n - i + 1 + curr.size() < k是为了剪枝，就算全取也无法满足，直接舍弃
		curr.push_back(i);
		if(curr.size() == k) {
			res.push_back(curr);
		} else {
			dfs(res, curr, n, i + 1, k);
		}
		curr.pop_back();
		dfs(res, curr, n, i + 1, k);
	}
};

int main() {
	Solution sol;
	int n, k;
	n = 4, k = 2;
	cout << sol.combine(n, k) << endl;
}