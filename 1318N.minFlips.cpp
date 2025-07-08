// Created: 2025-07-08
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1318. 或运算的最小翻转次数
给你三个正整数a、b 和 c。
你可以对 a 和 b的二进制表示进行位翻转操作，返回能够使按位或运算 a OR b == c成立的最小翻转次数。
「位翻转操作」是指将一个数的二进制表示任何单个位上的 1 变成 0 或者 0 变成 1。
示例 1：
	输入：a = 2, b = 6, c = 5
	输出：3
	解释：翻转后 a = 1 , b = 4 , c = 5 使得 a OR b == c
示例 2：
	输入：a = 4, b = 2, c = 7
	输出：1
示例 3：
	输入：a = 1, b = 2, c = 3
	输出：0
提示：
	1 <= a <= 10^9
	1 <= b<= 10^9
	1 <= c<= 10^9 */

class Solution1 {
public:
	int minFlips(int a, int b, int c) {
		auto bitA = int2bits(a), bitB = int2bits(b), bitC = int2bits(c);
		unsigned len = max({ bitA.size(), bitB.size(), bitC.size() });
		bitA.resize(len), bitB.resize(len), bitC.resize(len);
		int res = 0;
		for(unsigned i = 0; i < len; ++i) {
			if(bitC[i]) {
				if(!bitA[i] && !bitB[i]) ++res;
			} else {
				res += bitA[i];
				res += bitB[i];
			}
		}
		return res;
	}

private:
	vector<bool> int2bits(int val) {
		vector<bool> res;
		while(val > 0) {
			res.push_back(val % 2);
			val /= 2;
		}
		return res;
	}
}; // 先保存二进制位，然后计算

class Solution {
public:
	int minFlips(int a, int b, int c) {
		int res = 0;
		while(a > 0 || b > 0 || c > 0) {
			bool bitA = a & 1, bitB = b & 1, bitC = c & 1;
			if(bitC) {
				res += (!bitA && !bitB);
			} else {
				res += (bitA + bitB);
			}
			a >>= 1;
			b >>= 1;
			c >>= 1;
		}
		return res;
	}
};

int main() {
	Solution sol;
	int a, b, c;
	a = 2, b = 6, c = 5;
	cout << sol.minFlips(a, b, c) << endl; // 3
	a = 4, b = 2, c = 7;
	cout << sol.minFlips(a, b, c) << endl; // 1
	a = 1, b = 2, c = 3;
	cout << sol.minFlips(a, b, c) << endl; // 0
}