// Created: 2026-01-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 请实现整数数字的乘法、减法和除法运算，运算结果均为整数数字，
程序中只允许使用加法运算符和逻辑运算符，允许程序中出现正负常数，不允许使用位运算。
你的实现应该支持如下操作：
    Operations() 构造函数
    minus(a, b) 减法，返回a - b
    multiply(a, b) 乘法，返回a * b
    divide(a, b) 除法，返回a / b
示例：
    Operations operations = new Operations();
    operations.minus(1, 2); //返回-1
    operations.multiply(3, 4); //返回12
    operations.divide(5, -2); //返回-2
提示：
	你可以假设函数输入一定是有效的，例如不会出现除法分母为0的情况
	单个用例的函数调用次数不会超过1000次 */

class Operations {
	long long minus(long long a, long long b) {
		return a + (~b + 1); // 二进制补码取负
	}

public:
	Operations() { }

	int minus(int a, int b) {
		return minus(a + 0ll, b + 0ll);
	}

	int multiply(int a, int b) {
		bool neg = false;
		long long x = a, y = b;
		if(x < 0) x = minus(0ll, x), neg = !neg;
		if(y < 0) y = minus(0ll, y), neg = !neg;

		long long res = 0;
		while(y) {
			if(y & 1) res += x;
			x <<= 1;
			y >>= 1;
		}

		return neg ? minus(0ll, res) : res;
	}

	int divide(int a, int b) {
		if(a == INT_MIN && b == -1) return INT_MAX; // 特判溢出

		bool neg = false;
		long long x = a, y = b;
		if(x < 0) x = minus(0ll, x), neg = !neg;
		if(y < 0) y = minus(0ll, y), neg = !neg;

		long long res = 0;
		while(x >= y) {
			long long temp = y, multiple = 1;
			while((temp << 1) <= x) {
				temp <<= 1;
				multiple <<= 1;
			}
			x = minus(x, temp);
			res += multiple;
		}

		return neg ? minus(0ll, res) : res;
	}
};

int main() {
	Operations ops;
	cout << boolalpha;
	cout << ops.minus(21, 4) << "  " << (21 - 4) << endl;
	cout << ops.minus(7, 4) << "  " << (7 - 4) << endl;
	cout << ops.minus(21, 24) << "  " << (21 - 24) << endl;
	cout << ops.minus(-21, 4) << "  " << (-21 - 4) << endl;
	cout << ops.minus(-21, -4) << "  " << (-21 - -4) << endl;
	cout << ops.minus(21, 4) << "  " << (21 - 4) << endl;

	cout << ops.multiply(7, 4) << "  " << (7 * 4) << endl;
	cout << ops.multiply(21, 24) << "  " << (21 * 24) << endl;
	cout << ops.multiply(-21, 4) << "  " << (-21 * 4) << endl;
	cout << ops.multiply(-21, -4) << "  " << (-21 * -4) << endl;
	cout << ops.multiply(21, 4) << "  " << (21 * 4) << endl;

	cout << ops.divide(7, 4) << "  " << (7 / 4) << endl;
	cout << ops.divide(21, 24) << "  " << (21 / 24) << endl;
	cout << ops.divide(-21, 4) << "  " << ((-21) / 4) << endl;
	cout << ops.divide(-21, -4) << "  " << ((-21) / (-4)) << endl;
}