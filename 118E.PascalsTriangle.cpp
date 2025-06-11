// Created: 2025-06-11
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 118. 杨辉三角
给定一个非负整数numRows，生成「杨辉三角」的前numRows行。
在「杨辉三角」中，每个数是它左上方和右上方的数的和。
示例 1:
	输入: numRows = 5
	输出: {{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1}}
	示例2:
	输入: numRows = 1
	输出: {{1}}
提示:
	1 <= numRows <= 30 */

class Solution1 {
public:
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> res(numRows);
		res[0] = { 1 };
		for(int i = 1; i < numRows; ++i) {
			res[i].resize(i + 1);
			for(int j = 0; j <= i; ++j) {
				int left = j == 0 ? 0 : res[i - 1][j - 1];
				int right = j == i ? 0 : res[i - 1][j];
				res[i][j] = left + right;
			}
		}
		return res;
	}
}; // 把杨辉三角的每一排左对齐

class Solution2 {
public:
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> res(numRows);
		res[0] = { 1 };
		for(int i = 1; i < numRows; ++i) {
			res[i].resize(i + 1);
			for(int j = 0; j <= i; ++j) {
				res[i][j] = (j > 0 ? res[i - 1][j - 1] : 0) + (j < i ? res[i - 1][j] : 0);
			}
		}
		return res;
	}
};

class Solution {
public:
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> c(numRows);
		for(int i = 0; i < numRows; i++) {
			c[i].resize(i + 1, 1);
			for(int j = 1; j < i; j++) {
				c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
			}
		}
		return c;
	}
};

int main() {
	Solution sol;
	int numRows;
	numRows = 5;
	cout << sol.generate(numRows) << endl;
	numRows = 1;
	cout << sol.generate(numRows) << endl;
}