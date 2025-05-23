// Created: 2025-05-23
#include "MyUtils.h"

/*120. 三角形最小路径和
给定一个三角形 triangle ，找出自顶向下的最小路径和。
每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于
上一层结点下标 + 1 的两个结点。 也就是说，如果正位于当前行的下标 j
，那么下一步可以移动到下一行的下标 j 或 j + 1 。*/

class Solution1 {
public:
	int minimumTotal(vector<vector<int>> &triangle) {
		return dfs(triangle, 0, 0);
	}

private:
	int dfs(vector<vector<int>> &triangle, int i, int j) {
		if(i >= triangle.size() || j >= triangle[i].size() || j < 0) {
			return 0;
		}
		int now = triangle[i][j];
		return now + min(dfs(triangle, i + 1, j), dfs(triangle, i + 1, j + 1));
	}
}; // 递归暴力解法，从顶点(0,0)出发，递归计算所有路径的和，返回最小值

class Solution2 {
public:
	int minimumTotal(vector<vector<int>> &triangle) {
		memo.resize(triangle.size());
		for(int i = 0; i < triangle.size(); ++i) {
			memo[i].resize(triangle[i].size(), INT_MIN);
		}
		return dfs(triangle, 0, 0);
	}

private:
	vector<vector<int>> memo;
	int dfs(vector<vector<int>> &triangle, int i, int j) {
		if(i >= triangle.size() || j >= triangle[i].size() || j < 0) {
			return 0;
		}
		if(memo[i][j] != INT_MIN) {
			return memo[i][j];
		}
		int now = triangle[i][j];
		memo[i][j] = now + min(dfs(triangle, i + 1, j), dfs(triangle, i + 1, j + 1));
		return memo[i][j];
	}
}; // 递归+记忆化搜索，避免重复计算子问题，提高效率

class Solution3 {
public:
	int minimumTotal(vector<vector<int>> &triangle) {
		vector<vector<int>> dp = triangle;
		for(int i = triangle.size() - 2; i >= 0; --i) {
			for(int j = 0; j < triangle[i].size(); ++j) {
				dp[i][j] += min(dp[i + 1][j], dp[i + 1][j + 1]);
			}
		}
		return dp[0][0];
	}
}; // 自底向上动态规划，dp[i][j]表示从(i,j)出发到底部的最小路径和

class Solution4 {
public:
	int minimumTotal(vector<vector<int>> &triangle) {
		vector<int> dp = triangle.back();
		for(int i = triangle.size() - 2; i >= 0; --i) {
			for(int j = 0; j < triangle[i].size(); ++j) {
				dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
			}
		}
		return dp[0];
	}
}; // 空间优化的自底向上动态规划，只用一维数组存储当前行的最小路径和

class Solution {
public:
	int minimumTotal(vector<vector<int>> &triangle) {
		int n = triangle.size();
		for(int i = n - 2; i >= 0; --i) {
			for(int j = 0; j <= i; ++j) {
				triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
			}
		}
		return triangle[0][0];
	}
}; // 空间优化，直接改写 triangle 数组的值

int main() {
	Solution sol;
}