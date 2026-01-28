// Created: 2026-01-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个以字符串形式表示的非负整数num1和num2，返回num1和num2的乘积，它们的乘积也表示为字符串形式。
注意：不能使用任何内置的 BigInteger 库或直接将输入转换为整数。

示例 1:
输入: num1 = "2", num2 = "3"
输出: "6"

示例2:
输入: num1 = "123", num2 = "456"
输出: "56088"

提示：
	1 <= num1.length, num2.length <= 200
	num1和 num2只能由数字组成。
	num1和 num2都不包含任何前导零，除了数字0本身。 */

class Solution1 {
public:
	string multiply(const string &num1, const string &num2) {
		if(num1 == "0" || num2 == "0") return "0";
		if(num1.size() < num2.size()) return multiply(num2, num1);

		int n1 = num1.size(), n2 = num2.size();
		string result;
		for(int i = 0; i < n1; ++i) {
			int digit = num1[n1 - 1 - i] - '0';
			string partial = oneDigMult(num2, digit);   // 先计算单步乘法的结果
			result = addWithOffset(result, partial, i); // 然后进行偏移后的加和
		}
		reverse(result.begin(), result.end());
		return result;
	}

private:
	// 计算 num × digit，结果低位在前
	string oneDigMult(const string &num, int digit) {
		string partial;
		int carry = 0;
		int idx = num.size() - 1;
		while(idx >= 0 || carry) {
			if(idx >= 0) {
				carry += (num[idx--] - '0') * digit;
			}
			partial.push_back(carry % 10 + '0');
			carry /= 10;
		}
		return partial;
	}

	// 计算 sum + partial * (10 ^ offset)，所有字符串均为低位在前
	string addWithOffset(const string &sum, const string &partial, int offset) {
		string newSum;
		int carry = 0;
		int i = 0, j = 0;
		int sumLen = sum.size();
		int partLen = partial.size();

		// 保留低位 offset 位（相当于左移 partial）
		while(i < offset) {
			newSum.push_back(sum[i++]);
		}

		// 正式逐位相加
		while(i < sumLen || j < partLen || carry) {
			if(i < sumLen) carry += sum[i++] - '0';
			if(j < partLen) carry += partial[j++] - '0';
			newSum.push_back(carry % 10 + '0');
			carry /= 10;
		}

		return newSum;
	}
}; // 先计算出nums1每位数与nums2的乘积，偏移后加到结果中

class Solution {
public:
	string multiply(string &num1, string &num2) {
		if(num1 == "0" || num2 == "0") return "0";
		if(num1.size() < num2.size()) return multiply(num2, num1);

		int n1 = num1.size(), n2 = num2.size();
		string res(n1 + n2, '0');
		for(int i = 0; i < n1; ++i) {
			int val = num1[n1 - 1 - i] - '0'; // 当前的一位被乘数
			int j = n2 - 1, k = i;            // j是乘数的下标，k是加和的下标
			int up = 0;                       // 进位
			while(j >= 0 || up) {
				if(j >= 0) up += (num2[j--] - '0') * val;
				up += res[k] - '0';
				res[k++] = up % 10 + '0';
				up /= 10;
			}
		}
		if(res.back() == '0') res.pop_back();
		reverse(res.begin(), res.end());
		return res;
	}
}; // 一边计算乘积一边加和

int main() {
	Solution sol;
	string num1, num2;
	num1 = "2", num2 = "3";
	cout << sol.multiply(num1, num2) << endl;

	num1 = "123", num2 = "456";
	cout << sol.multiply(num1, num2) << endl;
}