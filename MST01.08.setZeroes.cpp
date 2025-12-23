// Created: 2025-12-23
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 编写一种算法，若M × N矩阵中某个元素为0，则将其所在的行与列清零。
示例 1：
	输入：
	{
	  {1,1,1},
	  {1,0,1},
	  {1,1,1}
	}
	输出：
	{
	  {1,0,1},
	  {0,0,0},
	  {1,0,1}
	}
示例 2：
	输入：
	{
	  {0,1,2,0},
	  {3,4,5,2},
	  {1,3,1,5}
	}
	输出：
	{
	  {0,0,0,0},
	  {0,4,5,0},
	  {0,3,1,0}
	} */

class Solution1 {
public:
	void setZeroes(vector<vector<int>> &matrix) {
		if(matrix.size() == 0) return;
		int m = matrix.size(), n = matrix[0].size();
		vector<bool> line(m, 0), cow(n, 0);
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				if(matrix[i][j] == 0) {
					line[i] = true;
					cow[j] = true;
				}
			}
		}
		for(int i = 0; i < m; ++i) {
			if(line[i]) {
				for(int k = 0; k < n; ++k) {
					matrix[i][k] = 0;
				}
			}
		}
		for(int j = 0; j < n; ++j) {
			if(cow[j]) {
				for(int k = 0; k < m; ++k) {
					matrix[k][j] = 0;
				}
			}
		}
	}
}; // 用单独的数组记录需要删除的行和列

class Solution {
public:
	void setZeroes(vector<vector<int>> &matrix) {
		if(matrix.empty() || matrix[0].empty()) return;
		int m = matrix.size(), n = matrix[0].size();

		bool firstRowHasZero = false, firstColHasZero = false;
		// 检查第一行是否有零
		for(int j = 0; j < n; ++j) {
			if(matrix[0][j] == 0) {
				firstRowHasZero = true;
				break;
			}
		}
		// 检查第一列是否有零
		for(int i = 0; i < m; ++i) {
			if(matrix[i][0] == 0) {
				firstColHasZero = true;
				break;
			}
		}

		// 标记需要清零的行列
		for(int i = 1; i < m; ++i) {
			for(int j = 1; j < n; ++j) {
				if(matrix[i][j] == 0) {
					matrix[i][0] = 0; // 标记该行
					matrix[0][j] = 0; // 标记该列
				}
			}
		}
		// 清零标记行
		for(int i = 1; i < m; ++i) {
			if(matrix[i][0] == 0) {
				for(int j = 1; j < n; ++j) {
					matrix[i][j] = 0;
				}
			}
		}
		// 清零标记列
		for(int j = 1; j < n; ++j) {
			if(matrix[0][j] == 0) {
				for(int i = 1; i < m; ++i) {
					matrix[i][j] = 0;
				}
			}
		}

		// 清零第一行
		if(firstRowHasZero) {
			for(int j = 0; j < n; ++j) {
				matrix[0][j] = 0;
			}
		}
		// 清零第一列
		if(firstColHasZero) {
			for(int i = 0; i < m; ++i) {
				matrix[i][0] = 0;
			}
		}
	}
}; // 直接用第一行和第一列记录需要删除的行和列，注意这时需要两个单独的变量记录第一行和第一列是否需要清零，并且需要单独处理第一行和第一列

int main() {
	Solution sol;
	vector<vector<int>> matrix;
	matrix = { { 0, 1 } };
	sol.setZeroes(matrix);
	cout << matrix << endl;

	matrix = { { 1, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 } };
	sol.setZeroes(matrix);
	cout << matrix << endl;

	matrix = { { 0, 1, 2, 0 }, { 3, 4, 5, 2 }, { 1, 3, 1, 5 } };
	sol.setZeroes(matrix);
	cout << matrix << endl;
}