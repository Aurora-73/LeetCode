// Created: 2025-06-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 216. 组合总和 III
找出所有相加之和为 n 的 k 个数的组合，且满足下列条件：
	只使用数字1到9
	每个数字最多使用一次
返回 所有可能的有效组合的列表。
该列表不能包含相同的组合两次，组合可以以任何顺序返回。
示例 1:
	输入: k = 3, n = 7
	输出: {{1,2,4}}
	解释:
	1 + 2 + 4 = 7
	没有其他符合的组合了。
示例 2:
	输入: k = 3, n = 9
	输出: {{1,2,6}, {1,3,5}, {2,3,4}}
	解释:
	1 + 2 + 6 = 9
	1 + 3 + 5 = 9
	2 + 3 + 4 = 9
	没有其他符合的组合了。
示例 3:
	输入: k = 4, n = 1
	输出: {}
	解释: 不存在有效的组合。
	在{1,9}范围内使用4个不同的数字，我们可以得到的最小和是1+2+3+4 = 10，因为10 > 1，没有有效的组合。
提示:
	2 <= k <= 9
	1 <= n <= 60 */

class Solution1 {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		res.clear();
		now.clear();
		for(int i = 1; i < 10; ++i) {
			dfs(k, n, i);
		}
		return res;
	}

private:
	vector<vector<int>> res;
	vector<int> now;
	void dfs(int k, int n, int i) {
		now.push_back(i);
		if(k == 1) {
			if(n == i) {
				res.push_back(now);
			}
			now.pop_back();
			return;
		}
		n -= i;
		for(int j = i + 1; j < 10; ++j) {
			if(j <= n) {
				dfs(k - 1, n, j);
			}
		}
		now.pop_back();
	}
};

class Solution2 {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		res.clear();
		now.clear();
		dfs(k, n, 1);
		return res;
	}

private:
	vector<vector<int>> res;
	vector<int> now;
	void dfs(int k, int n, int i) {
		if(!k) {
			if(!n) {
				res.push_back(now);
			}
			return;
		}
		for(int j = i; j < 10; ++j) {
			if(j <= n) {
				now.push_back(j);
				dfs(k - 1, n - j, j + 1);
				now.pop_back();
			}
		}
	}
};

class Solution {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		res.clear();
		now.clear();
		dfs(k, n, 1);
		return res;
	}

private:
	vector<vector<int>> res;
	vector<int> now;

	// 计算区间 [a, a+1, ..., a+cnt-1] 的和
	int sum_min(int a, int cnt) {
		return (2 * a + cnt - 1) * cnt / 2;
	}
	// 计算区间 [9, 9-1, ..., 9-cnt+1] 的和
	int sum_max(int cnt) {
		return (2 * 9 - cnt + 1) * cnt / 2;
	}

	void dfs(int k, int n, int i) {
		// 剪枝1：最小可选和都 > n
		if(k > 0 && sum_min(i, k) > n) return;
		// 剪枝2：最大可选和都 < n
		if(k > 0 && sum_max(k) < n) return;

		if(k == 0) {
			if(n == 0) res.push_back(now);
			return;
		}

		for(int j = i; j <= 9; ++j) {
			if(j > n) break; // 再选更大的 j 肯定超过 n

			// // 前文
			now.push_back(j);
			dfs(k - 1, n - j, j + 1);
			now.pop_back();
			// // 后文
		}
	}
};

int main() {
	Solution sol;
	int k = 3, n = 7;
	cout << sol.combinationSum3(k, n) << endl; // {{1,2,4}}
	k = 3, n = 9;
	cout << sol.combinationSum3(k, n) << endl; // {{1,2,6}, {1,3,5}, {2,3,4}}
	k = 4, n = 1;
	cout << sol.combinationSum3(k, n) << endl; // { }
}