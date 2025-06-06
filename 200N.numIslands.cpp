// Created: 2025-05-05
#include "MyUtils.hpp"

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
		int dir2[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } }; // 上下左右四个方向
		for(int d = 0; d < 4; ++d) {
			dfs(grid, i + dir2[d][0], j + dir2[d][1]);
		}
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
							if(x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size()
							    && grid[x][y] == '1') {
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

class UnionFind {
public:
	explicit UnionFind(size_t s) : parent(s, -1), count(s) { }

	// 查找根（带路径压缩）
	size_t Find(size_t i) {
		if(parent[i] < 0) return i;
		return parent[i] = Find(parent[i]);
	}

	// 合并两个集合，返回新根
	size_t Union(size_t i, size_t j) {
		size_t rooti = Find(i), rootj = Find(j);
		if(rooti == rootj) return rooti;

		if(-parent[rooti] > -parent[rootj]) {
			parent[rooti] += parent[rootj];
			parent[rootj] = rooti;
			count--;
			return rooti;
		} else {
			parent[rootj] += parent[rooti];
			parent[rooti] = rootj;
			count--;
			return rootj;
		}
	}

	// 获取集合大小
	int Size() {
		return count;
	}

private:
	std::vector<int> parent;
	int count;
};

class Solution3 {
public:
	int numIslands(vector<vector<char>> &grid) {
		size_t m = grid.size(), n = m ? grid[0].size() : 0;
		UnionFind uf(m * n);
		int dir[2][2] = { { 0, 1 }, { 1, 0 } }, waters = 0;
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				if(grid[i][j] == '0') {
					waters++;
					continue;
				} else {
					for(int k = 0; k < 2; k++) {
						int ii = i + dir[k][0], jj = j + dir[k][1];
						if(ii >= 0 && ii < m && jj >= 0 && jj < n && grid[ii][jj] == '1') {
							uf.Union(i * n + j, ii * n + jj);
						}
					}
				}
			}
		}
		return uf.Size() - waters;
	}
};

int main() {
	Solution1 sol1;
	vector<vector<char>> grid;
	grid = { { '1', '1', '0', '1', '0' },
		{ '1', '1', '0', '0', '0' },
		{ '0', '0', '1', '0', '0' },
		{ '0', '0', '0', '1', '1' } };
	cout << sol1.numIslands(grid) << endl;
	grid = { { '1', '1', '0', '1', '0' },
		{ '1', '1', '0', '0', '0' },
		{ '0', '0', '1', '0', '0' },
		{ '0', '0', '0', '1', '1' } };
	Solution2 sol2;
	cout << sol2.numIslands(grid) << endl;
	grid = { { '1', '1', '0', '1', '0' },
		{ '1', '1', '0', '0', '0' },
		{ '0', '0', '1', '0', '0' },
		{ '0', '0', '0', '1', '1' } };
	Solution3 sol3;
	cout << sol3.numIslands(grid) << endl;
}