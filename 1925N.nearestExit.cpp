// Created: 2025-07-07
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1926. 迷宫中离入口最近的出口
给你一个m x n的迷宫矩阵maze（下标从 0 开始），矩阵中有空格子（用'.'表示）和墙（用'+'表示）。
同时给你迷宫的入口entrance，
用entrance = {entrancerow, entrancecol}表示你一开始所在格子的行和列。
每一步操作，你可以往 上，下，左 或者 右移动一个格子。你不能进入墙所在的格子，你也不能离开迷宫。
你的目标是找到离entrance最近的出口。出口的含义是maze边界上的空格子。entrance格子不算出口。
请你返回从 entrance到最近出口的最短路径的 步数，如果不存在这样的路径，请你返回 -1。
示例 1：
	输入：maze = {{'+','+','.','+'},{'.','.','.','+'},{'+','+','+','.'}}, entrance = {1,2}
	输出：1
	解释：总共有 3 个出口，分别位于 (1,0)，(0,2) 和 (2,3)。
	一开始，你在入口格子 (1,2) 处。
	- 你可以往左移动 2 步到达 (1,0)。
	- 你可以往上移动 1 步到达 (0,2)。
	从入口处没法到达 (2,3)。
	所以，最近的出口是 (0,2)，距离为 1 步。
示例 2：
	输入：maze = {{'+','+','+'},{'.','.','.'},{'+','+','+'}}, entrance = {1,0}
	输出：2
	解释：迷宫中只有 1 个出口，在 (1,2) 处。
	(1,0) 不算出口，因为它是入口格子。
	初始时，你在入口与格子 (1,0) 处。
	- 你可以往右移动 2 步到达 (1,2) 处。
	所以，最近的出口为 (1,2)，距离为 2 步。
示例 3：
	输入：maze = {{'.','+'}}, entrance = {0,0}
	输出：-1
	解释：这个迷宫中没有出口。
提示：
	maze.length == m
	maze{i}.length == n
	1 <= m, n <= 100
	maze{i}{j} 要么是'.'，要么是'+'。
	entrance.length == 2
	0 <= entrancerow < m
	0 <= entrancecol < n
	entrance一定是空格子。 */

class Solution {
public:
	int nearestExit(vector<vector<char>> &maze, vector<int> &entrance) {
		int dirs[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
		int m = maze.size(), n = maze[0].size(), step = 0;
		queue<pair<int, int>> q; // 必须是queue
		q.emplace(entrance[0], entrance[1]);
		maze[entrance[0]][entrance[1]] = '+';
		while(!q.empty()) {
			int size = q.size();
			for(int k = 0; k < size; ++k) {
				auto [i, j] = q.front();
				q.pop();
				for(auto &dir : dirs) {
					int ii = i + dir[0], jj = j + dir[1];
					if(ii >= 0 && ii < m && jj >= 0 && jj < n) {
						if(maze[ii][jj] == '.') {
							q.emplace(ii, jj);
							maze[ii][jj] = '+';
						}
					} else {
						if(step) {
							return step;
						}
					}
				}
			}
			++step;
		}
		return -1;
	}
};

int main() {
	Solution sol;
	vector<int> entrance;
	vector<vector<char>> maze;
	maze = { { '+', '.', '+', '+', '+', '+', '+' },
		{ '+', '.', '+', '.', '.', '.', '+' },
		{ '+', '.', '+', '.', '+', '.', '+' },
		{ '+', '.', '.', '.', '+', '.', '+' },
		{ '+', '+', '+', '+', '+', '.', '+' } },
	entrance = { 0, 1 };
	cout << sol.nearestExit(maze, entrance) << endl; // 12
	maze = { { '+', '+', '.', '+' }, { '.', '.', '.', '+' }, { '+', '+', '+', '.' } },
	entrance = { 1, 2 };
	cout << sol.nearestExit(maze, entrance) << endl; // 1
	maze = { { '+', '+', '+' }, { '.', '.', '.' }, { '+', '+', '+' } }, entrance = { 1, 0 };
	cout << sol.nearestExit(maze, entrance) << endl; // 2
	maze = { { '.', '+' } }, entrance = { 0, 0 };
	cout << sol.nearestExit(maze, entrance) << endl; // -1
}