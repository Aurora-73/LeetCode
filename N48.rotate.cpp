#include "MyUtils.h"

/*给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。*/

// 旋转 = 转置 + 每行反转
class Solution1 {
public:
	void rotate(vector<vector<int>> &matrix) {
		int n = matrix.size();
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < i; j++) {
				swap(matrix[i][j], matrix[j][i]);
			}
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n / 2; j++) { // 注意只有一半
				swap(matrix[i][j], matrix[i][n - j - 1]);
			}
		}
	}
};

class Solution2 {
public:
	void rotate(vector<vector<int>> &matrix) {
		int n = matrix.size();
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < i; j++) {
				swap(matrix[i][j], matrix[j][i]);
			}
		}
		for(vector<int> &row : matrix)
			reverse(row.begin(), row.end());
	}
};

int main() {
	Solution1 sol1;
	Solution2 sol2;
	vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	sol1.rotate(matrix);
	cout << matrix << endl;
	sol2.rotate(matrix);
	cout << matrix << endl;
}