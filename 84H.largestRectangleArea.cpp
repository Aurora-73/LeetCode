// Created: 2025-06-21
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 84. 柱状图中最大的矩形
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。
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
	0 <= heights{i} <= 10^4 */

class Solution1 {
public:
	int largestRectangleArea(vector<int> &heights) {
		int n = heights.size(), res = 0;
		// left[i] 默认 -1，表示左边界在最左侧之外
		// right[i] 默认 n，表示右边界在最右侧之外
		vector<int> left(n, -1), right(n, n);
		stack<int> st;

		// 第一次遍历：确定每个位置 i 的左边界 left[i]、并在弹栈时填写 right[stk.top()]
		for(int i = 0; i < n; ++i) {
			// 如果当前柱高 heights[i] 小于 栈顶索引对应高度，
			// 则说明栈顶元素遇到了自己的右边界 i
			while(!st.empty() && heights[st.top()] > heights[i]) {
				right[st.top()] = i; // 右边界（开）设置为 i
				st.pop();
			}
			// 栈不空时，栈顶就是当前 i 的左边界 L_i
			if(!st.empty()) {
				left[i] = st.top(); // 左边界（开）设置为 st.top()
			}
			// 将当前索引入栈，保持栈内 heights 单调递增
			st.push(i);
		}

		// 第二次遍历：计算以每根柱子为最矮柱时的最大矩形面积
		for(int i = 0; i < n; ++i) {
			// 区间宽度 = right[i] - left[i] - 1
			int width = right[i] - left[i] - 1;
			res = max(res, heights[i] * width);
		}
		return res;
	}
};
/* 用left和right记录每个位置高度的左边界和右边界（左开又开）
   压栈时确定当前元素的左边界，弹栈时确定栈顶元素的右边界  */

class Solution {
public:
	int largestRectangleArea(vector<int> &h) {
		int n = h.size(), res = 0, now, left;
		stack<int> st;
		for(int i = 0; i <= n; ++i) {
			int val = (i == n) ? -1 : h[i]; // 最后弹出全部的元素
			while(!st.empty() && h[st.top()] > val) {
				now = st.top(), st.pop();                // 先获取已经可以确定的元素的下标
				left = st.empty() ? -1 : st.top();       // 确定该元素的左边界
				res = max(res, h[now] * (i - left - 1)); // 右边界就是当前位置
			}
			st.push(i);
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> heights;
	heights = { 2, 1, 5, 6, 2, 3 };
	cout << sol.largestRectangleArea(heights) << endl; // 10
	heights = { 2, 4 };
	cout << sol.largestRectangleArea(heights) << endl; // 4
}