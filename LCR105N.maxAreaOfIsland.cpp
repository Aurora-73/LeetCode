// Created: 2025-12-19
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个由0 和 1 组成的非空二维数组grid，用来表示海洋岛屿地图。
一个岛屿是由一些相邻的1(代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在水平或者竖直方向上相邻。
你可以假设grid 的四个边缘都被 0（代表水）包围着。
找到给定的二维数组中最大的岛屿面积。如果没有岛屿，则返回面积为 0。
示例 1：
	输入: grid = {{0,0,1,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,1,0,0},{0,1,0,0,1,1,0,0,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,0,0,0,0,0,0,1,1,0,0,0,0}}
	输出: 6
	解释: 对于上面这个给定矩阵应返回6。注意答案不应该是 11，因为岛屿只能包含水平或垂直的四个方向的 1。
示例 2：
	输入: grid = {{0,0,0,0,0,0,0,0}}
	输出: 0
提示：
	m == grid.length
	n == grid{i}.length
	1 <= m, n <= 50
	grid{i}{j} is either 0 or 1 */

class Solution {
public:
	int maxAreaOfIsland(vector<vector<int>> &grid) {
		m = grid.size(), n = grid[0].size();
		int res = 0;
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(grid[i][j]) {
					res = max(res, dfs(grid, i, j));
				}
			}
		}
		return res;
	}

private:
	int m, n;
	inline static constexpr std::array<std::array<int, 2>, 4> dirs {
		{ { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } }
	};
	int dfs(vector<vector<int>> &grid, int i, int j) {
		if(i < 0 || j < 0 || i >= m || j >= n || !grid[i][j]) {
			return 0;
		}
		int res = 1;
		grid[i][j] = 0;
		for(auto &dir : dirs) {
			res += dfs(grid, i + dir[0], j + dir[1]);
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> grid;
	grid = { { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
		{ 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0 },
		{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 } };
	cout << sol.maxAreaOfIsland(grid) << endl;
	grid = { { 0, 0, 0, 0, 0, 0, 0, 0 } };
	cout << sol.maxAreaOfIsland(grid) << endl;
}