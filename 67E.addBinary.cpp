// Created: 2025-04-27
#include "MyUtils.hpp"

/*  */

class Solution {
public:
	string addBinary(string a, string b) {
		string res, zero = "0", one = "1";
		bool up = false;
		int ia = a.length() - 1, ib = b.length() - 1;
		while(ia >= 0 && ib >= 0) {
			int val = up + (a[ia--] == '1') + (b[ib--] == '1');
			if(val >= 2) {
				val -= 2;
				up = true;
			} else
				up = false;
			res = (val ? one : zero) + res;
		}
		while(ia >= 0) {
			int val = up + (a[ia--] == '1');
			if(val >= 2) {
				val -= 2;
				up = true;
			} else
				up = false;
			res = (val ? one : zero) + res;
		}
		while(ib >= 0) {
			int val = up + (b[ib--] == '1');
			if(val >= 2) {
				val -= 2;
				up = true;
			} else
				up = false;
			res = (val ? one : zero) + res;
		}
		if(up) res = one + res;
		return res;
	}
};

class Solution {
public:
	string addBinary(string a, string b) {
		int n = max(a.length(), b.length());
		unique_ptr<char[]> res(new char[n + 2]); // 预留空间，包括可能的进位
		// 或者unique_ptr<char[]> res = std::make_unique<char[]>(n + 2);
		bool up = false;
		int ia = a.length() - 1, ib = b.length() - 1, ir = n;
		res[n + 1] = '\0'; // 手动加上字符串结束符

		// 合并所有情况到一个循环
		while(ia >= 0 || ib >= 0 || up) {
			int val = up; // 从上次的进位开始

			if(ia >= 0) val += (a[ia--] == '1'); // 处理a的当前位
			if(ib >= 0) val += (b[ib--] == '1'); // 处理b的当前位

			up = val >= 2;
			res[ir--] = (val % 2) + '0';
		}

		// 从res[ir+1]开始构造字符串
		return string(res.get() + ir + 1);
	}
};

class Solution {
public:
	string addBinary(string a, string b) {
		string res;
		int i = a.size() - 1, j = b.size() - 1, carry = 0;

		while(i >= 0 || j >= 0 || carry) {
			int sum = carry;
			if(i >= 0) sum += (a[i--] - '0');
			if(j >= 0) sum += (b[j--] - '0');
			res.push_back(sum % 2 + '0');
			carry = sum / 2;
		}

		reverse(res.begin(), res.end());
		return res;
	}
};

class Solution {
public:
	string addBinary(string a, string b) {
		int n = max(a.size(), b.size()) + 1; // 可能有额外进位
		string res(n, '0');
		int i = a.size() - 1, j = b.size() - 1, k = n - 1, carry = 0;

		while(i >= 0 || j >= 0 || carry) {
			int sum = carry;
			if(i >= 0) sum += (a[i--] - '0');
			if(j >= 0) sum += (b[j--] - '0');
			res[k--] = (sum % 2) + '0';
			carry = sum / 2;
		}

		// 如果最高位是 '0'，说明没有实际进位，需要去掉
		if(res[0] == '0') {
			return res.substr(1);
		}
		return res;
	}
};

int main() {
	Solution sol;
	string a, b;
	a = "1010";
	b = "1011";
	cout << sol.addBinary(a, b) << endl;
}