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
	bool canFinish(int numCourses, const vector<vector<int>> &prerequisites) {
		// 1. 构建邻接表
		vector<vector<int>> graph(numCourses);
		for(const auto &p : prerequisites) {
			// p[1] → p[0]：要学 p[0] 之前必须先完成 p[1]
			graph[p[1]].emplace_back(p[0]);
		}

		// 2. 两个辅助数组
		// visited[u] 表示节点 u 是否已经被 DFS 访问过
		// onPath[u]  表示节点 u 是否在当前递归栈（即访问路径）上
		vector<bool> visited(numCourses, false), onPath(numCourses, false);

		// 3. 标志位：只要发现环，就置为 true
		bool hasCycle = false;

		// 4. 用 std::function 包装一个递归 lambda，方便在函数内部捕获外部变量
		function<void(int)> dfs = [&](int u) {
			// 4.1 如果 u 已经在当前路径上，说明形成了环
			if(onPath[u]) {
				hasCycle = true;
				return;
			}
			// 4.2 如果已经访问过，或者全局已检测到环，就直接剪枝返回
			if(visited[u] || hasCycle)
				return;

			// 4.3 进入节点 u：标记已访问，并加入当前路径
			visited[u] = true;
			onPath[u] = true;

			// 4.4 递归访问所有后继节点
			for(int v : graph[u]) {
				dfs(v);
			}

			// 4.5 回溯时，将 u 从路径中移除
			onPath[u] = false;
		};

		// 5. 对每个节点 i（0…numCourses-1）做一次 DFS，直到发现环为止
		for(int i = 0; i < numCourses && !hasCycle; ++i) {
			dfs(i);
		}

		// 6. 如果没检测到环，则可以完成所有课程
		return !hasCycle;
	}
};

int main() {
	Solution1 sol1;
	int numCourses = 2;
	vector<vector<int>> prerequisites = {{1, 0}};
	sol1.canFinish(numCourses, prerequisites);
}