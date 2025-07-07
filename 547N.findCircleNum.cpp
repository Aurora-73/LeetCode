// Created: 2025-07-06
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 547. 省份数量
有 n 个城市，其中一些彼此相连，另一些没有相连。
如果城市 a 与城市 b 直接相连，且城市 b 与城市 c 直接相连，那么城市 a 与城市 c 间接相连。
省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。
给你一个 n x n 的矩阵 isConnected，其中 isConnected{i}{j} = 1 表示第 i 个城市和第 j 个城市直接相连，
而 isConnected{i}{j} = 0 表示二者不直接相连。
返回矩阵中 省份 的数量。
示例 1：
	输入：isConnected = {{1,1,0},{1,1,0},{0,0,1}}
	输出：2
示例 2：
	输入：isConnected = {{1,0,0},{0,1,0},{0,0,1}}
	输出：3
提示：
	1 <= n <= 200
	n == isConnected.length
	n == isConnected{i}.length
	isConnected{i}{j} 为 1 或 0
	isConnected{i}{i} == 1
	isConnected{i}{j} == isConnected{j}{i} */

class Solution1 {
public:
	int findCircleNum(vector<vector<int>> &isConnected) {
		n = isConnected.size();
		int cnt = 0;
		vector<int> visited(n);
		for(int i = 0; i < n; ++i) {
			if(!visited[i]) {
				dfs(isConnected, visited, i);
				++cnt;
			}
		}
		return cnt;
	}

private:
	int n;
	void dfs(vector<vector<int>> &isConnected, vector<int> &visited, int now) {
		visited[now] = true;
		for(int i = 0; i < n; ++i) {
			if(!visited[i] && isConnected[now][i]) {
				dfs(isConnected, visited, i);
			}
		}
	}
}; // DFS 解法

class Solution2 {
public:
	int findCircleNum(vector<vector<int>> &isConnected) {
		int n = isConnected.size(), cnt = 0;
		vector<int> visited(n);
		queue<int> q;
		for(int i = 0; i < n; ++i) {
			if(!visited[i]) {
				q.push(i);
				visited[i] = true;
				++cnt;
			}
			while(!q.empty()) {
				int now = q.front();
				q.pop();
				for(int j = 0; j < n; ++j) {
					if(!visited[j] && isConnected[now][j]) {
						q.push(j);
						visited[j] = true;
					}
				}
			}
		}
		return cnt;
	}
}; // BFS 解法

class Solution3 {
public:
	int findCircleNum(vector<vector<int>> &isConnected) {
		int n = isConnected.size();
		parent = vector<int>(n, -1);
		for(int i = 0; i < n; ++i) {
			for(int j = i + 1; j < n; ++j) { // 只遍历上三角
				if(isConnected[i][j]) {
					Union(i, j);
				}
			}
		}
		return RootCount();
	}

private:
	std::vector<int> parent;
	int RootCount() {
		int res = 0;
		for(auto p : parent)
			if(p < 0) ++res;
		return res;
	}

	int Find(int i) {
		if(parent[i] < 0) return i;
		return parent[i] = Find(parent[i]);
	}

	void Union(int i, int j) {
		int rooti = Find(i), rootj = Find(j);
		if(rooti == rootj) return;
		if(-parent[rooti] > -parent[rootj]) {
			parent[rooti] += parent[rootj];
			parent[rootj] = rooti;
		} else {
			parent[rootj] += parent[rooti];
			parent[rooti] = rootj;
		}
	}
}; // 并查集解法

int main() {
	Solution1 sol1;
	Solution2 sol2;
	Solution3 sol3;
	vector<vector<int>> isConnected;
	isConnected = { { 1, 1, 0 }, { 1, 1, 0 }, { 0, 0, 1 } };
	cout << sol1.findCircleNum(isConnected) << endl; // 2
	cout << sol2.findCircleNum(isConnected) << endl; // 2
	cout << sol3.findCircleNum(isConnected) << endl; // 2

	isConnected = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };
	cout << sol1.findCircleNum(isConnected) << endl; // 3
	cout << sol2.findCircleNum(isConnected) << endl; // 3
	cout << sol3.findCircleNum(isConnected) << endl; // 3
}