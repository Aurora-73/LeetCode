// Created: 2025-05-05
#include "MyUtils.h"

/*130. 被围绕的区域
给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' 组成，捕获 所有 被围绕的区域：
连接：一个单元格与水平或垂直方向上相邻的单元格连接。
区域：连接所有 'O' 的单元格来形成一个区域。
围绕：如果您可以用 'X' 单元格 连接这个区域，并且区域中没有任何单元格位于 board 边缘，则该区域被 'X' 单元格围绕。
通过 原地 将输入矩阵中的所有 'O' 替换为 'X' 来 捕获被围绕的区域。你不需要返回任何值。*/

class Solution1 {
public:
	void solve(vector<vector<char>> &board) {
		int m = board.size(), n = board[0].size();
		for(int i = 0; i < m; i++) {
			dfs(board, i, 0);
			dfs(board, i, n - 1);
		}
		for(int j = 0; j < n; j++) {
			dfs(board, 0, j);
			dfs(board, m - 1, j);
		}
		for(auto &s : board) {
			for(auto &c : s) {
				if(c == 'N') {
					c = 'O';
				} else if(c == 'O') {
					c = 'X';
				}
			}
		}
	}
	void dfs(vector<vector<char>> &board, int a, int b) {
		if(a < 0 || b < 0 || a >= board.size() || b >= board[0].size() || board[a][b] != 'O') {
			return;
		}
		board[a][b] = 'N';
		int dirs[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
		for(auto &dir : dirs) {
			dfs(board, a + dir[0], b + dir[1]);
		}
	}
};

class Solution2 {
public:
	void solve(vector<vector<char>> &board) {
		int m = board.size(), n = board[0].size();
		for(int i = 0; i < m; i++) {
			bfs(board, i, 0);
			bfs(board, i, n - 1);
		}
		for(int j = 0; j < n; j++) {
			bfs(board, 0, j);
			bfs(board, m - 1, j);
		}
		for(auto &s : board) {
			for(auto &c : s) {
				if(c == 'N') {
					c = 'O';
				} else if(c == 'O') {
					c = 'X';
				}
			}
		}
	}
	void bfs(vector<vector<char>> &board, int i, int j) {
		if(board[i][j] != 'O')
			return; // 上面不检查下面就要检查
		queue<pair<int, int>> q;
		q.emplace(i, j);
		board[i][j] = 'N';
		int dirs[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
		while(!q.empty()) {
			i = q.front().first;
			j = q.front().second;
			q.pop();
			for(auto &dir : dirs) {
				int a = i + dir[0], b = j + dir[1];
				if(a < 0 || b < 0 || a >= board.size() || b >= board[0].size() || board[a][b] != 'O') {
					continue;
				}
				q.emplace(a, b);
				board[a][b] = 'N';
			}
		}
	}
};

// 缺少并查集

int main() {
	Solution1 sol1;
	vector<vector<char>> board;
	board = { { 'X', 'X', 'X', 'X' }, { 'X', 'O', 'O', 'X' }, { 'X', 'X', 'O', 'X' }, { 'X', 'O', 'X', 'X' } };
	sol1.solve(board);
	cout << board << endl;
	board = { { 'X', 'X', 'X', 'X' }, { 'X', 'O', 'O', 'X' }, { 'X', 'X', 'O', 'X' }, { 'X', 'O', 'X', 'X' } };
	Solution2 sol2;
	sol2.solve(board);
	cout << board << endl;
}