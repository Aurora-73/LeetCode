// Created: 2025-12-20
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 一个密码锁由 4个环形拨轮组成，
每个拨轮都有 10 个数字： "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"。
每个拨轮可以自由旋转：例如把 "9" 变为"0"，"0" 变为 "9"。每次旋转都只能旋转一个拨轮的一位数字。
锁的初始数字为 "0000"，一个代表四个拨轮的数字的字符串。
列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。
字符串 target 代表可以解锁的数字，请给出解锁需要的最小旋转次数，如果无论如何不能解锁，返回 -1。
示例 1：
	输入：deadends = {"0201","0101","0102","1212","2002"}, target = "0202"
	输出：6
	解释：
	可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"。
	
	注意 "0000" -> "0001" -> "0002" -> "010^2" -> "0202" 这样的序列是不能解锁的，
	因为当拨动到 "010^2" 时这个锁就会被锁定。
示例 2：
	输入: deadends = {"8888"}, target = "0009"
	输出：1
	解释：
	把最后一位反向旋转一次即可 "0000" -> "0009"。
示例 3：
	输入: deadends = {"8887","8889","8878","8898","8788","8988","7888","9888"}, target = "8888"
	输出：-1
	解释：
	无法旋转到目标数字且不被锁定。
示例 4：
	输入: deadends = {"0000"}, target = "8888"
	输出：-1
提示：
	1 <=deadends.length <= 500
	deadends{i}.length == 4
	target.length == 4
	target 不在 deadends 之中
	target 和 deadends{i} 仅由若干位数字组成 */

class Solution1 {
public:
	typedef array<uint8_t, 4> pwtype;
	int openLock(vector<string> &deadends, string &targetstr) {
		unordered_set<pwtype, pwtype_hash> visited;
		for(auto &str : deadends) {
			visited.emplace(uint8_t(str[0] - '0'),
			    uint8_t(str[1] - '0'),
			    uint8_t(str[2] - '0'),
			    uint8_t(str[3] - '0'));
		}
		queue<pwtype> que;
		pwtype target = { uint8_t(targetstr[0] - '0'),
			uint8_t(targetstr[1] - '0'),
			uint8_t(targetstr[2] - '0'),
			uint8_t(targetstr[3] - '0') };
		pwtype beg = { 0, 0, 0, 0 };
		if(visited.insert(beg).second) que.push(beg);
		int depth = 0, size;
		while(!que.empty()) {
			size = que.size();
			for(int k = 0; k < size; ++k) {
				pwtype curr = que.front();
				que.pop();
				if(curr == target) return depth;
				for(int i = 0; i < 4; ++i) {
					for(int j = 0; j < 2; ++j) {
						pwtype temp = curr;
						temp[i] = (temp[i] + (j == 0 ? -1 : 1) + 10) % 10;
						if(visited.insert(temp).second) {
							que.push(temp);
						}
					}
				}
			}
			++depth;
		}
		return -1;
	}

private:
	struct pwtype_hash {
		size_t operator()(const pwtype &p) const noexcept {
			return ((size_t)p[3] << 24) | ((size_t)p[2] << 16) | ((size_t)p[1] << 8)
			    | ((size_t)p[0]);
		}
	};
};

class Solution {
public:
	int openLock(vector<string> &deadends, string &target) {
		vector<bool> dead(10000, false);
		for(auto &s : deadends) {
			dead[stoi(s)] = true;
		}

		int targetNum = stoi(target);
		if(dead[0]) return -1;
		if(targetNum == 0) return 0;

		vector<bool> vis(10000, false);
		queue<int> q;
		q.push(0);
		vis[0] = true;

		int depth = 0;
		while(!q.empty()) {
			int sz = q.size();
			while(sz--) {
				int cur = q.front();
				q.pop();
				if(cur == targetNum) return depth;

				int base[4] = { 1000, 100, 10, 1 };
				for(int i = 0; i < 4; ++i) {
					int b = base[i];
					int d = (cur / b) % 10;

					// 向上拨
					int up = cur + (d == 9 ? -9 * b : b);
					if(!dead[up] && !vis[up]) {
						vis[up] = true;
						q.push(up);
					}

					// 向下拨
					int down = cur + (d == 0 ? 9 * b : -b);
					if(!dead[down] && !vis[down]) {
						vis[down] = true;
						q.push(down);
					}
				}
			}
			++depth;
		}
		return -1;
	}
}; // 直接用int作为编码

class Solution2 {
public:
	int openLock(vector<string> &deadends, string &target) {
		vector<bool> dead(10000, false);
		for(auto &s : deadends) dead[stoi(s)] = true;

		int targetNum = stoi(target);
		if(dead[0]) return -1;
		if(targetNum == 0) return 0;

		const int INF = 1e9;
		vector<int> dist(10000, INF);

		// 小根堆：f = g + h
		priority_queue<Node, vector<Node>, Cmp> pq;

		dist[0] = 0;
		pq.push({ 0, heuristic(0, targetNum), 0 });

		int base[4] = { 1000, 100, 10, 1 };

		while(!pq.empty()) {
			auto [g, f, cur] = pq.top();
			pq.pop();

			if(cur == targetNum) return g;
			if(g > dist[cur]) continue;

			for(int i = 0; i < 4; ++i) {
				int b = base[i];
				int d = (cur / b) % 10;

				int up = cur + (d == 9 ? -9 * b : b);
				int down = cur + (d == 0 ? 9 * b : -b);

				if(!dead[up] && g + 1 < dist[up]) {
					dist[up] = g + 1;
					int h = heuristic(up, targetNum);
					pq.push({ dist[up], dist[up] + h, up });
				}
				if(!dead[down] && g + 1 < dist[down]) {
					dist[down] = g + 1;
					int h = heuristic(down, targetNum);
					pq.push({ dist[down], dist[down] + h, down });
				}
			}
		}
		return -1;
	}

private:
	struct Node {
		int g, f, x; // g: 已走步数, f = g + h, x: 状态
	};
	struct Cmp {
		bool operator()(const Node &a, const Node &b) const {
			return a.f > b.f; // 小根堆
		}
	};

	int heuristic(int cur, int target) {
		int h = 0;
		for(int i = 0; i < 4; ++i) {
			int a = cur % 10;
			int b = target % 10;
			int d = abs(a - b);
			h += min(d, 10 - d);
			cur /= 10;
			target /= 10;
		}
		return h;
	}
}; // A* 搜索

int main() {
	Solution sol;
	vector<string> deadends;
	string target;
	deadends = { "0201", "0101", "0102", "1212", "2002" }, target = "0202";
	cout << sol.openLock(deadends, target) << endl;

	deadends = { "8888" }, target = "0009";
	cout << sol.openLock(deadends, target) << endl;

	deadends = { "8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888" }, target = "8888";
	cout << sol.openLock(deadends, target) << endl;

	deadends = { "0000" }, target = "8888";
	cout << sol.openLock(deadends, target) << endl;

	deadends = { "8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888" }, target = "8888";
	cout << sol.openLock(deadends, target) << endl;
}