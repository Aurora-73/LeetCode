// Created: 2025-07-09
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 875. 爱吃香蕉的珂珂
珂珂喜欢吃香蕉。
这里有 n 堆香蕉，第 i 堆中有piles{i}根香蕉。警卫已经离开了，将在 h 小时后回来。
珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 k 根。
如果这堆香蕉少于 k 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。
珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。
示例 1：
	输入：piles = {3,6,7,11}, h = 8
	输出：4
示例 2：
	输入：piles = {30,11,23,4,20}, h = 5
	输出：30
示例 3：
	输入：piles = {30,11,23,4,20}, h = 6
	输出：23
提示：
	1 <= piles.length <= 10^4
	piles.length <= h <= 10^9
	1 <= piles{i} <= 10^9 */

class Solution {
public:
	int minEatingSpeed(vector<int> &piles, int h) {
		long long sum = 0;
		int r = 0;
		for(auto p : piles) {
			sum += p;
			r = max(r, p);
		}
		++r;
		int l = max(int(sum / (h + 1)), 1); // 也可以直接初始化为 1
		while(l < r) {                      // 左闭右开
			int mid = l + (r - l) / 2;
			if(canEat(piles, h, mid)) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}
		return l;
	}

private:
	bool canEat(vector<int> &piles, int h, int k) {
		for(auto p : piles) {
			h -= (p - 1) / k + 1; // 向上取整的除法
		}
		return h >= 0;
	}
};

int main() {
	Solution sol;
	vector<int> piles;
	int h;
	piles = { 3, 6, 7, 11 }, h = 8;
	cout << sol.minEatingSpeed(piles, h) << endl; // 4
	piles = { 30, 11, 23, 4, 20 }, h = 5;
	cout << sol.minEatingSpeed(piles, h) << endl; // 30
	piles = { 30, 11, 23, 4, 20 }, h = 6;
	cout << sol.minEatingSpeed(piles, h) << endl; // 23
}