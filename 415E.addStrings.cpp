// Created: 2026-01-21
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个字符串形式的非负整数num1 和num2，计算它们的和并同样以字符串形式返回。
你不能使用任何內建的用于处理大整数的库（比如 BigInteger），也不能直接将输入的字符串转换为整数形式。
示例 1：
	输入：num1 = "11", num2 = "123"
	输出："134"
示例 2：
	输入：num1 = "456", num2 = "77"
	输出："533"
示例 3：
	输入：num1 = "0", num2 = "0"
	输出："0"
提示：
	1 <= num1.length, num2.length <= 10^4
	num1 和num2 都只包含数字0-9
	num1 和num2 都不包含任何前导零 */

class Solution {
public:
	string addStrings(string &num1, string &num2) {
		int i = num1.size() - 1, j = num2.size() - 1, up = 0;
		string res;
		res.reserve(max(i, j) + 2);
		while(i >= 0 || j >= 0 || up) {
			if(i >= 0) up += num1[i--] - '0';
			if(j >= 0) up += num2[j--] - '0';
			res.push_back(up % 10 + '0');
			up /= 10;
		}
		reverse(res.begin(), res.end());
		return res;
	}
};

int main() {
	Solution sol;
	string num1, num2;
	num1 = "11", num2 = "123";
	cout << sol.addStrings(num1, num2) << endl;

	num1 = "456", num2 = "77";
	cout << sol.addStrings(num1, num2) << endl;

	num1 = "0", num2 = "0";
	cout << sol.addStrings(num1, num2) << endl;
}