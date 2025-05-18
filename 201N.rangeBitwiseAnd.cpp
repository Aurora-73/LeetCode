// Created: 2025-05-17
#include "MyUtils.h"

/*  201. 数字范围按位与
给你两个整数 left 和 right 表示区间 [left, right]，返回此区间内所有数字 按位与 的结果（包含 left 、right 端点）。
示例 1：
    输入：left = 5, right = 7
    输出：4
示例 2：
    输入：left = 0, right = 0
    输出：0
示例 3：
    输入：left = 1, right = 2147483647
    输出：0   */

class Solution {
public:
	int rangeBitwiseAnd(int left, int right) {
		for(int i = 0; i < 32; ++i) {
			if((left >> i) == (right >> i)) {
				return (left >> i) << i;
			}
		}
		return 0;
	}
};
// 范围内只要有一个数某位为0，则结果的该为为0
// 因此结果是 left 和 right 最长公共前缀后面补0的结果

int main() {
	Solution sol;
}