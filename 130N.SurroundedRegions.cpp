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

class UnionFindSimple {
public:
	explicit UnionFindSimple(size_t s) : parent(s, -1) { }

	// 路径压缩查找
	size_t Find(size_t i) {
		if(parent[i] < 0)
			return i;
		return parent[i] = Find(parent[i]);
	}

	// 按大小合并两个集合，返回新根
	size_t Union(size_t i, size_t j) {
		size_t ri = Find(i), rj = Find(j);
		if(ri == rj)
			return ri;

		// 负数的绝对值越大，集合越大
		if(-parent[ri] > -parent[rj]) {
			parent[ri] += parent[rj];
			parent[rj] = ri;
			return ri;
		} else {
			parent[rj] += parent[ri];
			parent[ri] = rj;
			return rj;
		}
	}

	// 判断 i、j 是否在同一个集合
	bool Connected(size_t i, size_t j) {
		return Find(i) == Find(j);
	}

	// 返回 i 所在集合的大小
	int Size(size_t i) {
		return -parent[Find(i)];
	}

private:
	vector<int> parent;
};

class Solution3 {
public:
	void solve(vector<vector<char>> &board) {
		size_t m = board.size();
		if(m == 0)
			return;
		size_t n = board[0].size();
		// 多分配一个 dummy 节点，用于收集边界上的 'O'
		size_t total = m * n;
		size_t dummy = total;
		UnionFindSimple uf(total + 1);

		// 四个方向：上、下、左、右
		int dirs[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

		// 1) 合并所有 'O' —— 边界的并到 dummy，内部的与相邻 'O' 并
		for(size_t i = 0; i < m; ++i) {
			for(size_t j = 0; j < n; ++j) {
				if(board[i][j] != 'O')
					continue;
				size_t id = i * n + j;
				// 边界上的 'O' 先并到 dummy
				if(i == 0 || i == m - 1 || j == 0 || j == n - 1) {
					uf.Union(id, dummy);
				}
				// 再与 4 邻域的 'O' 合并
				for(auto &d : dirs) {
					size_t ni = i + d[0], nj = j + d[1];
					if(ni < m && nj < n && board[ni][nj] == 'O') {
						uf.Union(id, ni * n + nj);
					}
				}
			}
		}

		// 2) 翻转所有不与 dummy 连通的 'O'
		for(size_t i = 0; i < m; ++i) {
			for(size_t j = 0; j < n; ++j) {
				if(board[i][j] == 'O' && !uf.Connected(i * n + j, dummy)) {
					board[i][j] = 'X';
				}
			}
		}
	}
}; // 并查集

// 并查集：parent[i]<0 表示 i 是根，且 -parent[i] 为该集合大小
class UnionFind {
public:
	explicit UnionFind(size_t s) : parent(s, -1) { }

	// 路径压缩查找
	size_t Find(size_t i) {
		return parent[i] < 0 ? i : (parent[i] = Find(parent[i]));
	}

	// 按集合大小合并，返回新根
	size_t Union(size_t i, size_t j) {
		size_t ri = Find(i), rj = Find(j);
		if(ri == rj)
			return ri;
		if(-parent[ri] > -parent[rj]) {
			parent[ri] += parent[rj];
			parent[rj] = ri;
			return ri;
		} else {
			parent[rj] += parent[ri];
			parent[ri] = rj;
			return rj;
		}
	}

private:
	vector<int> parent;
};

class Solution {
public:
	void solve(vector<vector<char>> &board) {
		size_t m = board.size();
		if(m == 0)
			return;
		size_t n = board[0].size();
		size_t total = m * n;

		UnionFind uf(total);
		int dirs[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

		// 1) 并查集合并：对每个 'O'，和四邻域的 'O' 做 Union
		for(size_t i = 0; i < m; ++i) {
			for(size_t j = 0; j < n; ++j) {
				if(board[i][j] != 'O')
					continue;
				size_t id = i * n + j;
				for(auto &d : dirs) {
					size_t ni = i + d[0], nj = j + d[1];
					if(ni < m && nj < n && board[ni][nj] == 'O') {
						uf.Union(id, ni * n + nj);
					}
				}
			}
		}

		// 2) 标记所有与边界相连（safe）的根
		vector<bool> safe(total, false);
		// 遍历上下边界
		for(size_t j = 0; j < n; ++j) {
			if(board[0][j] == 'O')
				safe[uf.Find(j)] = true;
			if(board[m - 1][j] == 'O')
				safe[uf.Find((m - 1) * n + j)] = true;
		}
		// 遍历左右边界
		for(size_t i = 0; i < m; ++i) {
			if(board[i][0] == 'O')
				safe[uf.Find(i * n)] = true;
			if(board[i][n - 1] == 'O')
				safe[uf.Find(i * n + n - 1)] = true;
		}

		// 3) 翻转所有不 safe 的 'O' → 'X'
		for(size_t i = 0; i < m; ++i) {
			for(size_t j = 0; j < n; ++j) {
				if(board[i][j] == 'O' && !safe[uf.Find(i * n + j)]) {
					board[i][j] = 'X';
				}
			}
		}
	}
};

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
	board = { { 'X', 'X', 'X', 'X' }, { 'X', 'O', 'O', 'X' }, { 'X', 'X', 'O', 'X' }, { 'X', 'O', 'X', 'X' } };
	Solution3 sol3;
	sol3.solve(board);
	cout << board << endl;
}