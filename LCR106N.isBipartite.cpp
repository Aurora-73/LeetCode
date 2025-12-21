// Created: 2025-12-19
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 存在一个 无向图，图中有 n 个节点。
其中每个节点都有一个介于 0 到 n - 1 之间的唯一编号。
给定一个二维数组 graph，表示图，其中 graph{u} 是一个节点数组，由节点 u 的邻接节点组成。形式上，
对于graph{u} 中的每个 v，都存在一条位于节点 u 和节点 v 之间的无向边。该无向图同时具有以下属性：
	不存在自环（graph{u} 不包含 u）。
	不存在平行边（graph{u} 不包含重复值）。
	如果 v 在 graph{u} 内，那么 u 也应该在 graph{v} 内（该图是无向图）
	这个图可能不是连通图，也就是说两个节点 u 和 v 之间可能不存在一条连通彼此的路径。
二分图 定义：如果能将一个图的节点集合分割成两个独立的子集 A 和 B，
并使图中的每一条边的两个节点一个来自 A 集合，一个来自 B 集合，就将这个图称为 二分图。
如果图是二分图，返回 true ；否则，返回 false。
示例 1：
	输入：graph = {{1,2,3},{0,2},{0,1,3},{0,2}}
	输出：false
	解释：不能将节点分割成两个独立的子集，以使每条边都连通一个子集中的一个节点与另一个子集中的一个节点。
示例 2：
	输入：graph = {{1,3},{0,2},{1,3},{0,2}}
	输出：true
	解释：可以将节点分成两组: {0, 2} 和 {1, 3}。
提示：
	graph.length == n
	1 <= n <= 100
	0 <= graph{u}.length < n
	0 <= graph{u}{i} <= n - 1
	graph{u} 不会包含 u
	graph{u} 的所有值 互不相同
	如果 graph{u} 包含 v，那么 graph{v} 也会包含 u */

class Solution {
public:
	bool isBipartite(const vector<vector<int>> &graph) {
		int n = graph.size();
		vector<char> color(n, 0);
		for(int i = 0; i < n; ++i) {
			if(color[i] == 0) {
				color[i] = 1;
				if(!dfs(graph, color, i)) return false;
			}
		}
		return true;
	}

private:
	bool dfs(const vector<vector<int>> &graph, vector<char> &color, int i) {
		for(int j : graph[i]) {
			if(color[j] == 0) {
				color[j] = 3 - color[i];
				if(!dfs(graph, color, j)) return false;
			} else if(color[j] == color[i]) {
				return false;
			}
		}
		return true;
	}
}; // 没有很多的解法，直接用深度/广度优先遍历模拟即可

class Solution2 {
public:
	bool isBipartite(const vector<vector<int>> &graph) {
		int n = graph.size();
		vector<int> color(n, 0);
		stack<int> q;
		for(int i = 0; i < n; ++i) {
			if(color[i] == 0) {
				color[i] = 1;
				q.push(i);
				while(!q.empty()) {
					int u = q.top();
					q.pop();
					for(int v : graph[u]) {
						if(color[v] == 0) {
							color[v] = 3 - color[u];
							q.push(v);
						} else if(color[v] == color[u]) {
							return false;
						}
					}
				}
			}
		}
		return true;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> graph;
	graph = { { 1, 2, 3 }, { 0, 2 }, { 0, 1, 3 }, { 0, 2 } };

	cout << sol.isBipartite(graph) << endl;
	graph = { { 1, 3 }, { 0, 2 }, { 1, 3 }, { 0, 2 } };
	cout << sol.isBipartite(graph) << endl;
}