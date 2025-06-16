// Created: 2025-06-16
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 739. 每日温度
给定一个整数数组temperatures，表示每天的温度，返回一个数组answer，
其中answer{i}是指对于第 i 天，下一个更高温度出现在几天后。
如果气温在这之后都不会升高，请在该位置用 0 来代替。
示例 1:
	输入: temperatures = {73,74,75,71,69,72,76,73}
	输出: {1,1,4,2,1,1,0,0}
示例 2:
	输入: temperatures = {30,40,50,60}
	输出:{1,1,1,0}
示例 3:
	输入: temperatures = {30,60,90}
	输出: {1,1,0}
提示：
	1 <= temperatures.length <= 10 ^ 5
	30 <= temperatures{i} <= 100 */

class Solution1 {
public:
	vector<int> dailyTemperatures(vector<int> &temp) {
		int n = temp.size();
		vector<int> res(n);
		stack<pair<int, int>> st; // val, index
		for(int i = n - 1; i >= 0; --i) {
			while(!st.empty() && st.top().first <= temp[i]) {
				st.pop();
			}
			if(!st.empty()) {
				res[i] = st.top().second - i;
			}
			st.emplace(temp[i], i);
		}
		return res;
	}
};

class Solution {
public:
	vector<int> dailyTemperatures(vector<int> &temperatures) {
		int n = temperatures.size();
		vector<int> ans(n);
		stack<int> st;
		for(int i = n - 1; i >= 0; i--) {
			int t = temperatures[i];
			while(!st.empty() && t >= temperatures[st.top()]) {
				st.pop();
			}
			if(!st.empty()) {
				ans[i] = st.top() - i;
			}
			st.push(i);
		}
		return ans;
	}
};

int main() {
	Solution sol;
	vector<int> temperatures;
	temperatures = { 73, 74, 75, 71, 69, 72, 76, 73 };
	cout << sol.dailyTemperatures(temperatures) << endl; // {1,1,4,2,1,1,0,0}
	temperatures = { 30, 40, 50, 60 };
	cout << sol.dailyTemperatures(temperatures) << endl; // {1,1,1,0}
	temperatures = { 30, 60, 90 };
	cout << sol.dailyTemperatures(temperatures) << endl; // {1,1,0}
}