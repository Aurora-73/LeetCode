// Created: 2025-12-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定 M×N 矩阵，每一行、每一列都按升序排列，请编写代码找出某元素。
示例：
现有矩阵 matrix 如下：
{
  {1,   4,  7, 11, 15},
  {2,   5,  8, 12, 19},
  {3,   6,  9, 16, 22},
  {10, 13, 14, 17, 24},
  {18, 21, 23, 26, 30}
}
给定 target=5，返回true。
给定target=20，返回false。 */

class Solution {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		if(matrix.empty()) return 0;
		int m = matrix.size(), n = matrix[0].size(), i = 0, j = n - 1;
		while(i < m && j >= 0) {
			if(matrix[i][j] == target) {
				return true;
			} else if(matrix[i][j] < target) {
				++i;
			} else {
				--j;
			}
		}
		return false;
	}
}; // 从右下角或左上角开始查找

int main() {
	Solution sol;
	vector<vector<int>> matrix;
	int target;
	matrix = { { 1, 4, 7, 11, 15 },
		{ 2, 5, 8, 12, 19 },
		{ 3, 6, 9, 16, 22 },
		{ 10, 13, 14, 17, 24 },
		{ 18, 21, 23, 26, 30 } };
	target = 5;
	cout << sol.searchMatrix(matrix, target) << endl;
	target = 20;
	cout << sol.searchMatrix(matrix, target) << endl;
}