// Created: 2025-06-27
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 130. 衣橱整理
家居整理师将待整理衣橱划分为 m x n 的二维矩阵 grid，其中 grid{i}{j} 代表一个需要整理的格子。
整理师自 grid{0}{0} 开始 逐行逐列 地整理每个格子。
整理规则为：在整理过程中，可以选择向右移动一格或向下移动一格，但不能移动到衣柜之外。同时，
不需要整理 digit(i)+ digit(j) > cnt 的格子，其中 digit(x)表示数字x 的各数位之和。
请返回整理师总共需要整理多少个格子。
示例 1：
	输入：m = 4, n = 7, cnt = 5
	输出：18
提示：
	1 <= n, m <= 100
	0 <= cnt <= 20 

换一种描述：
有一个 m x n 的二维矩阵 grid，从[0][0]位置出发，仅能经过 digit(i)+ digit(j) <= cnt 的格子，其中 digit(x)表示数字 x 的各数位之和。
问一共可以到达多少个格子（包括[0][0]，不可通过障碍） */

class Solution1 {
public:
	int wardrobeFinishing(int m, int n, int cnt) {
		count = 0, this->m = m, this->n = n;
		visited.resize(m, vector<bool>(n));
		passable = [&](int i, int j) {
			if(i >= m || j >= n || visited[i][j]) return false;
			int digitSum = 0;
			while(i > 0) {
				digitSum += i % 10;
				i /= 10;
			}
			while(j > 0) {
				digitSum += j % 10;
				j /= 10;
			}
			return digitSum <= cnt;
		};
		dfs(0, 0);
		return count;
	}

private:
	int count, m, n;
	vector<vector<bool>> visited;
	function<bool(int, int)> passable; // 用仿函数包装 lamda 表达式
	void dfs(int i, int j) {
		visited[i][j] = 1;
		++count;
		if(passable(i + 1, j)) dfs(i + 1, j);
		if(passable(i, j + 1)) dfs(i, j + 1);
	}
};

class Solution2 {
public:
	int wardrobeFinishing(int m, int n, int cnt) {
		count = 0, this->m = m, this->n = n, this->cnt = cnt;
		visited = vector<vector<bool>>(m, vector<bool>(n));
		dfs(0, 0);
		return count;
	}

private:
	int count, m, n, cnt;
	vector<vector<bool>> visited;
	void dfs(int i, int j) {
		visited[i][j] = 1;
		++count;
		if(passable(i + 1, j)) dfs(i + 1, j);
		if(passable(i, j + 1)) dfs(i, j + 1);
	}
	bool passable(int i, int j) {
		if(i >= m || j >= n || visited[i][j]) return false;
		int digitSum = 0;
		while(i > 0) {
			digitSum += i % 10;
			i /= 10;
		}
		while(j > 0) {
			digitSum += j % 10;
			j /= 10;
		}
		return digitSum <= cnt;
	};
}; // DFS 写法

class Solution {
public:
	int wardrobeFinishing(int m, int n, int cnt) {
		vector<vector<bool>> visited(m, vector<bool>(n));
		auto passable = [&](int i, int j) {
			if(i >= m || j >= n || visited[i][j]) return false;
			int digitSum = 0;
			while(i > 0) {
				digitSum += i % 10;
				i /= 10;
			}
			while(j > 0) {
				digitSum += j % 10;
				j /= 10;
			} // 局部的 i j 已经没用了，可以修改
			return digitSum <= cnt;
		};
		vector<pair<int, int>> vec;
		int res = 0;
		vec.emplace_back(0, 0), visited[0][0] = 1;
		while(!vec.empty()) {
			auto [i, j] = vec.back();
			vec.pop_back(), ++res;
			if(passable(i + 1, j)) {
				visited[i + 1][j] = 1;
				vec.emplace_back(i + 1, j);
			}
			if(passable(i, j + 1)) {
				visited[i][j + 1] = 1;
				vec.emplace_back(i, j + 1);
			}
		}
		return res;
	}
}; // 类 BFS 写法

int main() {
	Solution sol;
	int m = 4, n = 7, cnt = 5;
	cout << sol.wardrobeFinishing(m, n, cnt) << endl; // 18
}