// Created: 2025-05-18
#include "MyUtils.h"

/*69. x 的平方根 
给你一个非负整数 x ，计算并返回 x 的 算术平方根 。
由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5。*/

class Solution {
public:
	int mySqrt(int x) {
		// 特判：x = 0 或 1 时直接返回 x
		if(x < 2)
			return x;
		// 在区间 [1, x+1) 搜索，第一个使 mid*mid > x 的位置
		int left = 1, right = x; // 不要x + 1, 防止 int 溢出，但是x <= 1要特别处理
		while(left < right) {
			// 左闭右开，mid 向下取整
			int mid = left + (right - left) / 2;
			long long sq = 1LL * mid * mid; // 必须是 long long 因为最大约为 (right / 2) * (right / 2) 可能溢出
			if(sq <= x) {
				// mid^2 <= x 属于“好的”区间，搜索右半区（排除 mid）
				left = mid + 1;
			} else {
				// mid^2 > x 属于“坏的”区间，搜索左半区（保留 mid）
				right = mid;
			}
		}
		// 循环终止时，left == right，且指向第一个使 mid^2 > x 的位置
		// 答案就是 left-1，最后一个使 mid^2 <= x 的 mid
		return left - 1;
	}
};

// 二分查找，找 [0, x - 1] 内的最后一个小于等于 x 的算术平方根的整数
// 等同于找 [0, x - 1] 内的第一个大于 x 的算术平方根的整数的前一个数，或者等于 x 的算术平方根的整数

int main() {
	Solution sol;
}