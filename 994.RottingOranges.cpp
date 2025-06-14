// Created: 2025-06-14
#include "MyDateGen.h"
#include "MyUtils.hpp"
#include <list>
// #ifdef MY_UTILS_H

/* 994. 腐烂的橘子
在给定的m x n网格grid中，每个单元格可以有以下三个值之一：
	值0代表空单元格；
	值1代表新鲜橘子；
	值2代表腐烂的橘子。
每分钟，腐烂的橘子周围4 个方向上相邻 的新鲜橘子都会腐烂。
返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回-1。
示例 1：
	输入：grid = {{2,1,1},{1,1,0},{0,1,1}}
	输出：4
示例 2：
	输入：grid = {{2,1,1},{0,1,1},{1,0,1}}
	输出：-1
	解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个方向上。
示例 3：
	输入：grid = {{0,2}}
	输出：0
	解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0。
提示：
	m == grid.length
	n == grid{i}.length
	1 <= m, n <= 10
	grid{i}{j} 仅为0、1或2 */

class Solution1 {
public:
	int orangesRotting(vector<vector<int>> &grid) {
		int times = 0, good = 0, bad = 0;
		unsigned m = grid.size(), n = grid[0].size();
		vector<pair<unsigned, unsigned>> prev;
		for(unsigned i = 0; i < m; ++i) {
			for(unsigned j = 0; j < n; ++j) {
				if(grid[i][j] == 1) ++good;
				if(grid[i][j] == 2) prev.push_back({ i, j });
			}
		}
		vector<pair<unsigned, unsigned>> now;
		while(good > bad) {
			++times;
			for(auto [i, j] : prev) {
				if(i > 0 && grid[i - 1][j] == 1) {
					grid[i - 1][j] = 2;
					now.push_back({ i - 1, j });
					++bad;
				}
				if(i < m - 1 && grid[i + 1][j] == 1) {
					grid[i + 1][j] = 2;
					now.push_back({ i + 1, j });
					++bad;
				}
				if(j > 0 && grid[i][j - 1] == 1) {
					grid[i][j - 1] = 2;
					now.push_back({ i, j - 1 });
					++bad;
				}
				if(j < n - 1 && grid[i][j + 1] == 1) {
					grid[i][j + 1] = 2;
					now.push_back({ i, j + 1 });
					++bad;
				}
			}
			if(now.empty()) {
				return -1;
			}
			prev = std::move(now);
		}
		return times;
	}
};

class Solution {
public:
	int orangesRotting(vector<vector<int>> &grid) {
		int m = grid.size(), n = grid[0].size();
		int fresh = 0, minutes = 0;
		queue<pair<int, int>> q;
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(grid[i][j] == 2)
					q.push({ i, j });
				else if(grid[i][j] == 1)
					++fresh;
			}
		}
		while(!q.empty() && fresh > 0) {
			int sz = q.size();
			for(int i = 0; i < sz; ++i) {
				auto [x, y] = q.front();
				q.pop();
				for(auto [dx, dy] : dirs) {
					int nx = x + dx, ny = y + dy;
					if(nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
						grid[nx][ny] = 2;
						q.push({ nx, ny });
						--fresh;
					}
				}
			}
			++minutes;
		}
		return fresh == 0 ? minutes : -1;
	}

private:
	int dirs[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
}; // 多源广度优先遍历

int main() {
	Solution sol;
	Solution1 sol1;
	vector<vector<int>> grid;

	grid = { { 2, 1, 1 }, { 1, 1, 0 }, { 0, 1, 1 } };
	cout << sol.orangesRotting(grid) << endl; // 4
	grid = { { 2, 1, 1 }, { 1, 1, 0 }, { 0, 1, 1 } };
	cout << sol1.orangesRotting(grid) << endl; // 4

	grid = { { 2, 1, 1 }, { 0, 1, 1 }, { 1, 0, 1 } };
	cout << sol.orangesRotting(grid) << endl; // -1
	grid = { { 2, 1, 1 }, { 0, 1, 1 }, { 1, 0, 1 } };
	cout << sol1.orangesRotting(grid) << endl; // -1

	grid = { { 0, 2 } };
	cout << sol.orangesRotting(grid) << endl; // 0
	grid = { { 0, 2 } };
	cout << sol1.orangesRotting(grid) << endl; // 0
};