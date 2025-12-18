// Created: 2025-12-18
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个包含非负整数的 mxn网格grid，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
说明：一个机器人每次只能向下或者向右移动一步。
示例 1：
	输入：grid = {{1,3,1},{1,5,1},{4,2,1}}
	输出：7
	解释：因为路径 1→3→1→1→1 的总和最小。
示例 2：
	输入：grid = {{1,2,3},{4,5,6}}
	输出：12
提示：
	m == grid.length
	n == grid{i}.length
	1 <= m, n <= 200
	0 <= grid{i}{j} <= 100 */

class Solution1 {
public:
	int minPathSum(vector<vector<int>> &grid) {
		int m = grid.size(), n = grid[0].size();
		vector<vector<int>> dp(m, vector<int>(n, 0));
		dp.back().back() = grid.back().back();
		for(int i = m - 2; i >= 0; --i) {
			dp[i].back() = dp[i + 1].back() + grid[i].back();
		}
		for(int j = n - 2; j >= 0; --j) {
			dp.back()[j] = dp.back()[j + 1] + grid.back()[j];
		}
		for(int i = m - 2; i >= 0; --i) {
			for(int j = n - 2; j >= 0; --j) {
				dp[i][j] = min(dp[i + 1][j], dp[i][j + 1]) + grid[i][j];
			}
		}
		return dp[0][0];
	}
};

class Solution2 {
public:
	int minPathSum(vector<vector<int>> &grid) {
		int m = grid.size(), n = grid[0].size();
		vector<int> dp(n, 0);
		dp[n - 1] = grid[m - 1][n - 1];
		for(int j = n - 2; j >= 0; --j) {
			dp[j] = dp[j + 1] + grid[m - 1][j];
		}
		for(int i = m - 2; i >= 0; --i) {
			dp[n - 1] = dp[n - 1] + grid[i][n - 1];
			for(int j = n - 2; j >= 0; --j) {
				dp[j] = min(dp[j], dp[j + 1]) + grid[i][j];
			}
		}
		return dp[0];
	}
};

class Solution {
public:
	int minPathSum(vector<vector<int>> &grid) {
		int m = grid.size(), n = grid[0].size();
		for(int i = m - 2; i >= 0; --i) {
			grid[i].back() += grid[i + 1].back();
		}
		for(int j = n - 2; j >= 0; --j) {
			grid.back()[j] += grid.back()[j + 1];
		}
		for(int i = m - 2; i >= 0; --i) {
			for(int j = n - 2; j >= 0; --j) {
				grid[i][j] += min(grid[i + 1][j], grid[i][j + 1]);
			}
		}
		return grid[0][0];
	}
};

int main() {
	Solution sol;
	vector<vector<int>> grid;
	grid = { { 1, 3, 1 }, { 1, 5, 1 }, { 4, 2, 1 } };
	cout << sol.minPathSum(grid) << endl; // 7
	grid = { { 1, 2, 3 }, { 4, 5, 6 } };
	cout << sol.minPathSum(grid) << endl; // 12
}