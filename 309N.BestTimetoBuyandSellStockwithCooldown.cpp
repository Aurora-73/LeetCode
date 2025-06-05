// Created: 2025-06-04
#include "MyUtils.h"

/*309. 买卖股票的最佳时机含冷冻期
给定一个整数数组prices，其中第  prices[i] 表示第 i 天的股票价格 。​
设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:
卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
示例 1:
    输入: prices = [1,2,3,0,2]
    输出: 3 
    解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
提示：
    1 <= prices.length <= 5000
    0 <= prices[i] <= 1000*/

class Solution1 {
public:
	int maxProfit(vector<int> &prices) {
		int n = prices.size();
		vector<array<int, 3>> dp(n);
		// dp[i][0] 当前手里没有股票 且可以买入 的情况下的后续最大收益
		// dp[i][1] 当前手里有股票的情况下的后续最大收益
		// dp[i][2] 当前手里没有股票 且不可以买入 的情况下的后续最大收益
		// 0->0 1->1 0->1 1->2 2->0
		dp.back() = { 0, prices.back(), 0 };
		for(int i = n - 2; i >= 0; --i) {
			dp[i][0] = max(dp[i + 1][1] - prices[i], dp[i + 1][0]);
			dp[i][1] = max(dp[i + 1][2] + prices[i], dp[i + 1][1]);
			dp[i][2] = dp[i + 1][0];
		}
		return dp[0][0];
	}
};

class Solution {
public:
	int maxProfit(vector<int> &prices) {
		int n = prices.size();
		vector<array<int, 2>> dp(n);
		// dp[i][0] 当前手里没有股票 且可以买入 的情况下的后续最大收益
		// dp[i][1] 当前手里有股票的情况下的后续最大收益
		// dp[i][2] 当前手里没有股票 且不可以买入 的情况下的后续最大收益 可以用 dp[i + 1][0] 替代
		dp.back() = { 0, prices.back() };
		for(int i = n - 2; i >= 0; --i) {
			dp[i][0] = max(dp[i + 1][1] - prices[i], dp[i + 1][0]);
			dp[i][1] = max((i + 3 > n ? 0 : dp[i + 2][0]) + prices[i], dp[i + 1][1]);
		}
		return dp[0][0];
	}
};

int main() {
	Solution sol;
}