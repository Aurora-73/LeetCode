// Created: 2025-07-13
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 002. 二进制求和
给定两个 01 字符串a和b，请计算它们的和，并以二进制字符串的形式输出。
输入为 非空 字符串且只包含数字1和0。
示例 1：
	输入: a = "11", b = "10"
	输出: "101"
示例 2：
	输入: a = "1010", b = "1011"
	输出: "10101"
提示：
	每个字符串仅由字符 "0" 或 "1" 组成。
	1 <= a.length, b.length <= 10^4
	字符串如果不是 "0"，就都不含前导零。
注意：本题与主站 67题相同：
	https://leetcode-cn.com/problems/add-binary/ */

class Solution1 {
public:
	string addBinary(string &a, string &b) {
		bool up = false;
		std::reverse(a.begin(), a.end());
		std::reverse(b.begin(), b.end());
		string res;
		int na = a.size(), nb = b.size(), i = 0;
		res.reserve(max(na, nb) + 1);
		while((i < na && i < nb) || up) {
			int sum = up + (i < na && a[i] == '1') + (i < nb && b[i] == '1');
			res.push_back(sum % 2 + '0');
			up = sum / 2;
			++i;
		}
		while(i < na) {
			res.push_back(a[i]);
			++i;
		}
		while(i < nb) {
			res.push_back(b[i]);
			++i;
		}
		std::reverse(res.begin(), res.end());
		return res;
	}
};

class Solution {
public:
	string addBinary(string a, string b) {
		string res;
		bool up = false;
		int na = a.size(), nb = b.size(), i = 0;
		res.reserve(max(na, nb) + 1);
		while(i < na || i < nb || up) {
			int sum = up + (i < na && a[na - 1 - i] == '1') + (i < nb && b[nb - 1 - i] == '1');
			res.push_back(sum % 2 + '0');
			up = sum / 2;
			++i;
		}
		std::reverse(res.begin(), res.end());
		return res;
	}
};

int main() {
	Solution sol;
	string a, b;
	a = "1", b = "111";
	cout << sol.addBinary(a, b) << endl; // "1000"
	a = "11", b = "10";
	cout << sol.addBinary(a, b) << endl; // "101"
	a = "1010", b = "1011";
	cout << sol.addBinary(a, b) << endl; // "10101"
}