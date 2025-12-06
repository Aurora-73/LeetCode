// Created: 2025-12-06
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定非负整数数组 heights，数组中的数字用来表示柱状图中各个柱子的高度。
每个柱子彼此相邻，且宽度为 1。
求在该柱状图中，能够勾勒出来的矩形的最大面积。
示例 1:
	输入：heights = {2,1,5,6,2,3}
	输出：10
	解释：最大的矩形为图中红色区域，面积为 10
示例 2：
	输入： heights = {2,4}
	输出： 4
提示：
	1 <= heights.length <=10^5
	0 <= heights{i} <= 10^4
注意：本题与主站 84题相同： */

class Solution {
public:
	int largestRectangleArea(vector<int> &heights) {
		int res = 0, n = heights.size();
		vector<int> left(n, -1), right(n, n); // 记录向左向右首个小于该元素的下标
		stack<int> l_st, r_st;
		for(int i = 0; i < n; ++i) {
			while(!l_st.empty() && heights[l_st.top()] > heights[i]) {
				right[l_st.top()] = i;
				l_st.pop();
			} // 注意从左遍历得到的是右边界，从右遍历得到的是左边界
			while(!r_st.empty() && heights[r_st.top()] > heights[n - i - 1]) {
				left[r_st.top()] = n - i - 1;
				r_st.pop();
			}
			l_st.push(i);
			r_st.push(n - i - 1);
		}
		for(int i = 0; i < n; ++i) {
			res = max(res, heights[i] * (right[i] - left[i] - 1));
		}
		return res;
	}
};
// 矩形的高一定是数组中的某个元素，且宽是这个元素向左向右扩展的最大宽度之和，只需要遍历每个 {元素 * 扩展的最大宽度}
// 单调栈用于求每个元素向左向右扩展的最大宽度，类似于LCR038N.dailyTemperatures

int main() {
	Solution sol;
	vector<int> heights;
	heights = { 2, 1, 5, 6, 2, 3 };
	cout << sol.largestRectangleArea(heights) << endl; // 10
	heights = { 2, 4 };
	cout << sol.largestRectangleArea(heights) << endl; // 4
}