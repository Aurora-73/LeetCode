// Created: 2025-12-21
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个变量对数组 equations 和一个实数值数组 values 作为已知条件，
其中 equations{i} = {Ai, Bi} 和 values{i} 共同表示等式 Ai / Bi = values{i}。
每个 Ai 或 Bi 是一个表示单个变量的字符串。
另有一些以数组 queries 表示的问题，其中 queries{j} = {Cj, Dj} 表示第 j 个问题，
请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。
返回 所有问题的答案。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。
如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。
注意：输入总是有效的。可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。
示例 1：
	输入：equations = {{"a","b"},{"b","c"}}, values = {2.0,3.0}, queries = {{"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"}}
	输出：{6.00000,0.50000,-1.00000,1.00000,-1.00000}
	解释：
	条件：a / b = 2.0, b / c = 3.0
	问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
	结果：{6.0, 0.5, -1.0, 1.0, -1.0 }
示例 2：
	输入：equations = {{"a","b"},{"b","c"},{"bc","cd"}}, values = {1.5,2.5,5.0}, queries = {{"a","c"},{"c","b"},{"bc","cd"},{"cd","bc"}}
	输出：{3.75000,0.40000,5.00000,0.20000}
示例 3：
	输入：equations = {{"a","b"}}, values = {0.5}, queries = {{"a","b"},{"b","a"},{"a","c"},{"x","y"}}
	输出：{0.50000,2.00000,-1.00000,-1.00000}
提示：
	1 <= equations.length <= 20
	equations{i}.length == 2
	1 <= Ai.length, Bi.length <= 5
	values.length == equations.length
	0.0 < values{i} <= 20.0
	1 <= queries.length <= 20
	queries{i}.length == 2
	1 <= Cj.length, Dj.length <= 5
	Ai, Bi, Cj, Dj 由小写英文字母与数字组成 */

class Solution1 {
public:
	vector<double> calcEquation(const vector<vector<string>> &equations,
	    const vector<double> &values,
	    const vector<vector<string>> &queries) {
		// 构建邻接表
		unordered_map<string, vector<pair<string, double>>> graph;
		int m = equations.size();
		for(int i = 0; i < m; ++i) {
			const string &a = equations[i][0];
			const string &b = equations[i][1];
			double v = values[i];
			graph[a].push_back({ b, v });
			graph[b].push_back({ a, 1.0 / v });
		}

		// 处理每个查询
		vector<double> ans;
		ans.reserve(queries.size());
		for(auto &q : queries) {
			const string &start = q[0];
			const string &end = q[1];

			// 若任一变量未出现过，结果为 -1
			if(graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
				ans.push_back(-1.0);
				continue;
			}

			// 特判 start == end
			if(start == end) {
				ans.push_back(1.0);
				continue;
			}

			unordered_set<string> visited;
			double res = dfs(start, end, visited, graph);
			ans.push_back(res);
		}
		return ans;
	}

private:
	// 返回从 cur 到 target 的值（路径乘积），找不到返回 -1.0
	double dfs(const string &cur,
	    const string &target,
	    unordered_set<string> &visited,
	    unordered_map<string, vector<pair<string, double>>> &graph) {
		if(cur == target) return 1.0;
		visited.insert(cur);

		for(const auto &nei : graph[cur]) {
			const string &next = nei.first;
			double weight = nei.second;
			if(visited.count(next)) continue;
			double sub = dfs(next, target, visited, graph);
			if(sub != -1.0) {
				return weight * sub;
			}
		}
		return -1.0;
	}
}; // 邻接表(pair{节点，值})

class Solution {
public:
	vector<double> calcEquation(vector<vector<string>> &equations,
	    vector<double> &values,
	    vector<vector<string>> &queries) {
		matrix.clear();
		unordered_map<string, int> vertexs;

		int ne = equations.size();
		vector<vector<int>> equationsInt(ne, vector<int>(2));
		for(int i = 0; i < ne; ++i) {
			auto p1 = vertexs.emplace(equations[i][0], vertexs.size());
			auto p2 = vertexs.emplace(equations[i][1], vertexs.size());
			equationsInt[i][0] = p1.first->second;
			equationsInt[i][1] = p2.first->second;
		}

		int nv = vertexs.size();
		matrix.resize(nv, vector<double>(nv, -2.0));
		for(int i = 0; i < nv; ++i) matrix[i][i] = 1.0;
		for(int i = 0; i < ne; ++i) {
			int u = equationsInt[i][0], v = equationsInt[i][1];
			matrix[u][v] = values[i];
			matrix[v][u] = 1.0 / values[i];
		}

		int nq = queries.size();
		vector<double> res(nq, -1.0);
		for(int i = 0; i < nq; ++i) {
			auto it1 = vertexs.find(queries[i][0]);
			auto it2 = vertexs.find(queries[i][1]);
			if(it1 != vertexs.end() && it2 != vertexs.end()) {
				vector<bool> visited(nv, false);
				res[i] = query(visited, it1->second, it2->second);
			}
		}
		return res;
	}

private:
	vector<vector<double>> matrix;

	double query(vector<bool> &visited, int l, int r) {
		// 若已有缓存，直接返回
		if(matrix[l][r] != -2.0) {
			return matrix[l][r];
		}

		visited[l] = true;
		double res = -1.0;
		int n = matrix.size();

		// 只沿着“已知存在的边”（权值 > 0）DFS
		for(int i = 0; i < n; ++i) {
			if(matrix[l][i] > 0 && !visited[i]) {
				double cur = query(visited, i, r);
				if(cur != -1.0) {
					res = matrix[l][i] * cur;
					break;
				}
			}
		}

		// 记忆化缓存结果
		matrix[l][r] = res;
		if(res != -1.0)
			matrix[r][l] = 1.0 / res;
		else
			matrix[r][l] = -1.0;

		return res;
	}
}; // 邻接矩阵，通过查询后保存查询到的值可以加快访问，-1代表不存在的值，-2代表没查询过

int main() {
	Solution sol;
	vector<vector<string>> equations, queries;
	vector<double> values;
	equations = { { "x1", "x2" }, { "x2", "x3" }, { "x3", "x4" }, { "x4", "x5" } },
	values = { 3.0, 4.0, 5.0, 6.0 },
	queries = { { "x1", "x5" },
		{ "x5", "x2" },
		{ "x2", "x4" },
		{ "x2", "x2" },
		{ "x2", "x9" },
		{ "x9", "x9" } };
	cout << sol.calcEquation(equations, values, queries) << endl;

	equations = { { "a", "b" }, { "b", "c" } }, values = { 2.0, 3.0 },
	queries = { { "a", "c" }, { "b", "a" }, { "a", "e" }, { "a", "a" }, { "x", "x" } };
	cout << sol.calcEquation(equations, values, queries) << endl;

	equations = { { "a", "b" }, { "b", "c" }, { "bc", "cd" } }, values = { 1.5, 2.5, 5.0 },
	queries = { { "a", "c" }, { "c", "b" }, { "bc", "cd" }, { "cd", "bc" } };
	cout << sol.calcEquation(equations, values, queries) << endl;

	equations = { { "a", "b" } }, values = { 0.5 },
	queries = { { "a", "b" }, { "b", "a" }, { "a", "c" }, { "x", "y" } };
	cout << sol.calcEquation(equations, values, queries) << endl;
}