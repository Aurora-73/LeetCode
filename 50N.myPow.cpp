// Created: 2025-05-19
#include "MyUtils.hpp"

/*50. Pow(x, n)
实现 pow(x, n) ，即计算 x 的整数 n 次幂函数（即，xn ）。*/

class Solution1 {
public:
	double myPow(double x, int n) {
		if(x == 1.0 || x == 0.0) return x;
		if(x == -1.0) return (n % 2 ? -1.0 : 1.0);

		bool negative = n < 0;
		unsigned int size;

		if(negative) {
			if(n == numeric_limits<int>::min()) {
				size = static_cast<unsigned int>(numeric_limits<int>::max()) + 1; // 防止溢出
			} else {
				size = static_cast<unsigned int>(-n);
			}
		} else {
			size = static_cast<unsigned int>(n);
		}

		double result = quickPow(x, size);
		return negative ? 1.0 / result : result;
	}

private:
	double quickPow(double x, unsigned int n) {
		if(n == 0) return 1.0;
		double half = quickPow(x, n / 2);
		return (n % 2) ? half * half * x : half * half;
	}
};

class Solution2 {
public:
	double myPow(double x, int n) {
		long long p = n;
		if(p < 0) {
			p = -p;
			x = 1.0 / x;
		}
		double res = 1, now = x;
		while(p > 0) {
			if(p & 1) {
				res *= now;
			}
			now *= now;
			p >>= 1;
		}
		return res;
	}
};

int main() {
	Solution1 sol1;
	cout << sol1.myPow(94, 40) << endl;
	cout << sol1.myPow(94, -40) << endl;
	Solution2 sol2;
	cout << sol1.myPow(94, 40) << endl;
	cout << sol2.myPow(94, -40) << endl;
}