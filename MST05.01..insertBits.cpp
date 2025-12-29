// Created: 2025-12-26
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个整型数字 N 与 M，以及表示比特位置的 i 与 j（i <= j，且从 0 位开始计算）。
编写一种方法，使 M 对应的二进制数字插入 N 对应的二进制数字的第 i ~ j 位区域，
不足之处用 0 补齐。具体插入过程如图所示。
题目保证从 i 位到 j 位足以容纳 M， 例如： M = 10011，则 i～j 区域至少可容纳 5 位。
示例 1：
    输入：N = 1024(10000000000), M = 19(10011), i = 2, j = 6
    输出：N = 1100(10001001100)
示例 2：
    输入：N = 0, M = 31(11111), i = 0, j = 4
    输出：N = 31(11111) */

class Solution1 {
public:
	int insertBits(int N, int M, int i, int j) {
		bitset<32> bM = M, bN = N;
		int start = i;
		while(i <= j) {
			bN[i] = bM[i - start];
			++i;
		}
		return bN.to_ulong();
	}
};

class Solution2 {
public:
	int insertBits(int N, int M, int i, int j) {
		// N &= 111111 00000 11111
		// N |= (M << i)
		int mask = 0xFFFFFFFF;
		if(j != 31)
			mask <<= j + 1;
		else
			mask = 0; // int左移31位会报错
		mask |= (1 << i) - 1;
		N &= mask;
		N |= (M << i);
		return N;
	}
};

class Solution {
public:
	int insertBits(int n, int m, int i, int j) {
		// 清除 n 的从低到高 i~j 位（i 从 0 开始）
		n &= ~(((1 << (j - i + 1)) - 1) << i);
		// 把 m 填入 n
		return n | (m << i);
	}
};

int main() {
	Solution sol;
	int N = 1024, M = 19, i = 2, j = 6;
	cout << sol.insertBits(N, M, i, j) << endl;

	N = 0, M = 31, i = 0, j = 4;
	cout << sol.insertBits(N, M, i, j) << endl;
}