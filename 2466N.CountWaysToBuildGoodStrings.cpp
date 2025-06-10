// Created: 2025-06-10
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 2466. 统计构造好字符串的方案数
给你整数zero，one，low和high，我们从空字符串开始构造一个字符串，每一步执行下面操作中的一种：
	将"0"在字符串末尾添加zero 次。
	将"1"在字符串末尾添加one次。
以上操作可以执行任意次。
如果通过以上过程得到一个 长度在low 和high之间（包含上下边界）的字符串，那么这个字符串我们称为好字符串。
请你返回满足以上要求的 不同好字符串数目。由于答案可能很大，请将结果对10^9 + 7取余后返回。
示例 1：
	输入：low = 3, high = 3, zero = 1, one = 1
	输出：8
	解释：
	一个可能的好字符串是 "011"。
	可以这样构造得到："" -> "0" -> "01" -> "011"。
	从 "000" 到 "111" 之间所有的二进制字符串都是好字符串。
示例 2：
	输入：low = 2, high = 3, zero = 1, one = 2
	输出：5
	解释：好字符串为 "00"，"11"，"000"，"110" 和 "011"。
提示：
	1 <= low<= high<= 10^5
	1 <= zero, one <= low */

class Solution1 {
public:
	int countGoodStrings(int low, int high, int zero, int one) {
		memo.clear();
		memo.resize(high + 1, -1);
		int res = dfs(low, high, zero, one, 0);
		return res;
	}

private:
	vector<int> memo;
	const int mod = int(pow(10, 9) + 7);
	int dfs(int low, int high, int zero, int one, int len) {
		if(len > high) {
			return 0;
		}
		if(memo[len] != -1) {
			return memo[len];
		}
		int res = int(len >= low);
		if(len + zero <= high) {
			res += dfs(low, high, zero, one, len + zero);
		}
		if(len + one <= high) {
			res += dfs(low, high, zero, one, len + one);
		}
		res %= mod;
		memo[len] = res;
		return res;
	}
};

class Solution2 {
public:
	int countGoodStrings(int low, int high, int zero, int one) {
		vector<int> dp(high + 1);
		const int mod = int(pow(10, 9) + 7);
		for(int i = high; i >= 0; --i) {
			dp[i] = i >= low;                               // 自身是不是
			dp[i] += (i + zero <= high) ? dp[i + zero] : 0; // 添加 0 之后有几个
			dp[i] += (i + one <= high) ? dp[i + one] : 0;   // 添加 1 之后有几个
			dp[i] %= mod;
		}
		return dp[0];
	}
};

class Solution {
public:
	int countGoodStrings(int low, int high, int zero, int one) {
		int gcd = std::gcd(zero, one);
		zero /= gcd, one /= gcd;
		low = (low - 1) / gcd + 1; // low 是上界
		high /= gcd;               // high 是下界
		vector<int> dp(high + 1);
		const int mod = int(pow(10, 9) + 7);
		for(int i = high; i >= 0; --i) {
			dp[i] = i >= low;                               // 自身是不是
			dp[i] += (i + zero <= high) ? dp[i + zero] : 0; // 添加 0 之后有几个
			dp[i] += (i + one <= high) ? dp[i + one] : 0;   // 添加 1 之后有几个
			dp[i] %= mod;
		}
		return dp[0];
	}
};

/* 每次增加的长度为 zero 或 one；
如果 zero 和 one 不是互质，而是有最大公约数 g，那么你构造出的所有字符串长度一定是 g 的倍数。
原问题：构造长度在 [low, high] 区间，步长为 zero 或 one
等价转化：构造长度在 [⌈low/g⌉, ⌊high/g⌋] 区间，步长为 zero/g 或 one/g 
x⋅g ∈ [low,high]       ⇒      x ∈ [⌈low/g⌉, ⌊high/g⌋] */

int main() {
	Solution sol;
	int low, high, zero, one;
	low = 3, high = 3, zero = 1, one = 1;
	cout << sol.countGoodStrings(low, high, zero, one) << endl; // 8
	low = 2, high = 3, zero = 1, one = 2;
	cout << sol.countGoodStrings(low, high, zero, one) << endl; // 5
}