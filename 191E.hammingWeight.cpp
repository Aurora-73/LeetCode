// Created: 2025-05-06
#include "MyUtils.hpp"

/*191. 位1的个数
给定一个正整数 n，编写一个函数，获取一个正整数的二进制形式并返回其二进制表达式中 设置位 的个数（也被称为汉明重量）。
示例 1：
输入：n = 11
输出：3
解释：输入的二进制串 1011 中，共有 3 个设置位。
示例 2：
输入：n = 128
输出：1
解释：输入的二进制串 10000000 中，共有 1 个设置位。
示例 3：
输入：n = 2147483645
输出：30
解释：输入的二进制串 1111111111111111111111111111101 中，共有 30 个设置位。*/

class Solution {
public:
	int hammingWeight(int n) {
		int count = 0;
		while(n > 0) {
			count += n % 2;
			n /= 2;
		}
		return count;
	}
};

int main() {
	Solution sol;
	cout << sol.hammingWeight(2147483645);
}