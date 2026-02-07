// Created: 2025-04-21
#include "MyUtils.hpp"

/* 48. 旋转图像
给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。
示例 1：
	输入：matrix = {{1,2,3},{4,5,6},{7,8,9}}
	输出：{{7,4,1},{8,5,2},{9,6,3}}
示例 2：
	输入：matrix = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}}
	输出：{{15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11}}
提示：
	n == matrix.length == matrix{i}.length
	1 <= n <= 20
	-1000 <= matrix{i}{j} <= 1000 */

class Solution1 {
public:
	void rotate(vector<vector<int>> &matrix) {
		int n = matrix.size(), less = 0, large = n - 1;
		while(less < large) {
			for(int i = 0; i < large - less; ++i) {
				int temp = matrix[less][less + i];
				matrix[less][less + i] = matrix[large - i][less];
				matrix[large - i][less] = matrix[large][large - i];
				matrix[large][large - i] = matrix[less + i][large];
				matrix[less + i][large] = temp;
			}
			++less, --large;
		}
	}
}; // 直接模拟

class Solution {
public:
	void rotate(vector<vector<int>> &matrix) {
		int n = matrix.size();
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < i; j++) {
				swap(matrix[i][j], matrix[j][i]);
			}
		} // 先转置
		for(vector<int> &row : matrix) {
			reverse(row.begin(), row.end());
		} // 后翻转
	}
}; // 旋转 = 转置 + 每行反转

int main() {
	Solution sol;
	vector<vector<int>> matrix;
	matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	sol.rotate(matrix);
	cout << matrix << endl;

	matrix = { { 5, 1, 9, 11 }, { 2, 4, 8, 10 }, { 13, 3, 6, 7 }, { 15, 14, 12, 16 } };
	sol.rotate(matrix);
	cout << matrix << endl;
}