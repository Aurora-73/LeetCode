// Created: 2025-12-25
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 节点间通路。
给定有向图，设计一个算法，找出两个节点之间是否存在一条路径。
示例 1：
	输入：n = 3, graph = {{0, 1}, {0, 2}, {1, 2}, {1, 2}}, start = 0, target = 2
	输出：true
示例 2：
	输入：n = 5, graph = {{0, 1}, {0, 2}, {0, 4}, {0, 4}, {0, 1}, {1, 3}, {1, 4}, {1, 3}, {2, 3}, {3, 4}}, start = 0, target = 4
	输出：true
提示：
	节点数量n在{0, 1e5}范围内。
	节点编号大于等于 0 小于 n。
	图中可能存在自环和平行边。 */

// class Solution {
// public:
// 	bool findWhetherExistsPath(int n, vector<vector<int>> &graph, int start, int target) {
// 		parent.assign(n, -1);
// 		for(auto &vec : graph) {
// 			Union(vec[0], vec[1]);
// 		}
// 		return Find(start) == Find(target);
// 	}

// private:
// 	vector<int> parent;
// 	int Find(int index) {
// 		if(parent[index] == -1) return index;
// 		return parent[index] = Find(parent[index]);
// 	}
// 	void Union(int a, int b) {
// 		int pa = Find(a), pb = Find(b);
// 		if(pa != pb) {
// 			parent[pa] = pb;
// 		}
// 	}
// }; // 有向图不能用并查集

class Solution1 {
public:
	bool findWhetherExistsPath(int n, vector<vector<int>> &graph, int start, int target) {
		edges = vector<vector<int>>(n);
		for(auto &vec : graph) {
			edges[vec[0]].push_back(vec[1]);
		}
		vector<bool> visited(n, false);
		return dfs(start, target, visited);
	}

private:
	vector<vector<int>> edges;
	bool dfs(int start, int target, vector<bool> &visited) {
		if(target == start) return 1;
		visited[start] = 1;
		for(auto v : edges[start]) {
			if(!visited[v]) {
				if(dfs(v, target, visited)) {
					return true;
				}
			}
		}
		return false;
	}
};

class Solution {
public:
	bool findWhetherExistsPath(int n, vector<vector<int>> &graph, int start, int target) {
		if(start == target) return true;
		vector<vector<int>> edges = vector<vector<int>>(n);
		for(auto &vec : graph) {
			edges[vec[0]].push_back(vec[1]);
		}
		vector<bool> visited(n, false);
		queue<int> que;
		que.push(start);
		visited[start] = 1;
		while(!que.empty()) {
			int curr = que.front();
			que.pop();
			for(auto v : edges[curr]) {
				if(!visited[v]) {
					if(v == target) return true;
					visited[v] = 1;
					que.push(v);
				}
			}
		}
		return false;
	}
};

int main() {
	Solution sol;
	int n, start, target;
	vector<vector<int>> graph;

	n = 4, graph = { { 0, 1 }, { 0, 2 }, { 1, 2 }, { 2, 0 }, { 3, 2 } }, start = 0, target = 3;
	cout << sol.findWhetherExistsPath(n, graph, start, target) << endl;

	n = 3, graph = { { 0, 1 }, { 0, 2 }, { 1, 2 }, { 1, 2 } }, start = 0, target = 2;
	cout << sol.findWhetherExistsPath(n, graph, start, target) << endl;

	n = 5,
	graph = { { 0, 1 },
		{ 0, 2 },
		{ 0, 4 },
		{ 0, 4 },
		{ 0, 1 },
		{ 1, 3 },
		{ 1, 4 },
		{ 1, 3 },
		{ 2, 3 },
		{ 3, 4 } },
	start = 0, target = 4;
	cout << sol.findWhetherExistsPath(n, graph, start, target) << endl;
}