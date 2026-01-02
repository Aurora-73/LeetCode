// Created: 2025-05-23
#include "MyUtils.hpp"

/*64. 最小路径和
给定一个包含非负整数的 m x n 网格 grid
，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
说明：每次只能向下或者向右移动一步。*/
// 从[0][0] 到 [m][n] 向下 i ++ 向右 j++

class Solution1 {
public:
	int minPathSum(vector<vector<int>> &grid) {
		m = grid.size(), n = grid[0].size();
		memo.resize(m, vector<int>(n, numeric_limits<int>::max() >> 3));
		return dfs(grid, 0, 0);
	}

private:
	vector<vector<int>> memo;
	int m, n;
	int dfs(vector<vector<int>> &grid, int i, int j) {
		if(i == m - 1 && j == n - 1) {
			return grid.back().back();
		}
		if(i >= m || j >= n) {
			return numeric_limits<int>::max() >> 3;
		}
		if(memo[i][j] != numeric_limits<int>::max() >> 3) {
			return memo[i][j];
		}
		int next_min = min(dfs(grid, i + 1, j), dfs(grid, i, j + 1));
		memo[i][j] = next_min + grid[i][j];
		return memo[i][j];
	}
};

class Solution {
public:
	int minPathSum(vector<vector<int>> &grid) {
		int m = grid.size(), n = grid[0].size();
		for(int i = m - 2; i >= 0; --i) {
			grid[i][n - 1] += grid[i + 1][n - 1];
		}
		for(int j = n - 2; j >= 0; --j) {
			grid[m - 1][j] += grid[m - 1][j + 1];
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
	vector<vector<int>> grid = { { 1, 3, 1 }, { 1, 5, 1 }, { 4, 2, 1 } };
	cout << sol.minPathSum(grid);
}