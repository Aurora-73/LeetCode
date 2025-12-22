// Created: 2025-12-21
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个有n个节点的有向无环图，用二维数组graph表示，请找到所有从0到n-1的路径并输出（不要求按顺序）。
graph的第 i 个数组中的单元都表示有向图中 i号节点所能到达的下一些结点（译者注：有向图是有方向的，
即规定了 a→b 你就不能从 b→a ），若为空，就是没有下一个节点了。
示例 1：
	输入：graph = {{1,2},{3},{3},{}}
	输出：{{0,1,3},{0,2,3}}
	解释：有两条路径 0 -> 1 -> 3 和 0 -> 2 -> 3
示例 2：
	输入：graph = {{4,3,1},{3,2,4},{3},{4},{}}
	输出：{{0,4},{0,3,4},{0,1,3,4},{0,1,2,3,4},{0,1,4}}
示例 3：
	输入：graph = {{1},{}}
	输出：{{0,1}}
示例 4：
	输入：graph = {{1,2,3},{2},{3},{}}
	输出：{{0,1,2,3},{0,2,3},{0,3}}
示例 5：
	输入：graph = {{1,3},{2},{3},{}}
	输出：{{0,1,2,3},{0,3}}
提示：
	n == graph.length
	2 <= n <= 15
	0 <= graph{i}{j} < n
	graph{i}{j} != i
	保证输入为有向无环图 (GAD) */

class Solution {
public:
	vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph) {
		res.clear();
		n = graph.size();
		vector<int> curr {};
		curr.push_back(0);
		dfs(graph, curr, 0);
		return res;
	}

private:
	int n;
	vector<vector<int>> res;
	void dfs(vector<vector<int>> &graph, vector<int> &curr, int i) {
		if(i == n - 1) {
			res.push_back(curr);
			return;
		}
		for(auto j : graph[i]) {
			curr.push_back(j);
			dfs(graph, curr, j);
			curr.pop_back();
		}
		return;
	}
}; // 直接用DFS遍历即可，因为是有向无环图，不需要visited数组

int main() {
	Solution sol;
	vector<vector<int>> graph;
	graph = { { 1, 2 }, { 3 }, { 3 }, {} };
	cout << sol.allPathsSourceTarget(graph) << endl;
	graph = { { 4, 3, 1 }, { 3, 2, 4 }, { 3 }, { 4 }, {} };
	cout << sol.allPathsSourceTarget(graph) << endl;
	graph = { { 1 }, {} };
	cout << sol.allPathsSourceTarget(graph) << endl;
	graph = { { 1, 2, 3 }, { 2 }, { 3 }, {} };
	cout << sol.allPathsSourceTarget(graph) << endl;
	graph = { { 1, 3 }, { 2 }, { 3 }, {} };
	cout << sol.allPathsSourceTarget(graph) << endl;
}