// Created: 2025-06-12
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 240. 搜索二维矩阵 II
编写一个高效的算法来搜索mxn矩阵 matrix 中的一个目标值 target。
该矩阵具有以下特性：
	每行的元素从左到右升序排列。
	每列的元素从上到下升序排列。
示例 1：
	输入：matrix = {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}}, target = 5
	输出：true
示例 2：
	输入：matrix = {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}}, target = 20
	输出：false
提示：
	m == matrix.length
	n == matrix{i}.length
	1 <= n, m <= 300
	-10^9<= matrix{i}{j} <= 10^9
	每行的所有元素从左到右升序排列
	每列的所有元素从上到下升序排列
	-10^9<= target <= 10^9 */

class Solution1 {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		int m = matrix.size(), n = matrix[0].size();
		for(int index = 0; index < m; ++index) {
			if(matrix[index].front() == target || matrix[index].back() == target) {
				return true;
			} else if(matrix[index].front() < target && matrix[index].back() > target) {
				int i = 0, j = n, mid;
				while(i < j) {
					mid = i + (j - i) / 2;
					if(matrix[index][mid] == target) {
						return true;
					} else if(matrix[index][mid] < target) {
						i = mid + 1;
					} else {
						j = mid;
					}
				}
			}
		}
		return false;
	}
};

class Solution2 {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		int n = matrix.size();
		for(int index = 0; index < n; ++index) {
			if(matrix[index].front() == target || matrix[index].back() == target) {
				return true;
			} else if(matrix[index].front() < target && matrix[index].back() > target) {
				auto it = lower_bound(matrix[index].begin(), matrix[index].end(), target);
				if(*it == target) {
					return true;
				}
			}
		}
		return false;
	}
};

class Solution {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		int m = matrix.size(), n = matrix[0].size();
		int i = 0, j = n - 1;
		while(i < m && j >= 0) {
			if(matrix[i][j] == target) {
				return true;
			} else if(matrix[i][j] > target) {
				j--;
			} else {
				i++;
			}
		}
		return false;
	}
};
/* 利用了矩阵「行递增、列递增」的特点 O(m + n)。
在「右上角」时：
    若等于目标，直接返回 true。
    若大于目标，由于本列下面的值更大，所以不可能在本列，向左移动 j--。
    若小于目标，由于本行左边的值更小，所以不可能在本行，向下移动 i++。
当指针越出边界（行走到末尾或列走到最左之前）仍未找到，则矩阵中不存在该值，返回 false。*/

int main() {
	Solution sol;
	vector<vector<int>> matrix;
	int target;
	matrix = { { 1, 4 }, { 2, 5 } };
	target = 4;
	cout << sol.searchMatrix(matrix, target) << endl; // true
	matrix = { { 1, 4, 7, 11, 15 },
		{ 2, 5, 8, 12, 19 },
		{ 3, 6, 9, 16, 22 },
		{ 10, 13, 14, 17, 24 },
		{ 18, 21, 23, 26, 30 } };
	target = 5;
	cout << sol.searchMatrix(matrix, target) << endl; // true
	matrix = { { 1, 4, 7, 11, 15 },
		{ 2, 5, 8, 12, 19 },
		{ 3, 6, 9, 16, 22 },
		{ 10, 13, 14, 17, 24 },
		{ 18, 21, 23, 26, 30 } };
	target = 20;
	cout << sol.searchMatrix(matrix, target) << endl; // false
}