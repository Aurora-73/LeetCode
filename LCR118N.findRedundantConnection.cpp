// Created: 2025-12-21
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 树可以看成是一个连通且 无环的无向图。
给定往一棵n 个节点 (节点值1～n) 的树中添加一条边后的图。添加的边的两个顶点包含在 1 到 n中间，且这条附加的边不属于树中已存在的边。
图的信息记录于长度为 n 的二维数组 edges，edges{i} = {ai, bi}表示图中在 ai 和 bi 之间存在一条边。
请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。如果有多个答案，则返回数组edges中最后出现的边。
示例 1：
	输入: edges = {{1,2},{1,3},{2,3}}
	输出: {2,3}
示例 2：
	输入: edges = {{1,2},{2,3},{3,4},{1,4},{1,5}}
	输出: {1,4}
提示:
	n == edges.length
	3 <= n <= 1000
	edges{i}.length == 2
	1 <= ai< bi<= edges.length
	ai != bi
	edges 中无重复元素
	给定的图是连通的 */

class Solution {
public:
	vector<int> findRedundantConnection(vector<vector<int>> &edges) {
		int n = edges.size();
		parent = vector<int>(n, -1);
		for(auto &edge : edges) {
			if(!unite(edge[0] - 1, edge[1] - 1)) {
				return edge;
			}
		}
		return {};
	}

private:
	vector<int> parent;
	int find(int index) {
		if(parent[index] == -1) return index;
		int par = index;
		while(parent[par] != -1) {
			par = parent[par];
		}
		parent[index] = par;
		return par;
	}
	bool unite(int i, int j) {
		int pi = find(i), pj = find(j);
		if(pi != pj) {
			parent[pi] = pj;
			return true;
		}
		return false;
	}
}; // 并查集，按照边不断进行合并，直到遇到无效的合并即为答案
// 因为一共有n条边，因此只多了一条边

int main() {
	Solution sol;
	vector<vector<int>> edges;
	edges = { { 1, 2 }, { 1, 3 }, { 2, 3 } };
	cout << sol.findRedundantConnection(edges) << endl; //  {2,3}

	edges = { { 1, 2 }, { 2, 3 }, { 3, 4 }, { 1, 4 }, { 1, 5 } };
	cout << sol.findRedundantConnection(edges) << endl; // {1,4}
}