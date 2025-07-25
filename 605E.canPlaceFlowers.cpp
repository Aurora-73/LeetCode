// Created: 2025-07-03
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 605. 种花问题
假设有一个很长的花坛，一部分地块种植了花，另一部分却没有。
可是，花不能种植在相邻的地块上，它们会争夺水源，两者都会死去。
给你一个整数数组flowerbed 表示花坛，由若干 0 和 1 组成，其中 0 表示没种植花，1 表示种植了花。
另有一个数n，能否在不打破种植规则的情况下种入n朵花？能则返回 true，不能则返回 false。
示例 1：
	输入：flowerbed = {1,0,0,0,1}, n = 1
	输出：true
示例 2：
	输入：flowerbed = {1,0,0,0,1}, n = 2
	输出：false
提示：
	1 <= flowerbed.length <= 2 * 10^4
	flowerbed{i} 为 0 或 1
	flowerbed 中不存在相邻的两朵花
	0 <= n <= flowerbed.length */

class Solution {
public:
	bool canPlaceFlowers(vector<int> &flowerbed, int n) {
		int i = 0, block_cnt = 0, m = flowerbed.size();
		while(i < m && flowerbed[i] == 0) ++i;
		n -= (i + (i == m)) / 2;
		for(; i < m; ++i) {
			if(flowerbed[i] == 0) {
				++block_cnt;
			} else {
				n -= (block_cnt - 1) / 2, block_cnt = 0;
			}
		}
		n -= block_cnt / 2;
		return n <= 0;
	}
};
// 中间的空格长度为 a 则可以加种 (a - 1) / 2 朵花，
// 左右两侧则为 a / 2，全空则为 (a + 1) / 2

class Solution {
public:
	bool canPlaceFlowers(vector<int> &flowerbed, int n) {
		int m = flowerbed.size();
		for(int i = 0; i < m; i++) {
			if((i == 0 || flowerbed[i - 1] == 0) && flowerbed[i] == 0
			    && (i == m - 1 || flowerbed[i + 1] == 0)) {
				n--;
				i++; // 下一个位置肯定不能种花，直接跳过
			}
		}
		return n <= 0;
	}
};
// 贪心算法，能种花立刻种，条件：f[i] == f[i - 1] == f[i - 2] == 0

int main() {
	Solution sol;
	vector<int> flowerbed;
	int n;
	flowerbed = { 1, 0, 0, 0, 1 }, n = 2;
	cout << sol.canPlaceFlowers(flowerbed, n) << endl; // true
	flowerbed = { 1, 0, 0, 0, 1 }, n = 1;
	cout << sol.canPlaceFlowers(flowerbed, n) << endl; // false
}