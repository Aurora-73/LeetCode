// Created: 2025-12-26
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 整数转换。
编写一个函数，确定需要改变几个位才能将整数 A 转成整数 B。
示例 1：
	 输入：A = 29 （或者 0b1110^1）, B = 15（或者 0b01111）
	 输出：2
示例 2：
	 输入：A = 1，B = 2
	 输出：2
提示:
	A，B范围在{-2147483648, 2147483647}之间 */

class Solution1 {
public:
	int convertInteger(int A, int B) {
		bitset<32> bA = A, bB = B;
		int res = 0;
		for(int i = 0; i < 32; ++i) {
			if(bA[i] != bB[i]) {
				++res;
			}
		}
		return res;
	}
};

class Solution2 {
public:
	int convertInteger(int A, int B) {
		unsigned int a = (unsigned int)A;
		unsigned int b = (unsigned int)B;
		int res = 0;
		while(a || b) {
			res += (a & 1) ^ (b & 1);
			a >>= 1;
			b >>= 1;
		}
		return res;
	}
}; // 注意负数右移会在左侧补充1，因此直接对int进行右移，并且使用while(a || b)会导致负数死循环

class Solution3 {
public:
	int convertInteger(int A, int B) {
		int res = 0, cnt = 0;
		while((A || B) && cnt < 32) {
			res += (A & 1) ^ (B & 1);
			A >>= 1;
			B >>= 1;
			++cnt;
		}
		return res;
	}
}; // 无视负数右移补充1的问题，最多允许右移32次，不影响结果

class Solution {
public:
	int convertInteger(int A, int B) {
		unsigned int x = (unsigned int)(A ^ B);
		int res = 0;
		while(x) {
			x &= (x - 1);
			++res;
		}
		return res;
	}
};

int main() {
	Solution sol;
	int A, B;
	A = 826966453, B = -729934991;
	cout << sol.convertInteger(A, B) << endl; // 14

	A = 29, B = 15;
	cout << sol.convertInteger(A, B) << endl;

	A = 1, B = 2;
	cout << sol.convertInteger(A, B) << endl;

	A = 826966453, B = -729934991;
	cout << sol.convertInteger(A, B) << endl;
}