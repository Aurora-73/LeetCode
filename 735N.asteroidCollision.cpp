// Created: 2025-07-05
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 735. 小行星碰撞
给定一个整数数组 asteroids，表示在同一行的小行星。
数组中小行星的索引表示它们在空间中的相对位置。
对于数组中的每一个元素，其绝对值表示小行星的大小，正负表示小行星的移动方向（正表示向右移动，
负表示向左移动）。每一颗小行星以相同的速度移动。
找出碰撞后剩下的所有小行星。碰撞规则：两个小行星相互碰撞，较小的小行星会爆炸。
如果两颗小行星大小相同，则两颗小行星都会爆炸。两颗移动方向相同的小行星，永远不会发生碰撞。
示例 1：
	输入：asteroids = {5,10,-5}
	输出：{5,10}
	解释：10 和 -5 碰撞后只剩下 10。 5 和 10 永远不会发生碰撞。
示例 2：
	输入：asteroids = {8,-8}
	输出：{}
	解释：8 和 -8 碰撞后，两者都发生爆炸。
示例 3：
	输入：asteroids = {10,2,-5}
	输出：{10}
	解释：2 和 -5 发生碰撞后剩下 -5。10 和 -5 发生碰撞后剩下 10。
提示：
	2 <= asteroids.length<= 10^4
	-1000 <= asteroids{i} <= 1000
	asteroids{i} != 0 */

class Solution1 {
public:
	vector<int> asteroidCollision(vector<int> &asteroids) {
		stack<int> st;
		int n = asteroids.size();
		for(int i = 0; i < n; ++i) {
			if(st.empty() || !(st.top() > 0 && asteroids[i] < 0)) {
				st.push(asteroids[i]);
			} else {
				int diff = st.top() + asteroids[i];
				if(diff <= 0) {
					if(diff < 0) {
						--i; // 还要再和当前栈顶判断相撞
					}
					st.pop();
				}
			}
		}
		n = st.size();
		vector<int> res(n);
		while(!st.empty()) {
			res[--n] = st.top();
			st.pop();
		}
		return res;
	}
};

class Solution {
public:
	vector<int> asteroidCollision(vector<int> &asteroids) {
		vector<int> res;
		int n = asteroids.size();
		for(int i = 0; i < n; ++i) {
			if(res.empty() || !(res.back() > 0 && asteroids[i] < 0)) {
				res.push_back(asteroids[i]);
			} else {
				int diff = res.back() + asteroids[i];
				if(diff <= 0) {
					if(diff < 0) {
						--i; // 还要再和当前栈顶判断相撞
					}
					res.pop_back();
				}
			}
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> asteroids;
	asteroids = { 5, 10, -5 };
	cout << sol.asteroidCollision(asteroids) << endl; // {5, 10}
	asteroids = { 8, -8 };
	cout << sol.asteroidCollision(asteroids) << endl; // {}
	asteroids = { 10, 2, -5 };
	cout << sol.asteroidCollision(asteroids) << endl; // {10}
}