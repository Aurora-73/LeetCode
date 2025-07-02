// Created: 2025-07-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 168. 丑数

给你一个整数 n ，请你找出并返回第 n 个 丑数 。
说明：丑数是只包含质因数 2、3、5 的正整数；1 是丑数。

示例 1：
输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。

提示：
	1 <= n<=1690 */

class Solution1 {
public:
	int nthUglyNumber(int n) {
		vector<int> uglyNum(n);
		unordered_set<int> us;
		int indexs[3] = { 0, 0, 0 }, factors[3] = { 2, 3, 5 };
		uglyNum[0] = 1;
		for(int i = 1; i < n; ++i) {
			int min_val = INT_MAX, min_i = 0;
			for(int j = 0; j < 3; ++j) {
				int val = factors[j] * uglyNum[indexs[j]];
				while(us.count(val)) {
					++indexs[j];
					val = factors[j] * uglyNum[indexs[j]];
				}
				if(val < min_val) {
					min_val = factors[j] * uglyNum[indexs[j]];
					min_i = j;
				}
			}
			++indexs[min_i];
			uglyNum[i] = min_val;
			us.insert(min_val);
		}
		return uglyNum.back();
	}
}; // 使用哈希表去除重复，记录每个因子当前的乘数，将最小的积加入

class Solution2 {
public:
	int nthUglyNumber(int n) {
		vector<int> uglyNum;
		int indexs[3] = { 0, 0, 0 }, factors[3] = { 2, 3, 5 };
		uglyNum.reserve(n), uglyNum.push_back(1);
		for(int i = 1; i < n; ++i) {
			int min_val = INT_MAX, min_i = 0;
			for(int j = 0; j < 3; ++j) {
				int this_val = factors[j] * uglyNum[indexs[j]];
				while(this_val <= uglyNum.back()) {
					++indexs[j];
					this_val = factors[j] * uglyNum[indexs[j]];
				}
				if(this_val < min_val) {
					min_val = this_val;
					min_i = j;
				}
			}
			++indexs[min_i];
			uglyNum.push_back(min_val);
		}
		return uglyNum.back();
	}
}; // 利用 uglyNum 递增的性质可以直接去除重复，小于等于上一个值的都是重复的

class Solution {
public:
	int nthUglyNumber(int n) {
		return uglyNum[n];
	} // 打表，不进入 solution 的代码不会被记录
private:
	static int uN() {
		uglyNum[1] = 1;
		int p2 = 1, p3 = 1, p5 = 1;
		for(int i = 2; i < 1691; i++) {
			int num2 = uglyNum[p2] * 2, num3 = uglyNum[p3] * 3, num5 = uglyNum[p5] * 5;
			uglyNum[i] = min(min(num2, num3), num5);
			if(uglyNum[i] == num2) p2++;
			if(uglyNum[i] == num3) p3++;
			if(uglyNum[i] == num5) p5++;
		}
		return 1;
	}; // 计算出当前值后 <每个> 等于当前值的下标都后移，因此也不会重复
	static int uglyNum[1691], a;
};

int Solution::uglyNum[1691], Solution::a = Solution::uN();

int main() {
	Solution sol;
	int n;
	n = 10;
	cout << sol.nthUglyNumber(n) << endl; // 12
	n = 1690;
	cout << sol.nthUglyNumber(n) << endl; // 2123366400
}
