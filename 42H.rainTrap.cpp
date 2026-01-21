// Created: 2025-04-22
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
示例 1：
	输入：height = {0,1,0,2,1,0,1,3,2,1,2,1}
	输出：6
	解释：上面是由数组 {0,1,0,2,1,0,1,3,2,1,2,1} 表示的高度图，
	在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
示例 2：
	输入：height = {4,2,0,3,2,5}
	输出：9
提示：
	n == height.length
	1 <= n <= 2 * 10^4
	0 <= height{i} <= 10^5 */

class Solution1 {
public:
	int trap(vector<int> &height) {
		int water = 0, n = height.size();
		vector<int> left(n), right(n);
		left[0] = height[0];
		right[n - 1] = height[n - 1];
		for(int i = 1; i < n; i++) {
			left[i] = max(left[i - 1], height[i]);
			right[n - 1 - i] = max(right[n - i], height[n - 1 - i]);
		}
		for(int i = 1; i < n - 1; i++) {
			water += max(min(left[i] - height[i], right[i] - height[i]), 0);
		}
		return water;
	}
}; // 单调栈，双数组解法

class Solution2 {
public:
	int trap(vector<int> &height) {
		int n = height.size(), res = 0, rightMax = 0;
		vector<int> leftMax(n);
		for(int i = 1; i < n; ++i) {
			leftMax[i] = max(leftMax[i - 1], height[i - 1]);
		}
		for(int i = n - 2; i >= 0; --i) {
			rightMax = max(rightMax, height[i + 1]);
			res += max(0, min(rightMax, leftMax[i]) - height[i]);
		}
		return res;
	}
}; // 单调栈，单数组单指针解法

class Solution {
public:
	int trap(vector<int> &height) {
		int water = 0, l = 0, r = height.size() - 1, maxL = -1, maxR = -1;
		while(l <= r) {
			if(maxL <= maxR) {
				water += max(0, maxL - height[l]);
				maxL = max(maxL, height[l]);
				++l;
			} else {
				water += max(0, maxR - height[r]);
				maxR = max(maxR, height[r]);
				--r;
			}
		}
		return water;
	}
}; // 双指针解法：由于k > 0 时 leftMax[i] >= leftMax[i - k], rightMax[i] >= rightMax[i + k]
// 而 i 处的水深取决于 min(leftMax[i], leftMax[i])，
// 则 leftMax[i - k] >= rightMax[i] 可以确定min(leftMax[i], leftMax[i]) == rightMax[i]
// 同理 rightMax[i + k] >= leftMax[i] 可以确定min(leftMax[i], leftMax[i]) == leftMax[i]
// 因此只需要比较当前的两侧的边界，将边界更低的一个向内侧移动
/*  想象你在数组的任意一个位置 i，这个位置上方能积多少水？
	首先找到他左边最高的柱子leftmax，然后找到右边最高的柱子rightmax，则位置 i 的积水量为min(leftmax, rightmax) - height[i]
	在双指针法中为什么leftmax<rightmax时就可以确定left处的积水量呢？
	这是因为此时left的左右屏障都以确定，且左边更短，储水量取决于leftmax，
	我们不需要知道left右边最高的高度是多少，只知道右边已经有一个比leftmax更高的屏障，
	确保水不会从右边流走，所以该位置的储水量就是leftmax-height[left]。*/

int main() {
	Solution sol;
	vector<int> height;
	height = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };

	height = { 4, 2, 0, 3, 2, 5 };

	height = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
}

/* 1、两次遍历（一次顺序遍历、一次逆序遍历），分别获得每一个格子的前后信息
每个格子能承载的雨水量为该格子左边的最大值lmax和右边的最大值rmax二者中最小的（短板效应）那一个减去本格的高度
2、对于某一个位置的格子，其实没必要同时知道左右两侧的最大高度，只需要知道当前格子左侧的最大高度和右侧的最大高度中的较小值即可
因为遍历时左右两侧的最大高度是单调递增的，因此对于l指针，左侧最大高度已定是maxL，但是右侧最大高度大于等于maxR，因此如果maxL小于maxR，那么l指针能承载的雨水量就是maxL
同理对于r指针，右侧最大高度已定是maxR，但是左侧最大高度大于等于maxL，因此如果maxR小于maxL，那么r指针能承载的雨水量就是maxR
这样就可以迭代l和r指针，求出每一个格子的雨水量 */