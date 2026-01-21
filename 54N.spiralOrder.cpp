#include "MyUtils.hpp"

/* 54. 螺旋矩阵
给你一个 m 行 n 列的矩阵matrix，请按照 顺时针螺旋顺序，返回矩阵中的所有元素。
示例 1：
	输入：matrix = {{1,2,3},{4,5,6},{7,8,9}}
	输出：{1,2,3,6,9,8,7,4,5}
示例 2：
	输入：matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12}}
	输出：{1,2,3,4,8,12,11,10,9,5,6,7}
提示：
	m == matrix.length
	n == matrix{i}.length
	1 <= m, n <= 10
	-100 <= matrix{i}{j} <= 100 */

class Solution1 {
public:
	vector<int> spiralOrder(vector<vector<int>> &matrix) {
		vector<int> vec(matrix[0].size() * matrix.size());
		int step_y = matrix.size() - 1, step_x = matrix[0].size();
		int y = 0, x = -1, now = 0, moved_step = 0, n = vec.size();
		int count = 2;
		bool move_x = true, move_add = true;
		while(now < n) {
			if(move_x) {
				if(moved_step < step_x) {
					move_add ? x++ : x--;
					moved_step++;
					vec[now++] = matrix[y][x];
				} else {
					step_x--;
					moved_step = 0;
					move_x = !move_x;
					count--;
					if(!count) {
						move_add = !move_add;
						count = 2;
					}
				}
			} else {
				if(moved_step < step_y) {
					move_add ? y++ : y--;
					moved_step++;
					vec[now++] = matrix[y][x];
				} else {
					step_y--;
					moved_step = 0;
					move_x = !move_x;
					count--;
					if(!count) {
						move_add = !move_add;
						count = 2;
					}
				}
			}
		}
		return vec;
	}
}; // 控制一个位置进行位移，非常复杂

class Solution2 {
public:
	vector<int> spiralOrder(vector<vector<int>> &matrix) {
		vector<int> res;
		int top = 0, bottom = matrix.size() - 1;
		int left = 0, right = matrix[0].size() - 1;
		while(top <= bottom && left <= right) {
			for(int i = left; i <= right; i++) {
				res.push_back(matrix[top][i]);
			}
			top++;
			for(int i = top; i <= bottom; i++) {
				res.push_back(matrix[i][right]);
			}
			right--;
			if(top > bottom || left > right) break; // 防止单行/列时出现重复
			for(int i = right; i >= left; i--) {
				res.push_back(matrix[bottom][i]);
			}
			bottom--;
			for(int i = bottom; i >= top; i--) {
				res.push_back(matrix[i][left]);
			}
			left++;
		}
		return res;
	}
}; // 每次遍历四个边框

class Solution {
public:
	vector<int> spiralOrder(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size();
		vector<int> res;
		res.reserve(m * n);
		int l = 0, r = n - 1, u = 0, d = m - 1;
		bool rd = true;
		while(l <= r && u <= d) {
			if(rd) {
				for(int j = l; j <= r; ++j) {
					res.push_back(matrix[u][j]);
				}
				++u;
				for(int i = u; i <= d; ++i) {
					res.push_back(matrix[i][r]);
				}
				--r;
			} else {
				for(int j = r; j >= l; --j) {
					res.push_back(matrix[d][j]);
				}
				--d;
				for(int i = d; i >= u; --i) {
					res.push_back(matrix[i][l]);
				}
				++l;
			}
			rd ^= 1;
		}
		return res;
	}
};

int main() {
	Solution sol;
	Solution1 sol1;
	vector<vector<int>> matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	cout << sol.spiralOrder(matrix) << endl;
	cout << sol1.spiralOrder(matrix) << endl;
	matrix = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } };
	cout << sol.spiralOrder(matrix) << endl;
	cout << sol1.spiralOrder(matrix) << endl;
}
