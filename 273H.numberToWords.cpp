// Created: 2026-01-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 将非负整数 num 转换为其对应的英文表示。
示例 1：
	输入：num = 123
	输出："One Hundred Twenty Three"
示例 2：
	输入：num = 12345
	输出："Twelve Thousand Three Hundred Forty Five"
示例 3：
	输入：num = 1234567
	输出："One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
提示：
	0 <= num <= 2^31 - 1 */

class Solution1 {
public:
	string numberToWords(int n) {
		if(n == 0) return "Zero";

		string res;
		int idx = 0; // 对应 Thousand / Million / Billion

		while(n > 0) {
			int part = n % 1000;
			if(part != 0) {
				string cur = three(part);
				if(idx > 0) cur += " " + big[idx];
				if(!res.empty())
					res = cur + " " + res;
				else
					res = cur;
			}
			n /= 1000;
			idx++;
		}
		return res;
	}

private:
	// 转换 1 ~ 999
	string three(int n) {
		string res;
		if(n >= 100) {
			res += low[n / 100] + " Hundred";
			n %= 100;
			if(n) res += " ";
		}
		if(n >= 20) {
			res += ten[n / 10];
			if(n % 10) res += " " + low[n % 10];
		} else if(n > 0) {
			res += low[n];
		}
		return res;
	}

private:
	inline static const string low[21] { "Zero",
		"One",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Eight",
		"Nine",
		"Ten",
		"Eleven",
		"Twelve",
		"Thirteen",
		"Fourteen",
		"Fifteen",
		"Sixteen",
		"Seventeen",
		"Eighteen",
		"Nineteen",
		"Twenty" };

	inline static const string ten[10] {
		"Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
	};

	inline static const string big[4] { "", "Thousand", "Million", "Billion" };
}; // 从低到高，往res前面添加
/* "
Two 2
        Billion 
One Hundred Forty Seven 147
        Million 
Four Hundred Eighty Three 483
        Thousand 
Six Hundred Forty Seven 647
" */

class Solution {
public:
	string numberToWords(int num) {
		if(num == 0) {
			return "Zero";
		}
		string sb;
		for(int i = 3, unit = 1000000000; i >= 0; i--, unit /= 1000) {
			int curNum = num / unit;
			if(curNum != 0) {
				num -= curNum * unit;
				string curr;
				recursion(curr, curNum);
				curr = curr + thousands[i] + " ";
				sb = sb + curr;
			}
		}
		while(sb.back() == ' ') {
			sb.pop_back();
		}
		return sb;
	}

private:
	vector<string> singles
	    = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
	vector<string> teens = { "Ten",
		"Eleven",
		"Twelve",
		"Thirteen",
		"Fourteen",
		"Fifteen",
		"Sixteen",
		"Seventeen",
		"Eighteen",
		"Nineteen" };
	vector<string> tens = {
		"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
	};
	vector<string> thousands = { "", "Thousand", "Million", "Billion" };

	void recursion(string &curr, int num) {
		if(num == 0) {
			return;
		} else if(num < 10) {
			curr = curr + singles[num] + " ";
		} else if(num < 20) {
			curr = curr + teens[num - 10] + " ";
		} else if(num < 100) {
			curr = curr + tens[num / 10] + " ";
			recursion(curr, num % 10);
		} else {
			curr = curr + singles[num / 100] + " Hundred ";
			recursion(curr, num % 100);
		}
	}
};

int main() {
	Solution sol;
	int num;
	num = 123;
	cout << sol.numberToWords(num) << endl;

	num = 12345;
	cout << sol.numberToWords(num) << endl;

	num = 1234567;
	cout << sol.numberToWords(num) << endl;
}