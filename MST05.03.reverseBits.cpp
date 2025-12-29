// Created: 2025-12-25
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个32位整数 num，你可以将一个数位从0变为1。
请编写一个程序，找出你能够获得的最长的一串1的长度。
示例 1：
	输入: num = 1775(110111011112)
	输出: 8
示例 2：
	输入: num = 7(01112)
	输出: 4 */

class Solution1 {
public:
	int reverseBits(int num) {
		bitset<32> bits = num;
		int res = 0;   // 保存结果
		int left = 0;  // 当前连续1长度
		int right = 0; // 前一段连续1长度
		for(int i = 0; i < 32; ++i) {
			if(bits[i] == 0) {
				// 翻转当前0，连接前后连续1
				res = max(res, left + right + 1);
				right = left; // 当前连续1变成前一段
				left = 0;     // 重置当前连续1
			} else {
				++left; // 连续1计数
			}
		}
		// 最后一段连续1 + 前一段连续1 + 翻转0
		return min(max(res, left + right + 1), 32);
		// 要和32取最小值是因为可能没有遇到过0，即-1
	}
};

class Solution {
public:
	int reverseBits(int num) {
		if(~num == 0) return 32;
		int res = 0, left = 0, right = 0;
		for(int i = 0; i < 32; ++i) {
			if(num & 1) {
				++left;
			} else {
				res = max(res, left + right + 1);
				right = left;
				left = 0;
			}
			num >>= 1;
		}
		res = max(res, left + right + 1);
		return res;
	}
}; // 不能写while(num)，因为对负数（如 -2）右移时，C++ 的行为是 算术右移，高位补符号位 1。

int main() {
	Solution sol;
	cout << sol.reverseBits(1774) << endl;
	cout << sol.reverseBits(-2) << endl;
	cout << sol.reverseBits(-1) << endl;
}