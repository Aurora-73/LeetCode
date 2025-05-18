// Created: 2025-05-18
#include "MyUtils.h"

/*69. x 的平方根 
给你一个非负整数 x ，计算并返回 x 的 算术平方根 。
由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5。*/

class Solution {
public:
	int mySqrt(int x) {
		int left = 1, right = x;
		while(left < right) {
			int mid = left + (right - left) / 2;
			long long mid2 = mid * mid;
			if(mid2 == x) {
				return mid;
			} else if(mid2 < x) {
				right = mid;
			} else {
				left = mid;
			}
		}
		return left;
	}
};
// 二分查找，找 [0, x - 1] 内的最后一个小于等于 x 的算术平方根的整数

int main() {
	Solution sol;
}