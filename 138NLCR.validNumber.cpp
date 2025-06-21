// Created: 2025-06-21
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 138. 有效数字
有效数字（按顺序）可以分成以下几个部分：
	若干空格
	一个 小数 或者 整数
	（可选）一个 "e" 或 "E"，后面跟着一个 整数
	若干空格
小数（按顺序）可以分成以下几个部分：
	（可选）一个符号字符（"+" 或 "-"）
	下述格式之一：
		至少一位数字，后面跟着一个点 "."
		至少一位数字，后面跟着一个点 "."，后面再跟着至少一位数字
		一个点 "."，后面跟着至少一位数字
整数（按顺序）可以分成以下几个部分：
	（可选）一个符号字符（"+" 或 "-"）
	至少一位数字
部分有效数字列举如下：{"2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"}
部分无效数字列举如下：{"abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"}
给你一个字符串 s，如果 s 是一个 有效数字，请返回 true。
示例 1：
	输入：s = "0"
	输出：true
示例 2：
	输入：s = "e"
	输出：false
示例 3：
	输入：s = "."
	输出：false
提示：
	1 <= s.length <= 20
	s 仅含英文字母（大写和小写），数字（0-9），加号 "+"，减号 "-"，空格 " " 或者点 "."。 */

class Solution {
public:
	bool validNumber(string s) {
		// 去除前后空格
		size_t l = 0, r = s.size();
		while(l < r && s[l] == ' ') ++l;
		while(r > l && s[r - 1] == ' ') --r;
		if(l >= r) return false;
		std::string_view sv(s.data() + l, r - l);

		// 查找e/E
		size_t epos = sv.find_first_of("eE");
		if(epos == std::string_view::npos) {
			return isDecimal(sv) || isInteger(sv);
		} else {
			std::string_view left = sv.substr(0, epos);
			std::string_view right = sv.substr(epos + 1);
			return (isDecimal(left) || isInteger(left)) && isInteger(right);
		}
	}

private:
	bool isDecimal(string_view sv) {
		int i = 0, n = sv.size();
		if(n == 0) return false;
		if(sv[i] == '+' || sv[i] == '-') ++i;
		bool num = false;
		while(i < n && sv[i] <= '9' && sv[i] >= '0') ++i, num = true;
		if(i == n) return false;
		if(sv[i++] != '.') return false;
		while(i < n && sv[i] <= '9' && sv[i] >= '0') ++i, num = true;
		return num && i == n;
	}

	bool isInteger(string_view sv) {
		int i = 0, n = sv.size();
		if(n == 0) return false;
		if(sv[i] == '+' || sv[i] == '-') ++i;
		bool num = false;
		while(i < n && sv[i] <= '9' && sv[i] >= '0') ++i, num = true;
		return num && i == n;
	}
};

int main() {
	Solution sol;
	string s;
	s = "0";
	cout << sol.validNumber(s) << endl; // 1
	s = "e";
	cout << sol.validNumber(s) << endl; // 0
	s = ".";
	cout << sol.validNumber(s) << endl; // 0
	vector<string> vec = { "2",
		"0089",
		"-0.1",
		"+3.14",
		"4.",
		"-.9",
		"2e10",
		"-90E3",
		"3e+7",
		"+6e-1",
		"53.5e93",
		"-123.456e789" };
	for(auto ss : vec) {
		cout << sol.validNumber(ss); // 1
	}
	cout << endl;
	vec = { "abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53" };
	for(auto ss : vec) {
		cout << sol.validNumber(ss); // 0
	}
	cout << endl;
}