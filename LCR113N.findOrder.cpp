// Created: 2025-12-22
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 现在总共有 numCourses门课需要选，记为0到numCourses-1。
给定一个数组prerequisites，它的每一个元素prerequisites{i}表示两门课程之间的先修顺序。
例如prerequisites{i} = {ai, bi}表示想要学习课程 ai，需要先完成课程 bi。
请根据给出的总课程数 numCourses 和表示先修顺序的prerequisites得出一个可行的修课序列。
可能会有多个正确的顺序，只要任意返回一种就可以了。如果不可能完成所有课程，返回一个空数组。
示例 1：
	输入: numCourses = 2, prerequisites = {{1,0}} 
	输出: {0,1}
	解释:总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 {0,1}。
示例 2：
	输入: numCourses = 4, prerequisites = {{1,0},{2,0},{3,1},{3,2}}
	输出: {0,1,2,3} or {0,2,1,3}
	解释:总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
	因此，一个正确的课程顺序是 {0,1,2,3}。另一个正确的排序是 {0,2,1,3}。
示例 3：
	输入: numCourses = 1, prerequisites = {} 
	输出: {0}
	解释:总共 1 门课，直接修第一门课就可。
提示：
	1 <= numCourses <= 2000
	0 <= prerequisites.length <= numCourses * (numCourses - 1)
	prerequisites{i}.length == 2
	0 <= ai, bi < numCourses
	ai != bi
	prerequisites中不存在重复元素 */

class Solution {
public:
	vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
		vector<int> preCont(numCourses, 0);
		vector<vector<int>> nexts(numCourses);
		for(auto const &preq : prerequisites) {
			int l = preq[0], r = preq[1];
			++preCont[l];
			nexts[r].push_back(l);
		}
		vector<int> res;
		queue<int> que;
		res.reserve(numCourses);
		for(int i = 0; i < numCourses; ++i) {
			if(preCont[i] == 0) {
				que.push(i);
			}
		}
		while(!que.empty()) {
			int curr = que.front();
			que.pop();
			res.push_back(curr);
			for(int num : nexts[curr]) {
				if((--preCont[num]) == 0) {
					que.push(num);
				}
			}
		}
		return res.size() == numCourses ? res : vector<int> {};
	}
};

int main() {
	Solution sol;
	int numCourses;
	vector<vector<int>> prerequisites;
	numCourses = 2, prerequisites = { { 1, 0 } };
	cout << sol.findOrder(numCourses, prerequisites) << endl;

	numCourses = 4, prerequisites = { { 1, 0 }, { 2, 0 }, { 3, 1 }, { 3, 2 } };
	cout << sol.findOrder(numCourses, prerequisites) << endl;

	numCourses = 1, prerequisites = {};
	cout << sol.findOrder(numCourses, prerequisites) << endl;
}