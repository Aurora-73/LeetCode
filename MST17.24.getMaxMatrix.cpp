// Created: 2026-01-08
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个正整数、负整数和 0 组成的 N × M矩阵，编写代码找出元素总和最大的子矩阵。
返回一个数组 {r1, c1, r2, c2}，其中 r1, c1 分别代表子矩阵左上角的行号和列号，
r2, c2 分别代表右下角的行号和列号。若有多个满足条件的子矩阵，返回任意一个均可。
注意：本题相对书上原题稍作改动
示例：
输入：
	{
	  {-1,0},
	  {0,-1}
	}
输出：
    {0,1,0,1}
	解释：输入中标粗的元素即为输出所表示的矩阵
说明：
	1 <= matrix.length, matrix{0}.length <= 200 */

class Solution1 {
public:
	vector<int> getMaxMatrix(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size();
		int max_sum = matrix[0][0];
		vector<int> res { 0, 0, 0, 0 };
		for(int i = 1; i < m; ++i) {
			matrix[i][0] += matrix[i - 1][0];
		}
		for(int j = 1; j < n; ++j) {
			matrix[0][j] += matrix[0][j - 1];
		}
		for(int i = 1; i < m; ++i) {
			for(int j = 1; j < n; ++j) {
				matrix[i][j] += matrix[i - 1][j] + matrix[i][j - 1] - matrix[i - 1][j - 1];
			}
		}
		for(int ei = 0; ei < m; ++ei) {
			for(int ej = 0; ej < n; ++ej) {
				for(int bi = 0; bi <= ei; ++bi) {
					for(int bj = 0; bj <= ej; ++bj) {
						int curr = matrix[ei][ej] + (bi & bj ? matrix[bi - 1][bj - 1] : 0)
						    - (bj ? matrix[ei][bj - 1] : 0) - (bi ? matrix[bi - 1][ej] : 0);
						if(curr > max_sum) {
							max_sum = curr;
							res = { bi, bj, ei, ej };
						}
					}
				}
			}
		}
		return res;
	}
};

class Solution2 {
public:
	vector<int> getMaxMatrix(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size();
		int max_sum = matrix[0][0];
		vector<int> res { 0, 0, 0, 0 };
		for(int i = 0; i < m; ++i) {
			for(int j = 1; j < n; ++j) {
				matrix[i][j] += matrix[i][j - 1];
			}
		}
		for(int ej = 0; ej < n; ++ej) {
			for(int bj = 0; bj <= ej; ++bj) {
				// 降维之后求最大子数组，贪心的前缀和
				int sum = 0, best_begin = 0, best_prev = 0;
				for(int i = 0; i < m; ++i) {
					int curr = matrix[i][ej] - (bj ? matrix[i][bj - 1] : 0);
					sum += curr;
					if(sum - best_prev > max_sum) {
						max_sum = sum - best_prev;
						res = { best_begin, bj, i, ej };
					}
					if(sum < best_prev) {
						best_prev = sum;
						best_begin = i + 1;
					}
				}
			}
		}
		return res;
	}
}; // 先对每一行求前缀和，然后遍历开始和结束行，通过前缀和求出每一行的部分和，然后在部分和的维数组上求最大子数组 O(n^2 * m)

class Solution3 {
public:
	vector<int> getMaxMatrix(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size();
		int max_sum = matrix[0][0];
		vector<int> res { 0, 0, 0, 0 };
		// 对每一列做前缀和
		for(int j = 0; j < n; ++j) {
			for(int i = 1; i < m; ++i) {
				matrix[i][j] += matrix[i - 1][j];
			}
		}
		// 固定上边界和下边界，降维为一维最大子数组
		for(int ei = 0; ei < m; ++ei) {
			for(int bi = 0; bi <= ei; ++bi) {
				int sum = 0, best_begin = 0, best_prev = 0;
				for(int j = 0; j < n; ++j) {
					int curr = matrix[ei][j] - (bi ? matrix[bi - 1][j] : 0);
					sum += curr;
					if(sum - best_prev > max_sum) {
						max_sum = sum - best_prev;
						res = { bi, best_begin, ei, j };
					}
					if(sum < best_prev) {
						best_prev = sum;
						best_begin = j + 1;
					}
				}
			}
		}
		return res;
	}
}; // 先对每一列求前缀和，然后遍历开始和结束列，通过前缀和求出每一列的部分和，然后在部分和的维数组上求最大子数组 O(m^2 * n)

class Solution {
public:
	vector<int> getMaxMatrix(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size();
		if(m > n) {
			return nSmall(matrix);
		} else {
			return mSmall(matrix);
		}
	}

private:
	vector<int> nSmall(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size();
		int max_sum = matrix[0][0];
		vector<int> res { 0, 0, 0, 0 };
		for(int i = 0; i < m; ++i) {
			for(int j = 1; j < n; ++j) {
				matrix[i][j] += matrix[i][j - 1];
			}
		}
		for(int ej = 0; ej < n; ++ej) {
			for(int bj = 0; bj <= ej; ++bj) {
				// 降维之后求最大子数组，贪心的前缀和
				int sum = 0, best_begin = 0, best_prev = 0;
				for(int i = 0; i < m; ++i) {
					int curr = matrix[i][ej] - (bj ? matrix[i][bj - 1] : 0);
					sum += curr;
					if(sum - best_prev > max_sum) {
						max_sum = sum - best_prev;
						res = { best_begin, bj, i, ej };
					}
					if(sum < best_prev) {
						best_prev = sum;
						best_begin = i + 1;
					}
				}
			}
		}
		return res;
	}
	vector<int> mSmall(vector<vector<int>> &matrix) {
		int m = matrix.size(), n = matrix[0].size();
		int max_sum = matrix[0][0];
		vector<int> res { 0, 0, 0, 0 };
		// 对每一列做前缀和
		for(int j = 0; j < n; ++j) {
			for(int i = 1; i < m; ++i) {
				matrix[i][j] += matrix[i - 1][j];
			}
		}
		// 固定上边界和下边界，降维为一维最大子数组
		for(int ei = 0; ei < m; ++ei) {
			for(int bi = 0; bi <= ei; ++bi) {
				int sum = 0, best_begin = 0, best_prev = 0;
				for(int j = 0; j < n; ++j) {
					int curr = matrix[ei][j] - (bi ? matrix[bi - 1][j] : 0);
					sum += curr;
					if(sum - best_prev > max_sum) {
						max_sum = sum - best_prev;
						res = { bi, best_begin, ei, j };
					}
					if(sum < best_prev) {
						best_prev = sum;
						best_begin = j + 1;
					}
				}
			}
		}
		return res;
	}
}; // 前两个的结合，根据数组的维度选择最小的那个

int main() {
	Solution sol;
	vector<vector<int>> matrix;
	matrix = { { -4, -5 } };
	cout << sol.getMaxMatrix(matrix) << endl;

	matrix = { { -1, 0 }, { 0, -1 } };
	cout << sol.getMaxMatrix(matrix) << endl;

	matrix = { { -1, -2, -9, 6 }, { 8, -9, -3, -6 }, { 2, 9, -7, -6 } };
	cout << sol.getMaxMatrix(matrix) << endl;
}