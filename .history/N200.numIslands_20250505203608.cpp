// Created: 2025-05-05
#include "MyUtils.h"

/*200. 岛屿数量
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。*/

class Solution1 {
public:
	int numIslands(vector<vector<char>> &grid) {
		int count = 0;
		for(int i = 0; i < grid.size(); ++i) {
			for(int j = 0; j < grid[0].size(); ++j) {
				if(grid[i][j] == '1') { // 只有当前单元格是陆地时才进行DFS
					dfs(grid, i, j);
					count++;
				}
			}
		}
		return count;
	}

private:
	void dfs(vector<vector<char>> &grid, int i, int j) {
		if(i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == '0') {
			return;
		}
		grid[i][j] = '0';
		int dir[3] = { -1, 0, 1 };
		for(auto a : dir) {
			for(auto b : dir) {
				if(abs(a) + abs(b) == 1) { // 只能由水平方向和/或竖直方向上相邻的陆地连接形成
					dfs(grid, i + a, j + b);
				}
			}
		}
		// int dir2[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; // 上下左右四个方向
		// for (int d = 0; d < 4; ++d) {
		//     dfs(grid, i + dir2[d][0], j + dir2[d][1]);
		// }
	}
}; // BFS 深度优先便利

class Solution2 {
public:
	int numIslands(vector<vector<char>> &grid) {
		int count = 0;
		for(int i = 0; i < grid.size(); ++i) {
			for(int j = 0; j < grid[0].size(); ++j) {
				if(grid[i][j] == '1') {
					count++;
					queue<pair<int, int>> q;
					q.emplace(i, j);
					grid[i][j] = '0'; // 入队前标记
					while(!q.empty()) {
						int a = q.front().first, b = q.front().second;
						q.pop();
						int dir[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
						for(int d = 0; d < 4; ++d) {
							int x = a + dir[d][0], y = b + dir[d][1]; // 不重复声明太长了
							if(x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == '1') {
								grid[x][y] = '0'; // 入队前标记，入队之后标记会导致重复访问
								q.emplace(x, y);
							}
						}
					}
				}
			}
		}
		return count;
	}
}; // DFS 广度优先遍历

int main() {
	Solution1 sol1;
	vector<vector<char>> grid = { { '1', '1', '0', '0', '0' },
		{ '1', '1', '0', '0', '0' },
		{ '0', '0', '1', '0', '0' },
		{ '0', '0', '0', '1', '1' } };
	cout << sol1.numIslands(grid) << endl;
	cout << sol1.numIslands(grid) << endl;
}