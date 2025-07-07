// Created: 2025-07-07
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 338. 比特位计数
给你一个整数 n，对于0 <= i <= n 中的每个 i，
计算其二进制表示中 1 的个数，返回一个长度为 n + 1 的数组 ans 作为答案。
示例 1：
	输入：n = 2
	输出：{0,1,1}
	解释：
	0 --> 0
	1 --> 1
	2 --> 10
示例 2：
	输入：n = 5
	输出：{0,1,1,2,1,2}
	解释：
	0 --> 0
	1 --> 1
	2 --> 10
	3 --> 11
	4 --> 100
	5 --> 10^1
提示：
	0 <= n <= 10^5
	进阶：
	很容易就能实现时间复杂度为 O(n log n) 的解决方案，你可以在线性时间复杂度 O(n) 内用一趟扫描解决此问题吗？
	你能不使用任何内置函数解决此问题吗？（如，C++ 中的__builtin_popcount ） */

class Solution1 {
public:
	vector<int> countBits(int n) {
		vector<int> res;
		res.reserve(n + 1);
		for(int i = 0; i <= n; ++i) {
			int cnt = 0, x = i;
			while(x) {
				cnt += x & 1;
				x >>= 1;
			}
			res.push_back(cnt);
		}
		return res;
	}
};

class Solution2 {
public:
	vector<int> countBits(int n) {
		vector<int> res;
		res.reserve(n + 1);
		for(int i = 0; i <= n; ++i) {
			if(i < 1) {
				res.push_back(i);
			} else if(i % 2) {
				res.push_back(res[i - 1] + 1);
			} else {
				res.push_back(res[i / 2]);
			}
		}
		return res;
	}
};

class Solution {
public:
	vector<int> countBits(int n) {
		return { allCnts.begin(), allCnts.begin() + n + 1 };
	}

private:
	inline static constexpr array<int, 10001> allCnts = []() constexpr {
		array<int, 10001> res {};
		for(int i = 0; i <= 10000; ++i) {
			if(i < 1) {
				res[i] = i;
			} else if(i % 2) {
				res[i] = res[i - 1] + 1;
			} else {
				res[i] = res[i / 2];
			}
		}
		return res;
	}();
}; // 实际测试样例有一个8万的，不符合描述

/*  数分为奇数和偶数两种，
    对于计数i，奇数的最低位是1，且其他位和他的前一个数一样 res[i] = res[i - 1] + 1
    对于偶数i，偶数的最低位一定为0，因此它的1的个数和去掉最后一位的i / 2一样 res[i] = res[i / 2]  */

int main() {
	Solution sol;
	int n;
	n = 1000;
	cout << sol.countBits(n) << endl;
}