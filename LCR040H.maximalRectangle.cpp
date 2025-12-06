// Created: 2025-12-06
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个由0 和 1组成的矩阵 matrix，找出只包含 1 的最大矩形，并返回其面积。
注意：此题 matrix输入格式为一维 01 字符串数组。
示例 1：
	输入：matrix = {"10100","10111","11111","10010"}
	输出：6
	解释：最大矩形如上图所示。
示例 2：
	输入：matrix = {}
	输出：0
示例 3：
	输入：matrix = {"0"}
	输出：0
示例 4：
	输入：matrix = {"1"}
	输出：1
示例 5：
	输入：matrix = {"00"}
	输出：0
提示：
	rows == matrix.length
	cols == matrix{0}.length
	0 <= row, cols <= 200
	matrix{i}{j} 为 "0" 或 "1" */

class Solution1 {
public:
	int maximalRectangle(vector<string> &matrix) {
		if(matrix.empty()) {
			return 0;
		}
		int res = 0, m = matrix.size(), n = matrix[0].size();
		vector<int> heights(n + 1, 0);
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(matrix[i][j] == '0') {
					heights[j] = 0;
				} else {
					++heights[j];
				}
			}
			res = max(res, largestRectangleArea(heights));
		}
		return res;
	}

private:
	int largestRectangleArea(vector<int> &heights) {
		// heights.push_back(0); // 数组最后加入一个0当做哨兵，可以让所有元素自动出栈，已经在前面加入这一步了
		int res = 0, n = heights.size();
		stack<int> st;
		for(int i = 0; i < n; ++i) {
			while(!st.empty() && heights[st.top()] > heights[i]) {
				int right = i, height = heights[st.top()];
				st.pop();
				int left = st.empty() ? -1 : st.top();
				res = max((right - left - 1) * height, res);
			}
			st.push(i);
		}
		return res;
	}
};
// 从上到下，以此计算以当前行为底的最大矩阵面积，计算方法与LCR039H.largestRectangleArea一样，并且height可以渐进式更新

class Solution {
public:
	int maximalRectangle(vector<string> &matrix) {
		if(matrix.empty()) {
			return 0;
		}
		int res = 0, m = matrix.size(), n = matrix[0].size();
		vector<int> heights(n, 0), left(n, -1), right(n, n);
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(matrix[i][j] == '0') {
					heights[j] = 0;
				} else {
					++heights[j];
				}
			}

			int lastZeroLeft = -1;
			for(int j = 0; j < n; ++j) {
				if(matrix[i][j] == '1') {
					left[j] = max(left[j], lastZeroLeft);
				} else {
					left[j] = -1;
					lastZeroLeft = j;
				}
			}

			int lastZeroRight = n;
			for(int j = n - 1; j >= 0; --j) {
				if(matrix[i][j] == '1') {
					right[j] = min(right[j], lastZeroRight);
				} else {
					right[j] = n;
					lastZeroRight = j;
				}
				res = max(res, (right[j] - left[j] - 1) * heights[j]);
			}
		}
		return res;
	}
};
// 也是从上到下，依次计算以当前行为底的二维数组的面积，并且left和right也是可以渐变的
// left的计算可以依赖前一行的计算结果：有两种情况，一种是因为以前就低于该列，另一种是出现了该行的0，因此需要记录遍历到当前为止的最靠右的0的位置

int main() {
	Solution sol;
	vector<string> matrix;
	matrix = { "10100", "10111", "11111", "10010" };
	cout << sol.maximalRectangle(matrix) << endl;

	matrix = {};
	cout << sol.maximalRectangle(matrix) << endl;

	matrix = { "1" };
	cout << sol.maximalRectangle(matrix) << endl;

	matrix = { "01" };
	cout << sol.maximalRectangle(matrix) << endl;
}