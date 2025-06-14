// Created: 2025-06-14
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 2566. 替换一个数字后的最大差值
给你一个整数num。
你知道 Danny Mittal 会偷偷将 0 到 9 中的一个数字 替换 成另一个数字。
请你返回将 num 中恰好一个数字进行替换后，得到的最大值和最小值的差为多少。
注意：
	当 Danny 将一个数字 d1 替换成另一个数字 d2 时，Danny 需要将nums中所有 d1 都替换成 d2。
	Danny 可以将一个数字替换成它自己，也就是说num可以不变。
	Danny 可以将数字分别替换成两个不同的数字分别得到最大值和最小值。
	替换后得到的数字可以包含前导 0。
	Danny Mittal 获得周赛 326 前 10 名，让我们恭喜他。
示例 1：
	输入：num = 11891
	输出：99009
	解释：
	为了得到最大值，我们将数字 1 替换成数字 9，得到 99899。
	为了得到最小值，我们将数字 1 替换成数字 0，得到 890。
	两个数字的差值为 99009。
示例 2：
	输入：num = 90
	输出：99
	解释：
	可以得到的最大值是 99（将 0 替换成 9），最小值是 0（将 9 替换成 0）。
	所以我们得到 99。
提示：
	1 <= num <= 10 ^ 8 */

class Solution1 {
public:
	int minMaxDifference(int num) {
		int max_val = 0, min_val = 0, n = 1;
		while(num >= n * 10) n *= 10;
		int dmin = num / n, dmax = dmin, n2 = n / 10;
		while(dmax == 9 && n2 >= 1) {
			dmax = (num / n2) % 10;
			n2 /= 10;
		}
		n = 0;
		while(num > 0) {
			int d = num % 10;
			max_val += (d == dmax ? 9 : d) * pow(10, n);
			min_val += (d == dmin ? 0 : d) * pow(10, n);
			num /= 10, ++n;
		}
		return max_val - min_val;
	}
};

class Solution {
public:
	int minMaxDifference(int num) {
		string s = to_string(num);
		string t = s;
		size_t pos = s.find_first_not_of('9');
		if(pos != string::npos) {
			char a = s[pos];
			replace(s.begin(), s.end(), a, '9');
		}
		char b = t[0];
		replace(t.begin(), t.end(), b, '0');
		return stoi(s) - stoi(t);
	}
};

int main() {
	Solution1 sol1;
	Solution sol;
	int num;
	num = 11891;
	cout << sol1.minMaxDifference(num) << endl;
	cout << sol.minMaxDifference(num) << endl;
	num = 90;
	cout << sol1.minMaxDifference(num) << endl;
	cout << sol.minMaxDifference(num) << endl;
	num = 99999;
	cout << sol1.minMaxDifference(num) << endl;
	cout << sol.minMaxDifference(num) << endl;
}