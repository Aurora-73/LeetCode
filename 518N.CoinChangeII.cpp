// Created: 2025-06-07
#include "MyUtils.hpp"

/* 518. 零钱兑换 II
给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。
请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 0 。
假设每一种面额的硬币有无限个。 
题目数据保证结果符合 32 位带符号整数。
示例 1：
    输入：amount = 5, coins = [1, 2, 5]
    输出：4
    解释：有四种方式可以凑成总金额：
    5=5
    5=2+2+1
    5=2+1+1+1
    5=1+1+1+1+1
提示：
    1 <= coins.length <= 300
    1 <= coins[i] <= 5000
    coins 中的所有值 互不相同
    0 <= amount <= 5000  */

class Solution {
public:
	int change(int amount, vector<int> &coins) {
		std::sort(coins.begin(), coins.end());
		vector<int> dp(amount + 1);
		dp.front() = 1;
		for(auto j : coins) {
			for(int i = j; i < amount + 1; ++i) {
				if(INT_MAX - dp[i] < dp[i - j]) {
					dp[i] = INT_MAX;
				} else {
					dp[i] += dp[i - j];
				}
			}
		}
#ifdef MY_UTILS_H
		cout << dp << endl;
#endif
		return dp.back();
	}
};
// 先遍历 amount 后遍历 coins 会导致重叠
// 先遍历 coins后遍历 amount 不会导致重叠
/* 当你先遍历 amount 再遍历 coins 的时候，你在“凑”同一个总额时，
会把不同顺序（比如先用 1 再用 2，和先用 2 再用 1）也算作两种不同的组合，导致重复计数；
而先遍历 coins 再遍历 amount，每一个面额的硬币只会在它前面的硬币都处理完之后才去累加，
不会再“回头”用更小的面额去和它组合，从而保证了每种组合只会被计数一次。*/

int main() {
	Solution sol;
	int amount;
	vector<int> coins;
	amount = 5;
	coins = { 1, 2, 5 };
	cout << sol.change(amount, coins);
}