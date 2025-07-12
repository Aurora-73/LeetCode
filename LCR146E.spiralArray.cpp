// Created: 2025-06-23
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 146. 螺旋遍历二维数组
给定一个二维数组 array，请返回「螺旋遍历」该数组的结果。
螺旋遍历：从左上角开始，按照 向右、向下、向左、向上 的顺序 依次 提取元素，然后再进入内部一层重复相同的步骤，直到提取完所有元素。
示例 1：
	输入：array = {{1,2,3},{8,9,4},{7,6,5}}
	输出：{1,2,3,4,5,6,7,8,9}
示例 2：
	输入：array = {{1,2,3,4},{12,13,14,5},{11,16,15,6},{10,9,8,7}}
	输出：{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}
	限制：
	0 <= array.length <= 100
	0 <= array{i}.length <= 100
 */

class Solution {
public:
	vector<int> spiralArray(vector<vector<int>> &array) {
		if(array.empty()) return {};
		int m = array.size(), n = array[0].size();
		int left = 0, right = n - 1, up = 0, down = m - 1;
		vector<int> res;
		res.reserve(m * n);
		while(left <= right && up <= down) {
			for(int j = left; j <= right; ++j) {
				res.push_back(array[up][j]);
			}
			++up;
			for(int i = up; i <= down; ++i) {
				res.push_back(array[i][right]);
			}
			--right;
			if(left > right || up > down) break; // 防止单行单列的情况出现重复
			for(int j = right; j >= left; --j) {
				res.push_back(array[down][j]);
			}
			--down;
			for(int i = down; i >= up; --i) {
				res.push_back(array[i][left]);
			}
			++left;
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<vector<int>> array;
	array = { { 1, 2, 3, 4 } };
	cout << sol.spiralArray(array) << endl;
	array = { { 1 }, { 2 }, { 3 }, { 4 } };
	cout << sol.spiralArray(array) << endl;
	array = { { 1, 2, 3 }, { 8, 9, 4 }, { 7, 6, 5 } };
	cout << sol.spiralArray(array) << endl;
	array = { { 1, 2, 3, 4 }, { 12, 13, 14, 5 }, { 11, 16, 15, 6 }, { 10, 9, 8, 7 } };
	cout << sol.spiralArray(array) << endl;
}