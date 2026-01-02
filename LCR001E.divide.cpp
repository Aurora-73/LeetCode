// Created: 2025-07-12
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 001. 两数相除
给定两个整数 a 和 b，求它们的除法的商 a/b，要求不得使用乘号 "*"、除号 "/" 以及求余符号 "%"。
注意：
	整数除法的结果应当截去（truncate）其小数部分，
	例如：truncate(8.345) = 8以及truncate(-2.7335) = -2
	假设我们的环境只能存储 32 位有符号整数，其数值范围是 {−2^31,231−1}。
	本题中，如果除法结果溢出，则返回 231− 1
示例 1：
	输入：a = 15, b = 2
	输出：7
	解释：15/2 = truncate(7.5) = 7
示例 2：
	输入：a = 7, b = -3
	输出：-2
	解释：7/-3 = truncate(-2.33333..) = -2
示例 3：
	输入：a = 0, b = 1
	输出：0
示例 4：
	输入：a = 1, b = 1
	输出：1
提示:
	-231<= a, b <= 231- 1
	b != 0 */

class Solution {
public:
	int divide(int a, int b) {
		// 处理特殊溢出
		if(a == numeric_limits<int>::min() && b == -1) {
			return numeric_limits<int>::max();
		}
		// 用 long long 存绝对值，防止 abs(numeric_limits<int>::min()) 溢出
		long long dvd = a;
		dvd = abs(dvd);
		long long dvs = b;
		dvs = abs(dvs);

		bool neg = ((a < 0) ^ (b < 0));
		long long ans = 0;

		// 从最高位往下找
		// 1 << 31 对应的值就是 2^31，大于所有 int 的绝对值范围
		for(int shift = 31; shift >= 0; --shift) {
			if((dvs << shift) <= dvd) {
				dvd -= (dvs << shift);
				ans += (1LL << shift);
			}
		}

		return ans * (neg ? -1 : 1);
	}
};

int main() {
	Solution sol;
	// 示例测试用例
	cout << sol.divide(15, 2) << endl; // 输出: 7
	cout << sol.divide(7, -3) << endl; // 输出: -2
	cout << sol.divide(0, 1) << endl;  // 输出: 0
	cout << sol.divide(1, 1) << endl;  // 输出: 1
	// 可自行添加更多测试
	return 0;
}