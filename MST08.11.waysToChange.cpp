// Created: 2025-12-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 硬币。
给定数量不限的硬币，币值为25分、10分、5分和1分，编写代码计算n分有几种表示法。
(结果可能会很大，你需要将结果模上1000000007)
示例 1：
	输入：n = 5
	输出：2
	解释：有两种方式可以凑成总金额:
        5=5
        5=1+1+1+1+1
示例 2：
	输入：n = 10
	输出：4
	解释：有四种方式可以凑成总金额:
        10=10
        10=5+5
        10=5+1+1+1+1+1
        10=1+1+1+1+1+1+1+1+1+1
你可以假设：
	0 <= n (总金额) <= 1000000 */

class Solution1 {
public:
	int waysToChange(int n) {
		return dfs(n, 0);
	}

private:
	int coins[4] = { 1, 5, 10, 25 };
	int dfs(int i, int j) {
		if(i <= 0 || j > 3) {
			return i == 0;
		}
		return dfs(i, j + 1) + dfs(i - coins[j], j);
	}
};

class Solution2 {
public:
	int waysToChange(int n) {
		vector<vector<int>> dp(5, vector<int>(n + 1));
		int coins[4] = { 1, 5, 10, 25 };
		for(int i = 0; i < 5; ++i) {
			dp[i][0] = 1;
		}
		for(int i = 3; i >= 0; --i) {
			for(int j = 1; j <= n; ++j) {
				dp[i][j] = dp[i + 1][j];
				if(j >= coins[i]) {
					dp[i][j] += dp[i][j - coins[i]];
				}
				dp[i][j] %= 1000000007;
			}
		}
		return dp[0][n];
	}
}; // dp[i][j]：dfs(i, j)，i [0, n], j [0, 4]

class Solution {
public:
	int waysToChange(int n) {
		vector<int> curr(n + 1);
		curr[0] = 1;
		int coins[4] = { 1, 5, 10, 25 };
		for(int i = 3; i >= 0; --i) {
			for(int j = 1; j <= n; ++j) {
				if(j >= coins[i]) {
					curr[j] += curr[j - coins[i]];
				}
				curr[j] %= 1000000007;
			}
		}
		return curr.back();
	}
}; // 滚动数组优化

int main() {
	Solution sol;
	int n;
	n = 5;
	cout << sol.waysToChange(n) << endl;

	n = 10;
	cout << sol.waysToChange(n) << endl;
}