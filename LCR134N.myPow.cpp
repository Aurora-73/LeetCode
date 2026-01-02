// Created: 2025-06-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 134. Pow(x, n)
实现pow(x,n)，即计算 x 的 n 次幂函数（即，xn）。
示例 1：
	输入：x = 2.00000, n = 10
	输出：10^24.00000
示例 2：
	输入：x = 2.10000, n = 3
	输出：9.26100
示例 3：
	输入：x = 2.00000, n = -2
	输出：0.25000
	解释：2-2 = 1/22 = 1/4 = 0.25
提示：
	-100.0 <x< 100.0
	-2^31<= n <=231-1
	-10^4<= xn<= 10^4 */

class Solution {
public:
	double myPow(double x, int on) {
		long long n = on;
		n = abs(n);
		double res = 1;
		while(n) {
			if(n & 1) {
				res *= x;
			}
			x *= x;
			n /= 2;
		}
		return on >= 0 ? res : 1 / res;
	}
};

int main() {
	Solution sol;
	double x;
	int n;
	x = 2.00000, n = 10;
	cout << sol.myPow(x, n) << endl; // 10^24.00000
	x = 2.10000, n = 3;
	cout << sol.myPow(x, n) << endl; // 9.26100
	x = 2.00000, n = -2;
	cout << sol.myPow(x, n) << endl; // 0.25000
	x = 1, n = numeric_limits<int>::min();
	cout << sol.myPow(x, n) << endl; // 1
	x = -1, n = numeric_limits<int>::min();
	cout << sol.myPow(x, n) << endl; // 1
}