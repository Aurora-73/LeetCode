// Created: 2025-06-27
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 129. 字母迷宫
字母迷宫游戏初始界面记作 m x n 二维字符串数组 grid，请判断玩家是否能在 grid 中找到目标单词 target。
注意：寻找单词时 必须 按照字母顺序，通过水平或垂直方向相邻的单元格内的字母构成，同时，同一个单元格内的字母不允许被重复使用。
示例 1：
	输入：grid = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, target = 'ABCCED'
	输出：true
示例 2：
	输入：grid = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, target = 'SEE'
	输出：true
示例 3：
	输入：grid = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, target = 'ABCB'
	输出：false
提示：
	m == grid.length
	n = grid{i}.length
	1 <= m, n <= 6
	1 <= target.length <= 15
	grid 和 target 仅由大小写英文字母组成 */

class Solution {
public:
	bool wordPuzzle(vector<vector<char>> &grid, string &target) {
		if(grid.empty()) return false;
		end = target.end();
		m = grid.size(), n = grid[0].size();
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(grid[i][j] == target[0]) {
					grid[i][j] = '!';
					if(dfs(grid, target.begin() + 1, i, j)) {
						return true;
					}
					grid[i][j] = target[0];
				}
			}
		}
		return false;
	}

private:
	int m, n;
	string::iterator end;
	int dirs[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
	bool dfs(vector<vector<char>> &grid, string::iterator now, int i, int j) {
		if(now == end) return true;
		char val = grid[i][j];
		grid[i][j] = '!';
		for(auto dir : dirs) {
			int ii = i + dir[0], jj = j + dir[1];
			if(ii >= 0 && jj >= 0 && ii < m && jj < n && grid[ii][jj] == *now) {
				if(dfs(grid, now + 1, ii, jj)) return true;
			}
		}
		grid[i][j] = val;
		return false;
	} // 进入时当前位置已经匹配成功，now已经后移
};

class Solution {
public:
	bool wordPuzzle(vector<vector<char>> &grid, string &target) {
		if(grid.empty()) return false;
		end = target.end();
		m = grid.size(), n = grid[0].size();
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(dfs(grid, target.begin(), i, j)) {
					return true;
				}
			}
		}
		return false;
	}

private:
	int m, n;
	string::iterator end;
	int dirs[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
	bool dfs(vector<vector<char>> &grid, string::iterator now, int i, int j) {
		if(i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != *now) {
			return false;
		}
		if(++now == end) return true;
		char val = grid[i][j];
		grid[i][j] = '!';
		for(auto dir : dirs) {
			if(dfs(grid, now, i + dir[0], j + dir[1])) {
				return true;
			}
		}
		grid[i][j] = val;
		return false;
	} // 进入时当前位置还没有匹配成功
};

int main() {
	Solution sol;
	vector<vector<char>> grid;
	string target;
	grid = { { 'A', 'B', 'C', 'E' }, { 'S', 'F', 'C', 'S' }, { 'A', 'D', 'E', 'E' } };
	target = "ABCCED";
	cout << sol.wordPuzzle(grid, target) << endl; // 1
	grid = { { 'A', 'B', 'C', 'E' }, { 'S', 'F', 'C', 'S' }, { 'A', 'D', 'E', 'E' } };
	target = "SEE";
	cout << sol.wordPuzzle(grid, target) << endl; // 1
	grid = { { 'A', 'B', 'C', 'E' }, { 'S', 'F', 'C', 'S' }, { 'A', 'D', 'E', 'E' } };
	target = "ABCB";
	cout << sol.wordPuzzle(grid, target) << endl; // 0
}