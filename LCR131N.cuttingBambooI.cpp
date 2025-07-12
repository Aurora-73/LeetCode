// Created: 2025-07-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 132. 砍竹子 II
现需要将一根长为正整数 bamboo_len 的竹子砍为若干段，每段长度均为 正整数。
请返回每段竹子长度的 最大乘积 是多少。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
示例 1：
	输入：bamboo_len = 12
	输出：81
提示：
	2 <= bamboo_len <= 1000 */

class Solution {
public:
	int cuttingBamboo(int n) {
		static constexpr int MOD = 1000000007;
		if(n <= 3) return n - 1;
		int quotient = n / 3, remainder = n % 3;
		if(remainder == 0) {
			return modPow(quotient);
		} else if(remainder == 1) {
			return (modPow(quotient - 1) * 4) % MOD;
		} else {
			return (modPow(quotient) * 2) % MOD;
		}
	}

private:
	static uint64_t modPow(int p) {
		static constexpr int MOD = 1000000007;
		uint64_t res = 1, now = 3;
		while(p > 0) {
			if(p & 1) {
				res *= now;
				res %= MOD;
			}
			now *= now;
			now %= MOD;
			p >>= 1;
		}
		return res;
	}
};

int main() {
	Solution sol;
	int bamboo_len = 1000;
	cout << sol.cuttingBamboo(bamboo_len) << endl;
	cout << sizeof(size_t) << endl;
	cout << sizeof(uint64_t) << endl;
	cout << sizeof(long long) << endl;
	cout << sizeof(uintmax_t) << endl;
}