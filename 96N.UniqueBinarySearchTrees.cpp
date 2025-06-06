// Created: 2025-06-06
#include "MyUtils.h"

/*96. 不同的二叉搜索树
给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。
示例 1：
    输入：n = 3
    输出：5
示例 2：
    输入：n = 1
    输出：1
提示：
    1 <= n <= 19
*/

class Solution {
public:
	int numTrees(int n) {
		vector<int> dp(n + 1);
		dp[0] = 1, dp[1] = 1;
		for(int i = 2; i <= n; ++i) {
			for(int j = 0; j < i; ++j) {
				dp[i] += dp[j] * dp[i - j - 1];
			}
		}
		return dp.back();
	}
};

class Solution1 {
public:
	int numTrees(int n) {
		long long C = 1;
		for(int i = 0; i < n; ++i) {
			C = C * 2 * (2 * i + 1) / (i + 2);
		}
		return (int)C;
	}
}; // 卡塔兰数 C

// 定义通用模板
template <int N>
struct CatalanNumber;

// 全特化基例：C(0) = 1
template <>
struct CatalanNumber<0> {
	static const int value = 1;
};

// 递归模板：C(n) = C(n-1) * 2*(2n-1) / (n+1)
template <int N>
struct CatalanNumber {
	static const int value = static_cast<long long>(CatalanNumber<N - 1>::value) * 2
	    * (2 * (N - 1) + 1) / ((N - 1) + 2);
};

class Solution {
public:
	int numTrees(int n) {
		switch(n) {
		case 0: return CatalanNumber<0>::value;
		case 1: return CatalanNumber<1>::value;
		case 2: return CatalanNumber<2>::value;
		case 3: return CatalanNumber<3>::value;
		case 4: return CatalanNumber<4>::value;
		case 5: return CatalanNumber<5>::value;
		case 6: return CatalanNumber<6>::value;
		case 7: return CatalanNumber<7>::value;
		case 8: return CatalanNumber<8>::value;
		case 9: return CatalanNumber<9>::value;
		case 10: return CatalanNumber<10>::value;
		case 11: return CatalanNumber<11>::value;
		case 12: return CatalanNumber<12>::value;
		case 13: return CatalanNumber<13>::value;
		case 14: return CatalanNumber<14>::value;
		case 15: return CatalanNumber<15>::value;
		case 16: return CatalanNumber<16>::value;
		case 17: return CatalanNumber<17>::value;
		case 18: return CatalanNumber<18>::value;
		case 19: return CatalanNumber<19>::value;
		default: return 0; // n >= 20 或负数，超出范围
		}
	}
};

int main() {
	cout << Solution().numTrees(19) << endl;
	cout << Solution1().numTrees(19) << endl;
}