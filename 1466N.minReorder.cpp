// Created: 2025-07-07
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1466. 重新规划路线
n 座城市，从 0 到 n-1 编号，其间共有 n-1 条路线。
因此，要想在两座不同城市之间旅行只有唯一一条路线可供选择（路线网形成一颗树）。
去年，交通运输部决定重新规划路线，以改变交通拥堵的状况。
路线用 connections 表示，其中 connections{i} = {a, b} 表示从城市 a 到 b 的一条有向路线。
今年，城市 0 将会举办一场大型比赛，很多游客都想前往城市 0。
请你帮助重新规划路线方向，使每个城市都可以访问城市 0。返回需要变更方向的最小路线数。
题目数据 保证 每个城市在重新规划路线方向后都能到达城市 0。
示例 1：
	输入：n = 6, connections = {{0,1},{1,3},{2,3},{4,0},{4,5}}
	输出：3
	解释：更改以红色显示的路线的方向，使每个城市都可以到达城市 0。
示例 2：
	输入：n = 5, connections = {{1,0},{1,2},{3,2},{3,4}}
	输出：2
	解释：更改以红色显示的路线的方向，使每个城市都可以到达城市 0。
示例 3：
	输入：n = 3, connections = {{1,0},{2,0}}
	输出：0
提示：
	2 <= n <= 5 * 10^4
	connections.length == n-1
	connections{i}.length == 2
	0 <= connections{i}{0}, connections{i}{1} <= n-1
	connections{i}{0} != connections{i}{1} */

class Solution1 {
public:
	int minReorder(int n, vector<vector<int>> &connections) {
		int res = 0;
		queue<int> q;
		vector<bool> visited = vector<bool>(n);
		vector<vector<bool>> map(n, vector<bool>(n)), cost(n, vector<bool>(n));
		for(auto &c : connections) {
			map[c[0]][c[1]] = 1;
			map[c[1]][c[0]] = 1;
			cost[c[1]][c[0]] = 1;
		}
		q.push(0);
		visited[0] = 1;
		while(!q.empty()) {
			int now = q.front();
			q.pop();
			for(int i = 0; i < n; ++i) {
				if(!visited[i]) {
					if(map[now][i] == 1) {
						q.push(i);
						visited[i] = 1;
						if(cost[now][i]) ++res;
					}
				}
			}
		}
		return res;
	}
}; // 注意是从0到任意节点，和遍历的顺序相反
// 临界表存图，空间溢出，这是稀疏图

struct pair_hash {
	size_t operator()(const pair<int, int> &p) const noexcept {
		// 简单地把两个 int 拼成一个 size_t ( int 32位，size_t 64位，直接拼接即可 )
		return ((size_t)p.first << 32) ^ (size_t)p.second;
	}
};

class Solution2 {
public:
	int minReorder(int n, vector<vector<int>> &connections) {
		int res = 0;
		queue<int> q;
		vector<bool> visited = vector<bool>(n);
		unordered_set<pair<int, int>, pair_hash> links;
		for(auto &con : connections) {
			links.insert({ con[0], con[1] });
		}
		q.push(0);
		visited[0] = 1;
		while(!q.empty()) {
			int now = q.front();
			q.pop();
			for(int i = 0; i < n; ++i) {
				if(!visited[i]) {
					auto it = links.find({ i, now });
					if(it != links.end()) {
						q.push(i);
						visited[i] = 1;
					}
					it = links.find({ now, i });
					if(it != links.end()) {
						++res;
						q.push(i);
						visited[i] = 1;
					}
				}
			}
		}
		return res;
	}
}; // 哈希表存边，时间溢出

class Solution3 {
public:
	int minReorder(int n, vector<vector<int>> &connections) {
		int res = 0;
		queue<int> q;
		vector<bool> visited = vector<bool>(n);
		vector<vector<pair<int, bool>>> links(n);
		for(auto &con : connections) {
			links[con[0]].emplace_back(con[1], true);
			links[con[1]].emplace_back(con[0], false);
		}
		q.push(0);
		visited[0] = 1;
		while(!q.empty()) {
			int now = q.front();
			q.pop();
			for(auto [i, flag] : links[now]) {
				if(!visited[i]) {
					if(flag) {
						++res;
					}
					q.push(i);
					visited[i] = 1;
				}
			}
		}
		return res;
	}
}; // 临界链表 + 方向存边
/*  用临界链表保存图，先将每条边假定为双向边，真正存在的方向为true，另一个方向为false
    从0点开始进行广度优先遍历，对于遍历到的节点的每个边，如果还没遍历过目标节点，如果改边是真实边，就直接遍历，否则将计数加一，然后遍历 
为什么正确？
    树里从 0 到任何节点有且只有一条路径。
    如果这条路径上某条边方向「背道而驰」，那就得改；如果已经朝向 0，那就不用动。
    BFS 从 0 向外走，相当于在每条唯一的路径上检查一次，不多改、不少改，正好是最少需要反转的次数。*/

class Solution {
public:
	int minReorder(int n, vector<vector<int>> &connections) {
		int res = 0, m = connections.size(), idx = -1;
		stack<int> q;
		vector<bool> visited(n), cost;
		vector<int> first(n, -1), to, nextLink;
		to.reserve(2 * m);
		nextLink.reserve(2 * m);
		cost.reserve(2 * m);
		for(auto &conn : connections) {
			to.push_back(conn[0]);
			cost.push_back(0);
			nextLink.push_back(first[conn[1]]);
			first[conn[1]] = ++idx;

			to.push_back(conn[1]);
			cost.push_back(1);
			nextLink.push_back(first[conn[0]]);
			first[conn[0]] = ++idx;
		}
		q.push(0);
		visited[0] = 1;
		while(!q.empty()) {
			int now = q.top(), link = first[now];
			q.pop();
			while(link != -1) {
				if(!visited[to[link]]) {
					if(cost[link]) {
						++res;
					}
					q.push(to[link]);
					visited[to[link]] = 1;
				}
				link = nextLink[link];
			}
		}
		return res;
	}
}; // 另一种存图法，first[i]: 顶点 i 的第一个边，to[l]: 边 l 的目的地，nextLink[l]: 边 l 的同一个顶点的下一个边，cost[l]：边 l 是否为虚边

int main() {
	Solution sol;
	int n;
	vector<vector<int>> connections;
	n = 6, connections = { { 0, 1 }, { 1, 3 }, { 2, 3 }, { 4, 0 }, { 4, 5 } };
	cout << sol.minReorder(n, connections) << endl; // 3
	n = 5, connections = { { 1, 0 }, { 1, 2 }, { 3, 2 }, { 3, 4 } };
	cout << sol.minReorder(n, connections) << endl; // 2
	n = 3, connections = { { 1, 0 }, { 2, 0 } };
	cout << sol.minReorder(n, connections) << endl; // 0
}