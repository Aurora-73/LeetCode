// Created: 2025-05-07
#include "MyUtils.h"

/*207. 课程表
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，
vv其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。*/

class Solution1 {
public:
	bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
		vector<int> degree(numCourses, 0);
		vector<vector<int>> afters(numCourses);
		for(auto &pair : prerequisites) {
			++degree[pair[0]];
			afters[pair[1]].push_back(pair[0]);
		}
		for(int www = 0; www < numCourses; ++www) {
			int now = -1;
			for(int i = 0; i < numCourses; ++i) {
				if(degree[i] == 0) {
					now = i;
					break;
				}
			}
			if(now == -1)
				return false;
			degree[now]--;
			for(auto after : afters[now]) {
				--degree[after];
			}
		}
		return true;
	}
};

class Solution2 {
public:
	bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
		vector<vector<int>> graph(numCourses);
		vector<int> inDegree(numCourses, 0);

		for(const auto &p : prerequisites) {
			graph[p[1]].push_back(p[0]);
			++inDegree[p[0]];
		}

		queue<int> q;
		for(int i = 0; i < numCourses; ++i)
			if(inDegree[i] == 0)
				q.push(i);

		int count = 0;
		while(!q.empty()) {
			int course = q.front();
			q.pop();
			++count;
			for(int next : graph[course]) {
				if(--inDegree[next] == 0)
					q.push(next);
			}
		}
		return count == numCourses;
	}
};

class Solution3 {
public:
	bool isCycle = false;
	vector<bool> visited, onPath;

	bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
		auto myGraph = buildGraph(prerequisites, numCourses);
		visited.resize(numCourses, false);
		onPath.resize(numCourses, false);
		for(int i = 0; i < numCourses; i++) {
			dfs(i, myGraph);
		}
		return !isCycle;
	}
	void dfs(int i, vector<vector<int>> &prerequisites) {
		if(onPath[i])
			isCycle = true;
		if(visited[i] || isCycle)
			return;

		onPath[i] = true;
		visited[i] = true;

		for(auto x : prerequisites[i]) {
			dfs(x, prerequisites);
		}
		onPath[i] = false;
	}
	vector<vector<int>> buildGraph(vector<vector<int>> &prerequisites, int numCourses) {
		vector<vector<int>> myGraph(numCourses);
		for(auto &edge : prerequisites) {
			int to = edge[0];
			int from = edge[1];
			myGraph[from].push_back(to);
		}
		return myGraph;
	}
};

int main() {
	Solution1 sol1;
	int numCourses = 2;
	vector<vector<int>> prerequisites = {{1, 0}};
	sol1.canFinish(numCourses, prerequisites);
}