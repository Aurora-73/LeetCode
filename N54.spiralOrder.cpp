#include "MyUtils.h"

class Solution {
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
			if(top > bottom || left > right)
				break; // 防止单行/列时出现重复
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

class Solution1 {
public:
	vector<int> spiralOrder(vector<vector<int>> &matrix) {
		vector<int> vec(matrix[0].size() * matrix.size());
		int step_y = matrix.size() - 1, step_x = matrix[0].size();
		int y = 0, x = -1, now = 0, moved_step = 0;
		int count = 2;
		bool move_x = true, move_add = true;
		while(now < vec.size()) {
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
};

int main() {
	Solution sol;
	Solution1 sol1;
	vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	cout << sol.spiralOrder(matrix) << endl;
	cout << sol1.spiralOrder(matrix) << endl;
	matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
	cout << sol.spiralOrder(matrix) << endl;
	cout << sol1.spiralOrder(matrix) << endl;
}
