// Created: 2025-05-14
#include "MyUtils.h"

/*74. 搜索二维矩阵
给你一个满足下述两条属性的 m x n 整数矩阵：
每行中的整数从左到右按非严格递增顺序排列。
每行的第一个整数大于前一行的最后一个整数。
给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。*/

// 二维非常复杂，赋值的时候还要+1要考虑是否进位
// 左闭右闭 二维
class Solution12 {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		if(matrix.empty() || matrix[0].empty())
			return false;
		int n = matrix.size(), m = matrix[0].size(); // 不一定是方形
		int left_i = 0, left_j = 0, right_i = n - 1, right_j = m - 1; // 左闭右闭
		while(left_i * m + left_j <= right_i * m + right_j) {
			int middle = ((right_i - left_i) * m + right_j - left_j) / 2 + left_i * m + left_j;
			int mid_i = middle / m, mid_j = middle % m;
			int &mid_val = matrix[mid_i][mid_j];
			if(target == mid_val) {
				return true;
			} else if(target < mid_val) {
				middle -= 1; // 直接给 right_j ± 1 可能导致进位或者 -1 的情况，必须重新计算
				right_i = middle / m;
				right_j = middle % m;
			} else {
				middle += 1;
				left_i = middle / m;
				left_j = middle % m;
			}
		}
		return false;
	}
};

// 左闭右闭 一维
class Solution11 {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		int n = matrix.size(), m = matrix[0].size();
		int left = 0, right = n * m - 1, mid, mid_val;
		while(left <= right) {
			mid = left + (right - left) / 2;
			mid_val = matrix[mid / m][mid % m];
			if(target == mid_val) {
				return true;
			} else if(target < mid_val) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}
		return false;
	}
};

// 左闭右闭 二维
class Solution22 {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		if(matrix.empty() || matrix[0].empty())
			return false;
		int n = matrix.size(), m = matrix[0].size(); // 不一定是方形
		int left_i = 0, left_j = 0, right_i = n - 1, right_j = m; // 左闭右开
		while(left_i * m + left_j < right_i * m + right_j) {
			int middle = ((right_i - left_i) * m + right_j - left_j) / 2 + left_i * m + left_j;
			int mid_i = middle / m, mid_j = middle % m;
			int &mid_val = matrix[mid_i][mid_j];
			if(target == mid_val) {
				return true;
			} else if(target < mid_val) {
				right_i = mid_i;
				right_j = mid_j;
			} else {
				middle += 1; // 直接给 right_j ± 1 可能导致进位或者 -1 的情况，必须重新计算  // 注意这里仍要加1
				left_i = middle / m;
				left_j = middle % m;
			}
		}
		return false;
	}
};

// 左闭右开 一维
class Solution21 {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		int n = matrix.size(), m = matrix[0].size();
		int left = 0, right = n * m, mid, mid_val;
		while(left < right) {
			mid = left + (right - left) / 2;
			mid_val = matrix[mid / m][mid % m];
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

int main() {
	Solution11 sol11;
}