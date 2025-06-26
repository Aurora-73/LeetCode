// Created: 2025-06-25
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 121. 寻找目标值 - 二维数组
m*n 的二维数组 plants 记录了园林景观的植物排布情况，具有以下特性：
	每行中，每棵植物的右侧相邻植物不矮于该植物；
	每列中，每棵植物的下侧相邻植物不矮于该植物。
请判断 plants 中是否存在目标高度值 target。
示例 1：
	输入：plants = {{2,3,6,8},{4,5,8,9},{5,9,10,12}}, target = 8
	输出：true
示例 2：
	输入：plants = {{1,3,5},{2,5,7}}, target = 4
	输出：false
提示：
	0 <= n <= 1000
	0 <= m <= 1000 */

class Solution {
public:
	bool findTargetIn2DPlants(vector<vector<int>> &plants, int target) {
		if(plants.empty()) return false;
		int m = plants.size(), n = plants[0].size();
		int i = 0, j = n - 1;
		while(i < m && j >= 0) {
			int right_up_val = plants[i][j];
			if(right_up_val < target) {
				++i;
			} else if(right_up_val > target) {
				--j;
			} else {
				return true;
			}
		}
		return false;
	}
}; // 右上角的元素是本行的最大值，本列的最小值，用该元素可以一次排除一行或一列，时间复杂度O(m + n)

class Solution {
public:
	bool findTargetIn2DPlants(vector<vector<int>> &plants, int target) {
		if(plants.empty()) return false;
		int m = plants.size(), n = plants[0].size();
		int i = m - 1, j = 0;
		while(i >= 0 && j < n) {
			int left_down_val = plants[i][j];
			if(left_down_val < target) {
				++j;
			} else if(left_down_val > target) {
				--i;
			} else {
				return true;
			}
		}
		return false;
	}
}; // 左下角同理

int main() {
	Solution sol;
	vector<vector<int>> plants;
	int target;
	plants = { { 2, 3, 6, 8 }, { 4, 5, 8, 9 }, { 5, 9, 10, 12 } }, target = 8;
	cout << sol.findTargetIn2DPlants(plants, target) << endl; // true
	plants = { { 1, 3, 5 }, { 2, 5, 7 } }, target = 4;
	cout << sol.findTargetIn2DPlants(plants, target) << endl; // false
}