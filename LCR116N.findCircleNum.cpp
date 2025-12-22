// Created: 2025-12-22
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 有 n 个城市，其中一些彼此相连，另一些没有相连。
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
		int n = isConnected.size();
		vector<bool> visited(n, false);
		int res = 0;
		for(int i = 0; i < n; ++i) {
			if(!visited[i]) {
				++res;
				dfs(isConnected, visited, i);
			}
		}
		return res;
	}

private:
	void dfs(vector<vector<int>> &isConnected, vector<bool> &visited, int i) {
		visited[i] = true;
		for(int j = 0; j < isConnected.size(); ++j) {
			if(!visited[j] && isConnected[i][j]) {
				dfs(isConnected, visited, j);
			}
		}
	}
};

class Solution {
public:
	int findCircleNum(vector<vector<int>> &isConnected) {
		n = isConnected.size(), mergeCnt = 0;
		parents = vector<int>(n, -1);
		for(int i = 0; i < n; ++i) {
			for(int j = i + 1; j < n; ++j) {
				if(isConnected[i][j]) {
					Union(i, j);
				}
			}
		}
		return n - mergeCnt;
	}

private:
	int n, mergeCnt;
	vector<int> parents;
	int find(int index) {
		if(parents[index] == -1) return index;
		return parents[index] = find(parents[index]);
	}
	void Union(int i, int j) {
		int pi = find(i), pj = find(j);
		if(pi != pj) {
			parents[pi] = pj;
			++mergeCnt;
		}
	}
};

int main() {
	Solution sol;
	vector<vector<int>> isConnected;
	isConnected = { { 1, 1, 0 }, { 1, 1, 0 }, { 0, 0, 1 } };
	cout << sol.findCircleNum(isConnected) << endl;

	isConnected = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };
	cout << sol.findCircleNum(isConnected) << endl;
}