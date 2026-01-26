// Created: 2025-05-18
#include "MyUtils.hpp"

/*69. x 的平方根 
给你一个非负整数 x，计算并返回x的 算术平方根。
由于返回类型是整数，结果只保留 整数部分，小数部分将被 舍去。
注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5。
示例 1：
	输入：x = 4
	输出：2
示例 2：
	输入：x = 8
	输出：2
	解释：8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。
提示：
	0 <= x <= 2^31 - 1*/

class Solution1 {
public:
	int mySqrt(int x) {
		if(x < 2) return x;
		// 在区间 [1, x+1) 搜索，第一个使 mid*mid > x 的位置
		int left = 1, right = x; // 不要x + 1, 防止 int 溢出，但是x <= 1要特别处理
		while(left < right) {
			// 左闭右开，mid 向下取整
			int mid = left + (right - left) / 2;
			long long sq = 1LL * mid * mid;
			// 必须是 long long 因为最大约为 (right / 2) * (right / 2) 可能溢出
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

class Solution2 {
public:
	int mySqrt(int x) {
		if(x < 2) return x;
		int l = 0, r = x; // 左闭右开
		while(l < r) {
			int mid = l + (r - l) / 2;
			if(mid <= x / mid && mid + 1 > x / (mid + 1)) {
				// 不仅平方小于等于x，而且是最大的一个
				return mid;
			} else if(mid < x / mid) {
				l = mid + 1; // 已经确定l不是待求得数，可以放心排除
			} else {
				r = mid;
			}
		}
		return l;
	}
}; // 寻找 平方小于等于x 的最大的整数，用除法而不是乘法可以避免溢出

class Solution {
public:
	int mySqrt(int x) {
		if(x < 2) return x;
		int l = 0, r = x;  // [l, r)，保证 r 不会越界
		while(l + 1 < r) { // 保证至少有两个元素区间，退出时 l 为答案
			int mid = l + (r - l) / 2;
			if((long long)mid <= x / mid) { // mid * mid <= x
				l = mid;
			} else {
				r = mid;
			}
		}
		return l;
	}
};

int main() {
	Solution sol;
	int x;
	x = 4;
	cout << sol.mySqrt(x) << endl;

	x = 8;
	cout << sol.mySqrt(x) << endl;
}