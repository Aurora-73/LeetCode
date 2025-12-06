// Created: 2025-12-06
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 请根据每日 气温 列表 temperatures，重新生成一个列表，
要求其对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。
如果气温在这之后都不会升高，请在该位置用0 来代替。
示例 1：
	输入：temperatures = {73,74,75,71,69,72,76,73}
	输出：{1,1,4,2,1,1,0,0}
示例 2：
	输入：temperatures = {30,40,50,60}
	输出：{1,1,1,0}
示例 3：
	输入：temperatures = {30,60,90}
	输出：{1,1,0}
提示：
	1 <=temperatures.length <= 10^5
	30 <=temperatures{i}<= 100 */

class Solution {
public:
	vector<int> dailyTemperatures(vector<int> &temperatures) {
		int n = temperatures.size();
		vector<int> res(n, 0);
		stack<int> st;
		for(int i = 0; i < n; ++i) {
			while(!st.empty() && temperatures[st.top()] < temperatures[i]) {
				res[st.top()] = i - st.top();
				st.pop();
			}
			st.push(i);
		}
		return res;
	}
}; // 单调栈，栈不需要记录值和下标，因为下标可以直接查找到值，栈中的温度是单调递减的
// 对于一个新的值，如果该值大于栈顶元素，则成功找到栈顶的更高气温，反之则可以入栈

int main() {
	Solution sol;
	vector<int> temperatures;
	temperatures = { 73, 74, 75, 71, 69, 72, 76, 73 };
	cout << sol.dailyTemperatures(temperatures) << endl;

	temperatures = { 30, 40, 50, 60 };
	cout << sol.dailyTemperatures(temperatures) << endl;

	temperatures = { 30, 60, 90 };
	cout << sol.dailyTemperatures(temperatures) << endl;
}