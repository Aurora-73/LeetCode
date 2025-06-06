// Created: 2025-05-27
#include "MyUtils.hpp"

/*  931. 下降路径最小和
给你一个 n x n 的 方形 整数数组 matrix ，请你找出并返回通过 matrix 的下降路径 的 最小和 。
下降路径 可以从第一行中的任何元素开始，并从每一行中选择一个元素。
在下一行选择的元素和当前行所选元素最多相隔一列（即位于正下方或者沿对角线向左或者向右的第一个元素）。
具体来说，位置 (row, col) 的下一个元素应当是 (row + 1, col - 1)、(row + 1, col) 或者 (row + 1, col + 1) 。*/

class Solution1 {
public:
	int minFallingPathSum(vector<vector<int>> &matrix) {
		m = matrix.size(), n = matrix[0].size();
		memo.resize(m, vector<int>(n, INT_MAX));
		int min_val = INT_MAX >> 6;
		for(int j = 0; j < n; ++j) {
			min_val = min(min_val, dfs(matrix, 0, j));
		}
		return min_val;
	}

private:
	vector<vector<int>> memo;
	int m, n;
	int dfs(vector<vector<int>> &matrix, int i, int j) {
		if(i == m) return 0;
		if(j < 0 || j >= n) return INT_MAX >> 6;
		if(memo[i][j] != INT_MAX) return memo[i][j];
		int min_val = INT_MAX >> 6;
		for(int k = -1; k < 2; ++k) {
			min_val = min(min_val, dfs(matrix, i + 1, j + k));
		}
		memo[i][j] = min_val + matrix[i][j];
		return memo[i][j];
	}
};

class Solution2 {
public:
	int minFallingPathSum(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size();
		auto get_dp = [&](int i, int j) {
			if(j < 0 || j >= n) {
				return INT_MAX;
			}
			return matrix[i][j];
		};
		for(int i = m - 2; i >= 0; --i) {
			for(int j = 0; j < n; ++j) {
				matrix[i][j]
				    += min({ matrix[i + 1][j], get_dp(i + 1, j + 1), get_dp(i + 1, j - 1) });
			}
		}
		int min_val = INT_MAX;
		for(int j = 0; j < n; ++j) {
			min_val = min(min_val, matrix[0][j]);
		}
		return min_val;
	}
};

class Solution {
public:
	int minFallingPathSum(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size();
		vector<int> dp = matrix.back();
		for(int i = m - 2; i >= 0; --i) {
			int prev = INT_MAX;
			for(int j = 0; j < n; ++j) {
				int temp = dp[j];
				dp[j] = min({ dp[j], (j > n - 2) ? INT_MAX : dp[j + 1], prev }) + matrix[i][j];
				prev = temp;
			}
		}
		int min_val = INT_MAX;
		for(int j = 0; j < n; ++j) {
			min_val = min(min_val, dp[j]);
		}
		return min_val;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> matrix = { { 17, 82 }, { 1, -44 } };
	cout << sol.minFallingPathSum(matrix);
}