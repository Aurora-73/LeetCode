// Created: 2025-05-06
#include "MyUtils.h"
#define MaxSize 10
/*对节点进行遍历和对边进行遍历*/

int dfs_arc(vector<vector<int>> &E) {
	size_t R = E.size(), C = R ? E[0].size() : 0;
	vector<vector<bool>> vis(R, vector<bool>(C, false));
	int count = 0;
	constexpr int dirs[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

	// 递归 lambda（无需 std::function 开销，C++14）
	auto dfs = [&](auto &&self, size_t i, size_t j) -> void {
		vis[i][j] = true;
		cout << "(" << i << "," << j << ")";
		for(auto &d : dirs) {
			size_t ni = i + d[0], nj = j + d[1];
			if(ni < R && nj < C && !vis[ni][nj] && E[ni][nj] == 1) {
				self(self, ni, nj);
			}
		}
	};

	for(size_t i = 0; i < R; ++i) {
		for(size_t j = 0; j < C; ++j) {
			if(!vis[i][j] && E[i][j] == 1) {
				++count;
				dfs(dfs, i, j);
			}
		}
	}
	return count;
} // 网格DFS，对边进行遍历，是对二维矩阵的格子进行遍历，检查二维格子连通性，用于连通域计数、迷宫／图像填色、岛屿数等

int dfs_vex(const vector<char> &V, const vector<vector<int>> &G) {
	size_t N = V.size();
	vector<bool> vis(N, false);
	int count = 0;
	// 递归 lambda（std::function 的内部实现会做类型擦除）
	std::function<void(size_t)> dfs = [&](size_t u) {
		for(size_t v = 0; v < N; ++v) {
			if(!vis[v] && G[u][v]) {
				vis[v] = true;
				cout << V[v] << ' ';
				dfs(v);
			}
		}
	};

	for(size_t i = 0; i < N; ++i) {
		if(!vis[i]) {
			++count;
			vis[i] = true;
			cout << V[i] << ' ';
			dfs(i);
			cout << '\n';
		}
	}
	return count;
} // 图DFS，对顶点进行遍历，是对抽象图结构遍历，检查顶点间的连通性，用于图遍历、连通分量、拓扑排序、强连通分量等

int bfs_arc(vector<vector<int>> &E) {
	size_t R = E.size(), C = R ? E[0].size() : 0;
	if(R == 0 || C == 0)
		return 0;
	vector<vector<bool>> vis(R, vector<bool>(C, false));
	constexpr int dirs[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
	int count = 0;
	queue<pair<size_t, size_t>> q;

	for(size_t i = 0; i < R; ++i) {
		for(size_t j = 0; j < C; ++j) {
			if(!vis[i][j] && E[i][j] == 1) {
				// 新的连通块
				++count;
				vis[i][j] = true;
				q.emplace(i, j);
				// 开始 BFS
				while(!q.empty()) {
					auto [x, y] = q.front();
					q.pop();
					cout << "(" << x << "," << y << ")";
					for(auto &d : dirs) {
						size_t nx = x + d[0], ny = y + d[1];
						if(nx < R && ny < C && !vis[nx][ny] && E[nx][ny] == 1) {
							vis[nx][ny] = true;
							q.emplace(nx, ny);
						}
					}
				}
			}
		}
	}
	return count;
}

int bfs_vex(const vector<char> &V, const vector<vector<int>> &G) {
	size_t N = V.size();
	vector<bool> vis(N, false);
	int count = 0;
	queue<size_t> q;
	for(size_t i = 0; i < N; ++i) {
		if(!vis[i]) {
			// 新的连通分量
			++count;
			vis[i] = true;
			q.push(i);
			cout << V[i] << ' ';
			// 开始 BFS
			while(!q.empty()) {
				size_t u = q.front();
				q.pop();
				for(size_t v = 0; v < N; ++v) {
					if(!vis[v] && G[u][v]) {
						vis[v] = true;
						cout << V[v] << ' ';
						q.push(v);
					}
				}
			}
			cout << '\n';
		}
	}
	return count;
}

int main() {
	return 0;
}