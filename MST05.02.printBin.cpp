// Created: 2025-12-26
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 二进制数转字符串。
给定一个介于 0 和 1 之间的实数（如 0.72），类型为 double，
打印它的二进制表达式。如果该数字无法精确地用 32 位以内的二进制表示，则打印“ERROR”。
示例 1：
	输入：0.625
	输出："0.101"
示例 2：
	输入：0.1
	输出："ERROR"
提示：0.1 无法被二进制准确表示
提示：
	32位包括输出中的 "0." 这两位。
	题目保证输入用例的小数位数最多只有 6 位 */

class Solution {
public:
	string printBin(double num) {
		string res = "0.";
		for(int i = 0; i < 30; ++i) { // 实际上最多6次即可判断，因为这个数在十进制为有限小数
			num *= 2;
			if(num >= 1) {
				res.push_back('1');
				num -= 1;
			} else {
				res.push_back('0');
			}
			if(num == 0.0) return res;
		}
		return "ERROR";
	}
};

int main() {
	Solution sol;
	double num;
	num = 0.625;
	cout << sol.printBin(num) << endl; // "0.101"

	num = 0.1;
	cout << sol.printBin(num) << endl; // "ERROR"
}