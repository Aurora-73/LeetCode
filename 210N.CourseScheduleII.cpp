// Created: 2025-05-07
#include "MyUtils.h"

/*现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。
给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi] ，表示在选修课程 ai 前 必须 先选修 bi 。
例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。
返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。
如果不可能完成所有课程，返回 一个空数组 。*/

class Solution1 {
public:
	vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
		vector<int> degree(numCourses, 0), res;
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
				return {};
			res.push_back(now);
			degree[now]--;
			for(auto after : afters[now]) {
				--degree[after];
			}
		}
		return res;
	}
};

class Solution2 {
public:
	vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
		vector<vector<int>> graph(numCourses);
		vector<int> inDegree(numCourses, 0), res;
		for(const auto &p : prerequisites) {
			graph[p[1]].push_back(p[0]);
			++inDegree[p[0]];
		}

		queue<int> q; // 使用队列保存可以访问的节点，不需要遍历inDegree了
		for(int i = 0; i < numCourses; ++i)
			if(inDegree[i] == 0)
				q.push(i);

		int count = 0;
		while(!q.empty()) {
			int course = q.front();
			res.push_back(course);
			q.pop();
			++count;
			for(int next : graph[course]) {
				if(--inDegree[next] == 0)
					q.push(next);
			}
		}
		return count == numCourses ? res : vector<int>();
	}
};

int main() {
	Solution1 sol1;
	int numCourses = 2;
	vector<vector<int>> prerequisites = {{1, 0}};
	sol1.findOrder(numCourses, prerequisites);
}