// Created: 2025-05-14
#include "MyUtils.h"

/*74. 搜索二维矩阵
给你一个满足下述两条属性的 cols x rows 整数矩阵：
每行中的整数从左到右按非严格递增顺序排列。
每行的第一个整数大于前一行的最后一个整数。
给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。*/

// 二维非常复杂，赋值的时候还要 ±1 要考虑是否进位或借位
// 左闭右开 二维
class Solution22 {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		if(matrix.empty() || matrix[0].empty()) return false;
		int rows = matrix.size(), cols = matrix[0].size(); // 不一定是方形
		int left_i = 0, left_j = 0, right_i = rows - 1, right_j = cols; // 左闭右开
		while(left_i * cols + left_j < right_i * cols + right_j) {
			int middle = ((right_i - left_i) * cols + right_j - left_j) / 2 + left_i * cols + left_j;
			int mid_i = middle / cols, mid_j = middle % cols;
			int &mid_val = matrix[mid_i][mid_j];
			if(target == mid_val) {
				return true;
			} else if(target < mid_val) {
				right_i = mid_i;
				right_j = mid_j;
			} else {
				middle += 1; // 直接给 right_j ± 1 可能导致进位或者 -1 的情况，必须重新计算  // 注意这里仍要加1
				left_i = middle / cols;
				left_j = middle % cols;
			}
		}
		return false;
	}
};

// 左闭右开 一维
class Solution21 {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		int rows = matrix.size(), cols = matrix[0].size();
		int left = 0, right = rows * cols, mid, mid_val;
		while(left < right) {
			mid = left + (right - left) / 2;
			mid_val = matrix[mid / cols][mid % cols];
			if(target == mid_val) {
				return true;
			} else if(target < mid_val) {
				right = mid;
			} else {
				left = mid + 1; // 注意这里仍要加1
			}
		}
		return false;
	}
};

class Solution {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		if(matrix.empty() || matrix[0].empty()) return false;
		int rows = matrix.size(), up = 0, down = rows; // 左闭右开
		while(up < down) {
			int mid = up + (down - up) / 2, mid_val = matrix[mid].back();
			if(mid_val == target) {
				return true;
			} else if(mid_val > target) {
				down = mid;
			} else {
				up = mid + 1;
			}
		} // 二分查找结束时的当前值大于等于target
		if(up == rows) { // 在这里等价于 up < 0 || up > rows - 1
			return false;
		}
		int cols = matrix[0].size(), left = 0, right = cols; // 左闭右开
		while(left < right) {
			int mid = left + (right - left) / 2, mid_val = matrix[up][mid];
			if(mid_val == target) {
				return true;
			} else if(mid_val > target) {
				right = mid;
			} else {
				left = mid + 1;
			}
		}
		return false;
	}
}; // O(logn+logm) 先查找在哪行，再查找在哪列

int main() {
	Solution sol;
}