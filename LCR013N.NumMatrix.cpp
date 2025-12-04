// Created: 2025-10-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个二维矩阵 matrix，以下类型的多个请求：
	计算其子矩形范围内元素的总和，该子矩阵的左上角为 (row1,col1)，右下角为 (row2,col2)。
实现 NumMatrix 类：
	NumMatrix(int{}{} matrix)给定整数矩阵 matrix 进行初始化
	int sumRegion(int row1, int col1, int row2, int col2)返回左上角 (row1,col1)、右下角(row2,col2)的子矩阵的元素总和。

示例 1：
	输入: 
	{"NumMatrix","sumRegion","sumRegion","sumRegion"}
	{{{{3,0,1,4,2},{5,6,3,2,1},{1,2,0,1,5},{4,1,0,1,7},{1,0,3,0,5}}},{2,1,4,3},{1,1,2,2},{1,2,2,4}}
	输出: 
	{null, 8, 11, 12}
	解释:
	NumMatrix numMatrix = new NumMatrix({{3,0,1,4,2},{5,6,3,2,1},{1,2,0,1,5},{4,1,0,1,7},{1,0,3,0,5}}});
	numMatrix.sumRegion(2, 1, 4, 3); // return 8 (红色矩形框的元素总和)
	numMatrix.sumRegion(1, 1, 2, 2); // return 11 (绿色矩形框的元素总和)
	numMatrix.sumRegion(1, 2, 2, 4); // return 12 (蓝色矩形框的元素总和)
提示：
	m == matrix.length
	n == matrix{i}.length
	1 <= m,n <=200
	-10^5<= matrix{i}{j} <= 10^5
	0 <= row1 <= row2 < m
	0 <= col1 <= col2 < n
	最多调用 10^4 次sumRegion 方法
注意：本题与主站 304题相同： */

class NumMatrix {
public:
	NumMatrix(vector<vector<int>> matrix) {
		int m = matrix.size(), n = matrix[0].size();
		for(int i = 1; i < m; ++i) {
			matrix[i][0] += matrix[i - 1][0];
		}
		for(int j = 1; j < n; ++j) {
			matrix[0][j] += matrix[0][j - 1];
		}
		for(int i = 1; i < m; ++i) {
			for(int j = 1; j < n; ++j) {
				matrix[i][j]
				    = matrix[i][j] + matrix[i - 1][j] + matrix[i][j - 1] - matrix[i - 1][j - 1];
			}
		}
		prefix = std::move(matrix);
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		row1--, col1--;
		int a = prefix[row2][col2];
		int b = row1 < 0 ? 0 : (col1 < 0 ? 0 : prefix[row1][col1]);
		int c = row1 < 0 ? 0 : prefix[row1][col2];
		int d = col1 < 0 ? 0 : prefix[row2][col1];
		return a + b - c - d;
	}

private:
	vector<vector<int>> prefix;
};

int main() {
	vector<vector<int>> matrix;
	matrix = { { { 3, 0, 1, 4, 2 },
		{ 5, 6, 3, 2, 1 },
		{ 1, 2, 0, 1, 5 },
		{ 4, 1, 0, 1, 7 },
		{ 1, 0, 3, 0, 5 } } };
	NumMatrix nm(matrix);
	cout << nm.sumRegion(2, 1, 4, 3) << endl;
	cout << nm.sumRegion(1, 1, 2, 2) << endl;
	cout << nm.sumRegion(1, 2, 2, 4) << endl;
}