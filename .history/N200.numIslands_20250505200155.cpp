// Created: 2025-05-05
#include "MyUtils.h"

/*200. 岛屿数量
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。*/

class Solution {
public:
	int numIslands(vector<vector<char>> &grid) {
		int count = 0;
		for(int i = 0; i < grid.size(); ++i) {
			for(int j = 0; j < grid[0].size(); ++j) {
				if(grid[i][j] == '1') {
					dfs(grid, i, j);
					count++;
				}
			}
		}
		return count;
	}
	void dfs(vector<vector<char>> &grid, int i, int j) {
		if(i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == '0') {
			return;
		}
		grid[i][j] = '0';
		int dir[3] = { -1, 0, 1 };
		for(auto a : dir) {
			for(auto b : dir) {
				if(!(a == 0 && b == 0)) {
					dfs(grid, i + a, j + b);
				}
			}
		}
	}
};

int main() {
	Solution sol;
	vector<vector<char>> grid = { { '1', '1', '0', '0', '0' },
		{ '1', '1', '0', '0', '0' },
		{ '0', '0', '1', '0', '0' },
		{ '0', '0', '0', '1', '1' } };
	cout << sol.numIslands(grid);
}