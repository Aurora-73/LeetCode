#include "MyUtils.hpp"

/*73. 矩阵置零
给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。*/

class Solution {
public:
	void setZeroes(vector<vector<int>> &matrix) {
		int n = matrix.size(), m = matrix[0].size();
		bool x0 = false, y0 = false;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(matrix[i][j] == 0) {
					if(i == 0)
						x0 = true;
					else
						matrix[i][0] = 0;
					if(j == 0)
						y0 = true;
					else
						matrix[0][j] = 0;
				}
			}
		}
		for(int i = 1; i < n; i++) {
			if(matrix[i][0] == 0) {
				for(int j = 0; j < m; j++) {
					matrix[i][j] = 0;
				}
			}
		}
		for(int j = 1; j < m; j++) {
			if(matrix[0][j] == 0) {
				for(int i = 0; i < n; i++) {
					matrix[i][j] = 0;
				}
			}
		}
		if(x0) {
			for(int j = 0; j < m; j++) matrix[0][j] = 0;
		}
		if(y0) {
			for(int i = 0; i < n; i++) matrix[i][0] = 0;
		}
	}
};
/*边找边改问题在于清零产生的0可能被当成原本就有的0，
因此最简单的方法就是设两个数组，标记某一行或者某一列是否需要清空
空间复杂度O(1)的做法是：
以第一行和第一列作为改行或列是否清零的标记，从第二行和第二列开始，
每遇到一个0就将其对应的行或列的开头设为0，作为标记，最后清空这些行列即可
但是这样第一行和第一列是否清零就需要两个单独的bool来保存*/

int main() { }