// Created: 2025-12-19
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个由 0 和 1 组成的矩阵 mat，请输出一个大小相同的矩阵，其中每一个格子是 mat 中对应位置元素到最近的 0 的距离。
两个相邻元素间的距离为 1。
示例 1：
	输入：mat = {{0,0,0},{0,1,0},{0,0,0}}
	输出：{{0,0,0},{0,1,0},{0,0,0}}
示例 2：
	输入：mat = {{0,0,0},{0,1,0},{1,1,1}}
	输出：{{0,0,0},{0,1,0},{1,2,1}}
提示：
	m == mat.length
	n == mat{i}.length
	1 <= m, n <= 10^4
	1 <= m * n <= 10^4
	mat{i}{j} is either 0 or 1.
	mat 中至少有一个 0 */

class Solution1 {
public:
	vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
		int m = mat.size(), n = mat[0].size();
		vector<vector<int>> res(m, vector<int>(n, INT_MAX >> 1));
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(mat[i][j] == 0) res[i][j] = 0;
			}
		}
		bool changed = true;
		int dirs[4][2] { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
		while(changed) {
			changed = false;
			for(int i = 0; i < m; ++i) {
				for(int j = 0; j < n; ++j) {
					int temp = res[i][j];
					for(auto &dir : dirs) {
						int ii = i + dir[0], jj = j + dir[1];
						if(ii >= 0 && ii < m && jj >= 0 && jj < n) {
							temp = min(temp, res[ii][jj] + 1);
						}
					}
					if(res[i][j] != temp) {
						changed = true;
						res[i][j] = temp;
					}
				}
			}
		}
		return res;
	}
}; // 反复松弛（Bellman-Ford 风格）：利用周围4格的值进行更新，直到无法更新，最坏时间复杂度O((mn)^2)

class Solution2 {
public:
	vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
		int m = mat.size(), n = mat[0].size();
		vector<vector<int>> res(m, vector<int>(n, INT_MAX));
		queue<pair<int, int>> que; // 必须用queue，因为后面不同层的会混在一起
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(mat[i][j] == 0) {
					res[i][j] = 0;
					que.emplace(i, j);
				}
			}
		}
		int depth = 1, dirs[4][2] { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
		while(!que.empty()) {
			int size = que.size();
			for(int k = 0; k < size; ++k) {
				auto [i, j] = que.front();
				que.pop();
				for(int (&dir)[2] : dirs) {
					int ii = i + dir[0], jj = j + dir[1];
					if(ii >= 0 && ii < m && jj >= 0 && jj < n) {
						if(res[ii][jj] == INT_MAX) {
							res[ii][jj] = depth;
							que.emplace(ii, jj);
						}
					}
				}
			}
			++depth;
		}
		return res;
	}
}; // 多源BFS：在普通BFS的基础上同时入队全部的0，时间复杂度O(mn)

class Solution {
public:
	vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
		constexpr int INFVAL = INT_MAX >> 1; // 防溢出
		int m = mat.size(), n = mat[0].size();
		vector<vector<int>> dp(m, vector<int>(n, INFVAL));
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(mat[i][j] == 0) dp[i][j] = 0;
			}
		}
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(i > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
				if(j > 0) dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
			}
		}
		for(int i = m - 1; i >= 0; --i) {
			for(int j = n - 1; j >= 0; --j) {
				if(i < m - 1) dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
				if(j < n - 1) dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
			}
		}
		return dp;
	}
}; // 本质是动态规划：dp[i][j] = min(dp[i - 1][j], dp[i + 1][j], dp[i][j - 1], dp[i][j + 1]) + 1，但是不能只扫描一遍
// 因此需要两次扫描，时间复杂度O(mn)。两次扫描已经足够，因为：
// 任意一条最短路径，总可以分解成：先往上/左走 + 再往下/右走（或反过来）
// 第一遍保证考虑了所有 上/左方向传播的最优解，第二遍在此基础上，再修正 下/右方向带来的更优解

int main() {
	Solution sol;
	vector<vector<int>> mat;

	mat = { { 1, 0, 1, 1, 0, 0, 1, 0, 0, 1 },
		{ 0, 1, 1, 0, 1, 0, 1, 0, 1, 1 },
		{ 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
		{ 1, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
		{ 0, 1, 0, 1, 1, 0, 0, 0, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 1, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 0, 1, 0 },
		{ 1, 1, 1, 1, 0, 1, 0, 0, 1, 1 } };
	cout << sol.updateMatrix(mat) << endl;

	mat = { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 } };
	cout << sol.updateMatrix(mat) << endl;

	mat = { { 0, 0, 0 }, { 0, 1, 0 }, { 1, 1, 1 } };
	cout << sol.updateMatrix(mat) << endl;
}