// Created: 2025-12-18
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 一个机器人位于一个 m x n网格的左上角 （起始点在下图中标记为 “Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
问总共有多少条不同的路径？
示例 1：
	输入：m = 3, n = 7
	输出：28
示例 2：
	输入：m = 3, n = 2
	输出：3
	解释：
	从左上角开始，总共有 3 条路径可以到达右下角。
	1. 向右 -> 向下 -> 向下
	2. 向下 -> 向下 -> 向右
	3. 向下 -> 向右 -> 向下
示例 3：
	输入：m = 7, n = 3
	输出：28
示例 4：
	输入：m = 3, n = 3
	输出：6
提示：
	1 <= m, n <= 100
	题目数据保证答案小于等于 2 * 10^9 */

class Solution1 {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>> dp(m, vector<int>(n, 1));
		for(int i = m - 2; i >= 0; --i) {
			for(int j = n - 2; j >= 0; --j) {
				dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
			}
		}
		return dp[0][0];
	}
};

class Solution2 {
public:
	int uniquePaths(int m, int n) {
		vector<int> dp(n, 1);
		for(int i = m - 2; i >= 0; --i) {
			for(int j = n - 2; j >= 0; --j) {
				dp[j] = dp[j] + dp[j + 1];
			}
		}
		return dp[0];
	}
};

class Solution {
public:
	int uniquePaths(int m, int n) {
		long long ans = 1;
		for(int x = n, y = 1; y < m; ++x, ++y) {
			ans = ans * x / y;
		}
		return ans;
	}
};

int main() {
	Solution sol;
	int m, n;
	m = 3, n = 7;
	cout << sol.uniquePaths(m, n) << endl; // 28
	m = 3, n = 2;
	cout << sol.uniquePaths(m, n) << endl; // 3
	m = 7, n = 3;
	cout << sol.uniquePaths(m, n) << endl; // 28
}