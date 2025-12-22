// Created: 2025-12-22
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个m x n 整数矩阵matrix，找出其中 最长递增路径 的长度。
对于每个单元格，你可以往上，下，左，右四个方向移动。 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）。
示例 1：
	输入：matrix = {{9,9,4},{6,6,8},{2,1,1}}
	输出：4 
	解释：最长递增路径为{1, 2, 6, 9}。
示例 2：
	输入：matrix = {{3,4,5},{3,2,6},{2,2,1}}
	输出：4 
	解释：最长递增路径是{3, 4, 5, 6}。注意不允许在对角线方向上移动。
示例 3：
	输入：matrix = {{1}}
	输出：1
提示：
	m == matrix.length
	n == matrix{i}.length
	1 <= m, n <= 200
	0 <= matrix{i}{j} <= 2^31 - 1 */

class Solution1 {
public:
	int longestIncreasingPath(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size(), res = 1;
		vector<vector<int>> dp(m, vector<int>(n, 1)); // 以dp[i][j]为最小值的递增路径长度
		map<int, vector<pair<int, int>>> mp;
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				mp[matrix[i][j]].emplace_back(i, j);
			}
		}
		int dirs[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
		for(const auto &pair : mp) {
			int val = pair.first;
			for(auto [i, j] : pair.second) {
				int curr = 1;
				for(auto dir : dirs) {
					int ii = i + dir[0], jj = j + dir[1];
					if(ii >= 0 && jj >= 0 && ii < m && jj < n && val > matrix[ii][jj]) {
						curr = max(curr, dp[ii][jj] + 1);
					}
				}
				dp[i][j] = curr;
				res = max(res, curr);
			}
		}
		return res;
	}
}; // 需要按照大小顺序确定长度，应该从小到大填充dp，用map自带的有序性来实现

class Solution2 {
public:
	int longestIncreasingPath(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size(), res = 1;
		vector<vector<int>> dp(m, vector<int>(n, 1)); // 以dp[i][j]为最小值的递增路径长度
		vector<tuple<int, int, int>> vals;
		vals.reserve(m * n);
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				vals.push_back({ matrix[i][j], i, j });
			}
		}
		std::sort(vals.begin(), vals.end());
		int dirs[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
		for(auto [val, i, j] : vals) {
			int curr = 1;
			for(auto dir : dirs) {
				int ii = i + dir[0], jj = j + dir[1];
				if(ii >= 0 && jj >= 0 && ii < m && jj < n && val > matrix[ii][jj]) {
					curr = max(curr, dp[ii][jj] + 1);
				}
			}
			dp[i][j] = curr;
			res = max(res, curr);
		}
		return res;
	}
}; // 有序访问的方式有：1、priority_qeue（最慢）  2、map   3、sort

class Solution3 {
public:
	int longestIncreasingPath(vector<vector<int>> &matrix) {
		m = matrix.size(), n = matrix[0].size(), res = 0;
		memo = vector<vector<int>>(m, vector<int>(n, 0));
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(memo[i][j] == 0) {
					dfs(matrix, i, j);
				}
			}
		}
		return res;
	}

private:
	int res, m, n;
	vector<vector<int>> memo;
	int dirs[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
	void dfs(vector<vector<int>> &matrix, int i, int j) {
		int curr = 1;
		for(auto dir : dirs) {
			int ii = i + dir[0], jj = j + dir[1];
			if(ii >= 0 && jj >= 0 && ii < m && jj < n && matrix[i][j] > matrix[ii][jj]) {
				if(memo[ii][jj] == 0) {
					dfs(matrix, ii, jj);
				}
				curr = max(curr, memo[ii][jj] + 1);
			}
		}
		memo[i][j] = curr;
		res = max(res, curr);
	}
}; // 记忆化DFS，遇到周围的matrix更小，但是memo未定的值就进行递归

class Solution {
public:
	int longestIncreasingPath(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size(), res = 1;
		vector<vector<int>> dp(m, vector<int>(n));
		vector<vector<int>> inDegree(m, vector<int>(n));
		int dirs[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				for(int *dir : dirs) {
					int ii = i + dir[0], jj = j + dir[1];
					if(ii >= 0 && jj >= 0 && ii < m && jj < n && matrix[i][j] > matrix[ii][jj]) {
						++inDegree[i][j];
					}
				}
			}
		}
		queue<pair<int, int>> que;
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(inDegree[i][j] == 0) {
					que.emplace(i, j);
				}
			}
		}
		while(que.size()) {
			auto [i, j] = que.front();
			que.pop();
			int curr = 1;
			for(auto dir : dirs) {
				int ii = i + dir[0], jj = j + dir[1];
				if(ii >= 0 && jj >= 0 && ii < m && jj < n) {
					if(matrix[i][j] > matrix[ii][jj]) {
						curr = max(curr, dp[ii][jj] + 1);
					} else if(matrix[i][j] < matrix[ii][jj]) { // 不是else，相等的不能减小入度
						if(--inDegree[ii][jj] == 0) {
							que.emplace(ii, jj);
						}
					}
				}
			}
			dp[i][j] = curr;
			res = max(res, curr);
		}

		return res;
	}
}; // 拓扑排序，可以起到和前两个解法一样的顺序，且更快一些

int main() {
	Solution sol;
	vector<vector<int>> matrix;

	matrix = { { 13, 5, 13, 9 }, { 5, 0, 2, 9 }, { 10, 13, 11, 10 }, { 0, 0, 13, 13 } };
	cout << sol.longestIncreasingPath(matrix) << endl;

	matrix = { { 9, 9, 4 }, { 6, 6, 8 }, { 2, 1, 1 } };
	cout << sol.longestIncreasingPath(matrix) << endl;

	matrix = { { 3, 4, 5 }, { 3, 2, 6 }, { 2, 2, 1 } };
	cout << sol.longestIncreasingPath(matrix) << endl;

	matrix = { { 1 } };
	cout << sol.longestIncreasingPath(matrix) << endl;
}