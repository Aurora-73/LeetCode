// Created: 2025-05-06
#include "MyUtils.h"
#include "MyListNode.h"

/*399. 除法求值
给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。
每个 Ai 或 Bi 是一个表示单个变量的字符串。
另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。
返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。
注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。
注意：未在等式列表中出现的变量是未定义的，因此无法确定它们的答案。*/

class Solution1 {
public:
	vector<double> calcEquation(vector<vector<string>> &equa, vector<double> &val, vector<vector<string>> &quer) {
		unordered_map<string, size_t> exp2index;
		double grap[40][40];
		for(size_t i = 0; i < 40; ++i) {
			for(size_t j = 0; j < 40; ++j) {
				grap[i][j] = (i == j) ? 1.0 : -1.0;
			}
		}

		// 构建图
		for(int i = 0; i < equa.size(); ++i) {
			size_t idx[2];
			for(int k = 0; k < 2; ++k) {
				const string &var = equa[i][k];
				auto it = exp2index.find(var);
				if(it == exp2index.end()) {
					idx[k] = exp2index.size();
					exp2index[var] = idx[k];
				} else {
					idx[k] = it->second;
				}
			}
			grap[idx[0]][idx[1]] = val[i];
			grap[idx[1]][idx[0]] = 1.0 / val[i];
		}

		size_t n = exp2index.size();
		for(size_t i = 0; i < n; ++i) {
			for(size_t j = 0; j < n; ++j) {
				if(i != j && grap[i][j] != -1.0) {
					vector<bool> visited(n, false);
					visited[i] = true;
					dfs(grap, n, i, j, visited, grap[i][j]);
				}
			}
		}

		// 查询
		vector<double> res(quer.size(), -1.0);
		for(int i = 0; i < quer.size(); ++i) {
			size_t idx[2];
			bool ok = true;
			for(int k = 0; k < 2; ++k) {
				auto it = exp2index.find(quer[i][k]);
				if(it == exp2index.end()) {
					ok = false;
					break;
				}
				idx[k] = it->second;
			}
			if(ok && grap[idx[0]][idx[1]] != -1.0) {
				res[i] = grap[idx[0]][idx[1]];
			}
		}

		return res;
	}

private:
	void dfs(double grap[40][40], size_t n, size_t src, size_t cur, vector<bool> &visited, double val) {
		visited[cur] = true;
		if(grap[src][cur] == -1.0) {
			grap[src][cur] = val;
			grap[cur][src] = 1.0 / val;
		}
		for(size_t k = 0; k < n; ++k) {
			if(!visited[k] && grap[cur][k] != -1.0) {
				dfs(grap, n, src, k, visited, val * grap[cur][k]);
			}
		}
	}
};

class Solution2 {
public:
	vector<double> calcEquation(
	    const vector<vector<string>> &equations, const vector<double> &values, const vector<vector<string>> &queries) {

		unordered_map<string, shared_ptr<string>> str_pool;
		unordered_map<shared_ptr<string>, unordered_map<shared_ptr<string>, double>> graph;

		// 构建字符串池并建立图结构
		for(size_t i = 0; i < equations.size(); ++i) {
			const string &a = equations[i][0];
			const string &b = equations[i][1];
			double val = values[i];

			if(!str_pool.count(a))
				str_pool[a] = make_shared<string>(a);
			if(!str_pool.count(b))
				str_pool[b] = make_shared<string>(b);

			shared_ptr<string> pa = str_pool[a];
			shared_ptr<string> pb = str_pool[b];

			graph[pa][pb] = val;
			graph[pb][pa] = 1.0 / val;
		}

		vector<double> res;
		for(const auto &q : queries) {
			const string &src = q[0];
			const string &dst = q[1];

			if(!str_pool.count(src) || !str_pool.count(dst)) {
				res.push_back(-1.0);
				continue;
			}

			shared_ptr<string> ps = str_pool[src];
			shared_ptr<string> pd = str_pool[dst];

			if(ps == pd) {
				res.push_back(1.0);
				continue;
			}

			unordered_set<shared_ptr<string>> visited;
			double result = -1.0;
			dfs(graph, ps, pd, 1.0, visited, result);
			res.push_back(result);
		}

		return res;
	}

private:
	void dfs(const unordered_map<shared_ptr<string>, unordered_map<shared_ptr<string>, double>> &graph,
	    const shared_ptr<string> &cur,
	    const shared_ptr<string> &target,
	    double acc,
	    unordered_set<shared_ptr<string>> &visited,
	    double &result) {

		visited.insert(cur);
		if(graph.count(cur) && graph.at(cur).count(target)) {
			result = acc * graph.at(cur).at(target);
			return;
		}

		if(!graph.count(cur))
			return;

		for(const auto &[neighbor, weight] : graph.at(cur)) {
			if(!visited.count(neighbor)) {
				dfs(graph, neighbor, target, acc * weight, visited, result);
				if(result != -1.0)
					return;
			}
		}
	}
};

class Solution3 {
public:
	vector<double> calcEquation(
	    vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries) {
		map<string, map<string, double>> m;
		for(int i = 0; i < equations.size(); i++) {
			m[equations[i][0]][equations[i][1]] = values[i];
			m[equations[i][1]][equations[i][0]] = 1 / values[i];
		}
		vector<double> res;
		for(int i = 0; i < queries.size(); i++) {
			unordered_set<string> visited;
			res.push_back(calc(m, visited, queries[i][0], queries[i][1]));
		}
		return res;
	}
	double calc(map<string, map<string, double>> &m, unordered_set<string> &visited, const string &q1, string &q2) {
		if(visited.count(q1))
			return -1;
		if(m.count(q1)) {
			visited.insert(q1);
			if(m[q1].count(q2))
				return m[q1][q2];
			for(auto &p : m[q1]) {
				double t = calc(m, visited, p.first, q2);
				if(t > 0)
					return t * p.second;
			}
		}
		return -1;
	}
};

// 缺少并查集

int main() {
	Solution1 sol1;
}