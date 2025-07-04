// Created: 2025-07-03
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 10^71. 字符串的最大公因子对于字符串s 和t，
只有在s = t + t + t + ... + t + t（t 自身连接 1 次或多次）时，我们才认定“t 能除尽 s”。
给定两个字符串str1和str2。返回 最长字符串x，要求满足x 能除尽 str1 且 x 能除尽 str2。
示例 1：
	输入：str1 = "ABCABC", str2 = "ABC"
	输出："ABC"
示例 2：
	输入：str1 = "ABABAB", str2 = "ABAB"
	输出："AB"
示例 3：
	输入：str1 = "LEET", str2 = "CODE"
	输出：""
提示：
	1 <= str1.length, str2.length <= 1000
	str1和str2由大写英文字母组成 */

class Solution1 {
public:
	string gcdOfStrings(string &str1, string &str2) {
		if(str1.size() < str2.size()) {
			swap(str1, str2);
		}
		int n1 = str1.size(), n2 = str2.size(), i = 0, j = 0, cnt = 0;
		while(i < n1) {
			if(str1[i] != str2[j]) {
				break;
			} else {
				++j, ++i;
				if(j == n2) {
					++cnt;
					j %= n2;
				}
			}
		}
		if(n2 * cnt == n1) {
			return str2;
		} else if(cnt == 0) {
			return "";
		} else {
			string remain = str1.substr(n2 * cnt);
			return gcdOfStrings(str2, remain);
		}
	}
};

class Solution {
public:
	string gcdOfStrings(const string &str1, const string &str2) {
		return string(gcd(str1, str2));
	}
	string_view gcd(string_view sv1, string_view sv2) {
		if(sv1.size() < sv2.size()) {
			swap(sv1, sv2);
		}
		int n1 = sv1.size(), n2 = sv2.size(), i = 0, j = 0, cnt = 0;
		while(i < n1) {
			if(sv1[i] != sv2[j]) {
				break;
			} else {
				++j, ++i;
				if(j == n2) {
					++cnt;
					j %= n2;
				}
			}
		}
		if(n2 * cnt == n1) {
			return sv2.begin();
		} else if(cnt == 0) {
			return "";
		} else {
			return gcd(sv2, sv1.substr(n2 * cnt));
		}
	}
}; // 零拷贝

/* 假如需要求 1997 和 615 两个正整数的最大公约数，用欧几里得算法，是这样进行的：
1997 ÷ 615 = 3 (余 152)
615 ÷ 152 = 4(余7)
152 ÷ 7 = 21(余5)
7 ÷ 5 = 1 (余2)
5 ÷ 2 = 2 (余1)
2 ÷ 1 = 2 (余0)
至此，最大公约数为1
以除数和余数反复做除法运算，当余数为 0 时，取当前算式除数为最大公约数，所以就得出了 1997 和 615 的最大公约数 1。 */

int main() {
	Solution sol;
	string str1, str2;
	str1 = "ABCABC", str2 = "ABC";
	cout << sol.gcdOfStrings(str1, str2) << endl; // "ABC"
	str1 = "ABABAB", str2 = "ABAB";
	cout << sol.gcdOfStrings(str1, str2) << endl; // "AB"
	str1 = "LEET", str2 = "CODE";
	cout << sol.gcdOfStrings(str1, str2) << endl; // ""
}