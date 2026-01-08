// Created: 2026-01-08
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个直方图(也称柱状图)，假设有人从上面源源不断地倒水，最后直方图能存多少水量?直方图的宽度为 1。
上面是由数组 {0,1,0,2,1,0,1,3,2,1,2,1} 表示的直方图，
在这种情况下，可以接 6 个单位的水（蓝色部分表示水）。感谢 Marcos 贡献此图。
示例：
输入：{0,1,0,2,1,0,1,3,2,1,2,1}
输出：6 */

class Solution {
public:
	int trap(vector<int> &height) {
		int n = height.size();
		vector<int> right(n);
		// 填充
		for(int i = n - 2; i >= 0; --i) {
			right[i] = max(right[i + 1], height[i + 1]);
		}
		int res = 0, left = 0;
		for(int i = 1; i < n; ++i) {
			left = max(left, height[i - 1]);
			res += max(0, min(left, right[i]) - height[i]);
		}
		return res;
	}
};

int main() {
	Solution sol;
	vector<int> height;
	height = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
	cout << sol.trap(height) << endl;
	height = { 0,
		1,
		0,
		2,
		23,
		3423,
		4321,
		4,
		234,
		123312,
		3,
		123,
		12,
		4,
		23,
		666,
		5234,
		5,
		3214,
		65,
		2534,
		5,
		312454,
		12,
		5,
		431,
		541,
		26,
		452,
		6,
		436,
		452,
		6413,
		524,
		5134146,
		6578,
		7657,
		2435,
		5614,
		567656,
		23,
		1,
		0,
		1,
		3,
		2,
		1,
		2,
		1 };
	cout << sol.trap(height) << endl;
}